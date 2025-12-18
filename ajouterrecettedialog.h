#ifndef AJOUTERRECETTEDIALOG_H
#define AJOUTERRECETTEDIALOG_H

#include <QDialog>
#include <QMessageBox>

class Backend;

namespace Ui {
class ajouterrecetteDialog;
}

class AjouterRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterRecetteDialog(Backend *backend, QWidget *parent = nullptr);
    ~AjouterRecetteDialog();

private slots:
    void on_btnAnnuler_clicked();
    void on_btnValider_clicked();

private:
    Ui::ajouterrecetteDialog *ui;
    Backend *m_backend;
};

#endif // AJOUTERRECETTEDIALOG_H
