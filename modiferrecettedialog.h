#ifndef MODIFIERRECETTEDIALOG_H
#define MODIFIERRECETTEDIALOG_H

#include <QDialog>
#include "backend.h"
#include "metiersHeader/recette.h"

namespace Ui {
class ModifierRecetteDialog;
}

class ModifierRecetteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModifierRecetteDialog(Backend *backend, const Recette &recette, QWidget *parent = nullptr);
    ~ModifierRecetteDialog();

private slots:
    void on_btnValider_clicked();
    void on_btnAnnuler_clicked();
    void on_btnParcourir_clicked();

private:
    Ui::ModifierRecetteDialog *ui;
    Backend *m_backend;
    Recette m_recette;
    QString m_nouveauCheminPhoto;
};

#endif
