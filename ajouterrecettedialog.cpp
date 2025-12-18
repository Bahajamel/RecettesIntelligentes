#include "ajouterrecettedialog.h"
#include "ui_ajouterrecettedialog.h"
#include "backend.h"

AjouterRecetteDialog::AjouterRecetteDialog(Backend *backend, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ajouterrecetteDialog)
    , m_backend(backend)
{
    ui->setupUi(this);
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
⃣     // Créer la recette
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

    accept(); // ferme le dialog
}
