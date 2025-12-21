#include "ajouterinstructiondialog.h"
#include "ui_ajouterinstructiondialog.h"
#include <QMessageBox>

AjouterInstructionDialog::AjouterInstructionDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ajouterinstructionDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ajouter une instruction"));

    setModal(true); // IMPORTANT
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

    // Par défaut : instruction simple
    ui->radioSimple->setChecked(true);
}

AjouterInstructionDialog::~AjouterInstructionDialog()
{
    delete ui;
}

QString AjouterInstructionDialog::getContenu() const
{
    return ui->textEditContenu->toPlainText().trimmed();
}

QString AjouterInstructionDialog::getType() const
{
    return ui->radioSimple->isChecked() ? "simple" : "composee";
}

bool AjouterInstructionDialog::estComposee() const
{
    return ui->radioComposee->isChecked();
}

void AjouterInstructionDialog::on_btnValider_clicked()
{
    if (getContenu().isEmpty()) {
        QMessageBox::warning(this, tr("Erreur"),  tr("Le contenu de l'instruction est obligatoire"));
        return;
    }

    accept();
}

void AjouterInstructionDialog::on_btnAnnuler_clicked()
{
    reject();
}

void AjouterInstructionDialog::on_radioSimple_toggled(bool checked)
{
    if (checked) {
        ui->labelInfo->setText(tr("Instruction simple : une étape unique de la recette"));
    }
}

void AjouterInstructionDialog::on_radioComposee_toggled(bool checked)
{
    if (checked) {
        ui->labelInfo->setText(tr("Instruction composée : un groupe d'étapes (ex: 'Préparation de la pâte')"));
    }
}

void AjouterInstructionDialog::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);

        // remettre les textes dynamiques
        if (ui->radioSimple->isChecked()) {
            ui->labelInfo->setText(
                tr("Instruction simple : une étape unique de la recette")
                );
        } else {
            ui->labelInfo->setText(
                tr("Instruction composée : un groupe d'étapes (ex: 'Préparation de la pâte')")
                );
        }
    }
    QDialog::changeEvent(event);
}


