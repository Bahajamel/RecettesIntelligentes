#ifndef AJOUTERINSTRUCTIONDIALOG_H
#define AJOUTERINSTRUCTIONDIALOG_H

#include <QDialog>
#include <QEvent>

namespace Ui {
class ajouterinstructionDialog;
}

class AjouterInstructionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterInstructionDialog(QWidget *parent = nullptr);
    ~AjouterInstructionDialog();

    QString getContenu() const;
    QString getType() const;
    bool estComposee() const;

protected:
    void changeEvent(QEvent *event) override;

private slots:
    void on_btnValider_clicked();
    void on_btnAnnuler_clicked();
    void on_radioSimple_toggled(bool checked);
    void on_radioComposee_toggled(bool checked);

private:
    Ui::ajouterinstructionDialog *ui;
};

#endif
