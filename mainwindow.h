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
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QPushButton>
#include <QVBoxLayout>
#include "metiersHeader/recette.h"


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
    void on_btnAddRecipe_clicked();
    void on_btnDeleteRecipe_clicked();
    void on_searchLineEdit_textChanged(const QString &text);
    void on_btnAddIngredient_clicked();
    void on_btnAddInstruction_clicked();
    void on_actionRenitialiser_triggered();
    void onRecetteSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onSearchTextChanged(const QString &text);
    void creerMenu();
    void updateInstructionDisplay();

private:
    void refreshRecipeList();
    void displayRecipeDetails(const Recette &recipe);
    void clearRecipeDetails();
    QPushButton* createRecipeCard(const Recette &recipe , int &index);
    void updateRecipeDetails();
    void displayRecipeImage(const QString &photoUrl);
    void displayIngredients(const Recette &recipe);
    void displayInstructions(const Recette &recipe);

    Ui::MainWindow *ui;
    Backend *backend;

    RecetteIngredientTableModel m_ingredientModel;
    InstructionTreeModel m_instructionModel;
    QTableView *m_ingredientsView = nullptr;
    QTreeView *m_instructionsView = nullptr;
    QSortFilterProxyModel *m_proxyModel = nullptr;
    int m_currentInstructionIndex = 0;
    QList<QSharedPointer<Instruction>> m_currentInstructions;
    QList<QPushButton*> m_recipeCards;
    int m_selectedRecipeId = -1;
    QString m_searchQuery;
    QString m_currentPhotoUrl;
    QTimer *m_updateTimer = nullptr;
};
#endif // MAINWINDOW_H
