#include "ajouterrecettedialog.h"
#include "ui_ajouterrecettedialog.h"
#include "backend.h"

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
    QString titre = ui->lineEditTitre->text();
    QString description = ui->textEditDescription->toPlainText();

    if (titre.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Titre obligatoire");
        return;
    }
    // 1️⃣ Créer la recette
    int recetteId = m_backend->creerRecette(titre, description);

    // 2️⃣ Ajouter ingrédients
    for (int row = 0; row < ui->tableIngredients->rowCount(); ++row) {
        if (!ui->tableIngredients->item(row, 0)) continue;

        QString nom   = ui->tableIngredients->item(row,0)->text();
        float qte     = ui->tableIngredients->item(row,1)->text().toFloat();
        QString unite = ui->tableIngredients->item(row,2)->text();

        m_backend->ajouterIngredientARecette(recetteId, nom, qte, unite);
    }

    // 3️⃣ Ajouter instructions
    for (int row = 0; row < ui->tableInstructions->rowCount(); ++row) {
        if (!ui->tableInstructions->item(row, 0)) continue;

        QString type    = ui->tableInstructions->item(row,0)->text();
        QString contenu = ui->tableInstructions->item(row,1)->text();
        int parentId    = ui->tableInstructions->item(row,2)->text().toInt();

        if (type.toLower() == "simple")
            m_backend->ajouterInstructionSimple(recetteId, parentId, contenu);
        else
            m_backend->ajouterInstructionComposee(recetteId, parentId, contenu);
    }
    emit recetteAjoutee(recetteId);
    accept() ;

}

void AjouterRecetteDialog::on_btnAjouterIngredient_clicked()
{
    // Ajouter une nouvelle ligne vide dans le tableau des ingrédients
    int row = ui->tableIngredients->rowCount();
    ui->tableIngredients->insertRow(row);

    // Créer des items éditables pour chaque colonne
    ui->tableIngredients->setItem(row, 0, new QTableWidgetItem("")); // Nom
    ui->tableIngredients->setItem(row, 1, new QTableWidgetItem("")); // Quantité
    ui->tableIngredients->setItem(row, 2, new QTableWidgetItem("")); // Unité

    // Optionnel : mettre le focus sur la première cellule de la nouvelle ligne
    ui->tableIngredients->setCurrentCell(row, 0);
    ui->tableIngredients->editItem(ui->tableIngredients->item(row, 0));

}
void AjouterRecetteDialog::on_btnAjouterInstruction_clicked()
{
    // Ajouter une nouvelle ligne vide dans le tableau des instructions
    int row = ui->tableInstructions->rowCount();
    ui->tableInstructions->insertRow(row);

    // Créer des items éditables pour chaque colonne
    ui->tableInstructions->setItem(row, 0, new QTableWidgetItem("simple")); // Type par défaut
    ui->tableInstructions->setItem(row, 1, new QTableWidgetItem(""));       // Contenu
    ui->tableInstructions->setItem(row, 2, new QTableWidgetItem("0"));      // Parent (0 = racine)

    // Optionnel : mettre le focus sur la cellule contenu
    ui->tableInstructions->setCurrentCell(row, 1);
    ui->tableInstructions->editItem(ui->tableInstructions->item(row, 1));
}


void AjouterRecetteDialog::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);

        // headers doivent être remis !
        ui->tableIngredients->setHorizontalHeaderLabels({
            tr("Nom"), tr("Quantité"), tr("Unité")
        });

        ui->tableInstructions->setHorizontalHeaderLabels({
            tr("Type"), tr("Contenu"), tr("Parent")
        });
    }
    QDialog::changeEvent(event);
}
