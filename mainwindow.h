#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QTreeView>
#include <QItemSelection>
#include <QSortFilterProxyModel>
#include "backend.h"
#include "modelsHeader/recetteingredientmodel.h"
#include "modelsHeader/instructiontreemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Backend *backend, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSauvegarder_triggered();

    void on_actionQuitter_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void on_actionRecherche_triggered();

    void on_btnMyRecipes_clicked();

    void on_actionRenitialiser_triggered();

    void onRecetteSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSearchTextChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    Backend *backend;

    RecetteIngredientTableModel m_ingredientModel;
    InstructionTreeModel m_instructionModel;
    QTableView *m_ingredientsView = nullptr;
    QTreeView *m_instructionsView = nullptr;
    QSortFilterProxyModel *m_proxyModel = nullptr;
};
#endif // MAINWINDOW_H
