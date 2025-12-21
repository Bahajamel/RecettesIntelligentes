#ifndef AJOUTERINGREDIENTDIALOG_H
#define AJOUTERINGREDIENTDIALOG_H

#include <QDialog>

namespace Ui {
class AjouterIngredientDialog;
}

class AjouterIngredientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterIngredientDialog(QWidget *parent = nullptr);
    ~AjouterIngredientDialog();

    QString getNom() const;
    float getQuantite() const;
    QString getUnite() const;

private slots:
    void on_btnValider_clicked();
    void on_btnAnnuler_clicked();

private:
    Ui::AjouterIngredientDialog *ui;

};



#endif
