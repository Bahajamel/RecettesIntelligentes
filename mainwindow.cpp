#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterrecettedialog.h"
#include <QVBoxLayout>
#include <QRegularExpression>

MainWindow::MainWindow( Backend *backend , QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backend(backend)
    , m_ingredientModel(this)
    , m_instructionModel(backend->instructionService())
{
    ui->setupUi(this);



    ui->tableViewRecettes->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Ou pour toujours afficher la barre de défilement
    ui->tableViewRecettes->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Configuration du comportement de défilement
    ui->tableViewRecettes->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->tableViewRecettes->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableViewRecettes->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    // Modèle des recettes avec proxy pour la recherche
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(backend->recetteModel());
    m_proxyModel->setFilterKeyColumn(0); // Filtrer sur la colonne 0 (Titre)
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive); // Recherche insensible à la casse
    ui->tableViewRecettes->setModel(m_proxyModel);

    // Vue des ingrédients (utilise le modèle RecetteIngredientTableModel)
    ui->ingredientTable->hide(); // widget placeholder dans le .ui
    m_ingredientsView = new QTableView(ui->tab1);
    m_ingredientsView->setModel(&m_ingredientModel);
    if (ui->verticalLayout_6) {
        ui->verticalLayout_6->insertWidget(0, m_ingredientsView);
    }

    // Vue des instructions (modèle InstructionTreeModel)
    if (ui->instructionList) ui->instructionList->hide();
    if (ui->navigation) ui->navigation->hide();
    if (ui->widget) ui->widget->hide();
    m_instructionsView = new QTreeView(ui->tab2);
    QVBoxLayout *instrLayout = qobject_cast<QVBoxLayout*>(ui->tab2->layout());
    if (!instrLayout) {
        instrLayout = new QVBoxLayout(ui->tab2);
        ui->tab2->setLayout(instrLayout);
    }
    instrLayout->addWidget(m_instructionsView);
    m_instructionsView->setModel(&m_instructionModel);

    // Connecter le champ de recherche au filtre
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchTextChanged);

    // charger au démarrage
    backend->chargerRecettes();
    auto sourceModel = backend->recetteModel();
    if (sourceModel) {
        connect(backend, &Backend::recettesModifiees,
                sourceModel,
                &RecetteTableModel::recharger);
    }

    // Réagir à la sélection d'une recette pour afficher les détails
    if (ui->tableViewRecettes->selectionModel()) {
        connect(ui->tableViewRecettes->selectionModel(),
                &QItemSelectionModel::selectionChanged,
                this,
                &MainWindow::onRecetteSelectionChanged);
    }

    // Sélectionner la première recette si disponible
    if (m_proxyModel && m_proxyModel->rowCount() > 0) {
        ui->tableViewRecettes->selectRow(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNouveau_triggered()
{
    qDebug() << "New Action triggered";
}


void MainWindow::on_actionOuvrir_triggered()
{
    qDebug() << "Ouvrir Action triggered";
}


void MainWindow::on_actionSauvegarder_triggered()
{
    qDebug() << "Save Action triggered";
}


void MainWindow::on_actionQuitter_triggered()
{
    qDebug() << "Quitter Action triggered";
    close();
}


void MainWindow::on_actionEdit_triggered()
{
    qDebug() << "Edit Action triggered";
}


void MainWindow::on_actionDelete_triggered()
{
    qDebug() << "Selete Action triggered";
}


void MainWindow::on_actionRecherche_triggered()
{
    qDebug() << "Search Action triggered";
}

void MainWindow::on_btnMyRecipes_clicked()
{
    AjouterRecetteDialog *dialog = new AjouterRecetteDialog(backend, this);

    // Connecter le signal du dialog au slot du MainWindow
    connect(dialog, &AjouterRecetteDialog::recetteAjoutee,
            this, &MainWindow::onRecetteAjoutee);

    dialog->exec();
    dialog->deleteLater();
}

void MainWindow::onRecetteAjoutee(int recetteId)
{
    // Option 1 : Recharger toutes les recettes
    backend->chargerRecettes();

    // Option 2 : Ajouter uniquement la nouvelle recette
    // (plus efficace si vous avez beaucoup de recettes)
    /*
    Recette recette = m_backend->getRecette(recetteId);
    int row = m_recetteModel->rowCount();
    m_recetteModel->insertRow(row);
    m_recetteModel->setData(m_recetteModel->index(row, 0), recette.titre);
    m_recetteModel->setData(m_recetteModel->index(row, 1), recette.description);
    */
}

void MainWindow::on_actionRenitialiser_triggered()
{
    backend->insererRecettesTest();
}

void MainWindow::onRecetteSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    if (!m_proxyModel || selected.indexes().isEmpty())
        return;

    // Obtenir l'index source depuis le proxy
    QModelIndex proxyIndex = selected.indexes().first();
    QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);
    
    auto sourceModel = qobject_cast<RecetteTableModel*>(m_proxyModel->sourceModel());
    if (!sourceModel)
        return;

    int row = sourceIndex.row();
    Recette r = sourceModel->recetteAt(row);

    // Afficher titre / description
    ui->titleLineEdit->setText(r.getTitre());
    ui->descriptionTextEdit->setPlainText(r.getDescription());

    // Ingrédients
    auto ingredients = backend->ingredientsDeRecette(r.getId());
    m_ingredientModel.setRecetteIngredients(ingredients);

    // Instructions
    backend->chargerInstructionsDansModele(m_instructionModel, r.getId());
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    if (m_proxyModel) {
        // Utiliser une expression régulière pour la recherche
        m_proxyModel->setFilterRegularExpression(QRegularExpression::escape(text));
    }
}


