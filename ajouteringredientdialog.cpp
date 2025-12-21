#include "ajouteringredientdialog.h"
#include "ui_ajouteringredientdialog.h"
#include <QMessageBox>

AjouterIngredientDialog::AjouterIngredientDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AjouterIngredientDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ajouter un ingrédient"));
    setModal(true); // IMPORTANT
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    ui->lineEditNom->setFocus();

}

AjouterIngredientDialog::~AjouterIngredientDialog()
{
    delete ui;
}

QString AjouterIngredientDialog::getNom() const
{
    return ui->lineEditNom->text().trimmed();
}

float AjouterIngredientDialog::getQuantite() const
{
    return ui->doubleSpinBoxQuantite->value();
}

QString AjouterIngredientDialog::getUnite() const
{
    return ui->comboBoxUnite->currentText();
}

void AjouterIngredientDialog::on_btnValider_clicked()
{
    if (getNom().isEmpty()) {
        QMessageBox::warning(this,tr("Erreur"), tr("Le nom de l'ingrédient est obligatoire"));
        return;
    }

    if (getQuantite() <= 0) {
        QMessageBox::warning(this, tr("Erreur"), tr("La quantité doit être supérieure à 0"));
        return;
    }

    accept();
}

void AjouterIngredientDialog::on_btnAnnuler_clicked()
{
    reject();
}
