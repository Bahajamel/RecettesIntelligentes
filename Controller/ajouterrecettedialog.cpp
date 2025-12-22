#include "ControllerHeader/ajouterrecettedialog.h"
#include "ui_ajouterrecettedialog.h"
#include "modelsHeader/ServiceLayerHeader/backend.h"

#include <QMessageBox>
#include <QDebug>
#include <QHash>
#include <QVector>

AjouterRecetteDialog::AjouterRecetteDialog(Backend *backend, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ajouterrecetteDialog)
    , m_backend(backend)
{
    ui->setupUi(this);

    ui->btnValider->setAutoDefault(false);
    ui->btnValider->setDefault(false);
    ui->btnAnnuler->setAutoDefault(false);

    ui->tableIngredients->setColumnCount(3);
    ui->tableIngredients->setHorizontalHeaderLabels({"Nom", "Quantité", "Unité"});
    ui->tableIngredients->setEditTriggers(QAbstractItemView::DoubleClicked |
                                          QAbstractItemView::SelectedClicked |
                                          QAbstractItemView::EditKeyPressed);
    ui->tableIngredients->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableIngredients->horizontalHeader()->setStretchLastSection(true);

    ui->tableInstructions->setColumnCount(3);
    ui->tableInstructions->setHorizontalHeaderLabels({"Type", "Contenu", "Parent"});
    ui->tableInstructions->setEditTriggers(QAbstractItemView::DoubleClicked |
                                           QAbstractItemView::SelectedClicked |
                                           QAbstractItemView::EditKeyPressed);
    ui->tableInstructions->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableInstructions->horizontalHeader()->setStretchLastSection(true);
}

AjouterRecetteDialog::~AjouterRecetteDialog()
{
    delete ui;
}

void AjouterRecetteDialog::on_btnAnnuler_clicked()
{
    reject();
}

void AjouterRecetteDialog::on_btnValider_clicked()
{
    QString titre = ui->lineEditTitre->text().trimmed();
    QString description = ui->textEditDescription->toPlainText().trimmed();

    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Titre obligatoire");
        return;
    }

    // 1) Créer la recette
    int recetteId = m_backend->creerRecette(titre, description);

    // 2) Ajouter ingrédients
    for (int row = 0; row < ui->tableIngredients->rowCount(); ++row) {
        if (!ui->tableIngredients->item(row, 0)) continue;

        QString nom = ui->tableIngredients->item(row, 0)->text().trimmed();
        QString qteTxt = ui->tableIngredients->item(row, 1) ? ui->tableIngredients->item(row, 1)->text().trimmed() : "";
        QString unite = ui->tableIngredients->item(row, 2) ? ui->tableIngredients->item(row, 2)->text().trimmed() : "";

        if (nom.isEmpty()) continue;

        bool ok = false;
        float qte = qteTxt.toFloat(&ok);
        if (!ok) qte = 0.0f;

        m_backend->ajouterIngredientARecette(recetteId, nom, qte, unite);

        m_backend->chargerRecettes();   // or emit recettesModifiees(); then chargerRecettes()
    }

    // 3) Ajouter instructions
    // Problème corrigé :
    // - "Parent = 0" n'est PAS une racine en SQL si la racine est "NULL".
    // - on force la racine à -1 côté backend (=> NULL dans la BD).
    // - on supporte aussi un parent donné sous forme "numéro de ligne" (1-based).
    QHash<int, int> rowToInstructionId; // rowIndex -> instructionId SQL renvoyé par le backend
    rowToInstructionId.reserve(ui->tableInstructions->rowCount());

    qDebug() << "Nombre de lignes d'instructions:" << ui->tableInstructions->rowCount();

    for (int row = 0; row < ui->tableInstructions->rowCount(); ++row) {
        auto typeItem = ui->tableInstructions->item(row, 0);
        auto contItem = ui->tableInstructions->item(row, 1);

        // On garde un slot même si on skip (pour mapping ligne->id)
        rowToInstructionId[row] = -1;

        if (!typeItem || !contItem) continue;

        QString type = typeItem->text().trimmed();
        QString contenu = contItem->text().trimmed();
        if (contenu.isEmpty()) continue;

        // parentId = -1 => racine (NULL en DB)
        int parentId = -1;

        auto parentItem = ui->tableInstructions->item(row, 2);
        QString parentTxt = parentItem ? parentItem->text().trimmed() : "";

        if (!parentTxt.isEmpty()) {
            bool ok = false;
            int raw = parentTxt.toInt(&ok);

            if (ok) {
                if (raw == 0) {
                    // 0 => racine
                    parentId = -1;
                } else if (raw > 0 && raw <= row) {
                    // raw est un "numéro de ligne" (1-based) : 1 => row 0
                    int parentRow = raw - 1;
                    int mapped = rowToInstructionId.value(parentRow, -1);

                    // Si le parent a bien été inséré avant, on utilise son vrai id SQL
                    if (mapped != -1) parentId = mapped;
                    else parentId = -1; // fallback racine pour éviter un parent invalide
                } else {
                    // sinon, on considère que c'est un id SQL direct
                    parentId = raw;
                }
            }
        }

        int createdId = -1;
        if (type.toLower() == "simple") {
            // IMPORTANT : ce code suppose que Backend renvoie l'ID de l'instruction créée
            createdId = m_backend->ajouterInstructionSimple(recetteId, parentId, contenu);
        } else {
            createdId = m_backend->ajouterInstructionComposee(recetteId, parentId, contenu);
        }

        rowToInstructionId[row] = createdId;

        if (createdId == -1) {
            QMessageBox::warning(
                this,
                "Instruction non enregistrée",
                QString("Insertion échouée pour l'instruction (ligne %1).\nContenu: %2\nParent: %3")
                    .arg(row + 1)
                    .arg(contenu)
                    .arg(parentTxt.isEmpty() ? "racine" : parentTxt)
                );
        }

        qDebug() << "Instruction ajoutée:" << contenu
                 << "| parentId:" << parentId
                 << "| createdId:" << createdId;
    }

    emit recetteAjoutee(recetteId);
    accept();
}

void AjouterRecetteDialog::on_btnAjouterIngredient_clicked()
{
    int row = ui->tableIngredients->rowCount();
    ui->tableIngredients->insertRow(row);

    ui->tableIngredients->setItem(row, 0, new QTableWidgetItem("")); // Nom
    ui->tableIngredients->setItem(row, 1, new QTableWidgetItem("")); // Quantité
    ui->tableIngredients->setItem(row, 2, new QTableWidgetItem("")); // Unité

    ui->tableIngredients->setCurrentCell(row, 0);
    ui->tableIngredients->editItem(ui->tableIngredients->item(row, 0));
}

void AjouterRecetteDialog::on_btnAjouterInstruction_clicked()
{
    int row = ui->tableInstructions->rowCount();
    ui->tableInstructions->insertRow(row);

    ui->tableInstructions->setItem(row, 0, new QTableWidgetItem("simple")); // Type
    ui->tableInstructions->setItem(row, 1, new QTableWidgetItem(""));       // Contenu

    // CORRECTION: parent vide = racine (NULL). Ne pas mettre "0".
    ui->tableInstructions->setItem(row, 2, new QTableWidgetItem(""));

    ui->tableInstructions->setCurrentCell(row, 1);
    ui->tableInstructions->editItem(ui->tableInstructions->item(row, 1));
}
