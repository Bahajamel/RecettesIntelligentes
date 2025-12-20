#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterrecettedialog.h"
#include <QVBoxLayout>
<<<<<<< HEAD
#include <QRegularExpression>
=======
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QMessageBox>
#include <QPixmap>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include "serviceHeader/recetteservice.h"
#include "metiersHeader/recetteingredient.h"
#include "metiersHeader/instructionsimple.h"
#include "metiersHeader/instructioncomposee.h"
#include "metiersHeader/unite.h"
>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a

MainWindow::MainWindow(Backend *backend, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backend(backend)
<<<<<<< HEAD
    , m_ingredientModel(this)
    , m_instructionModel(backend->instructionService())
{
    ui->setupUi(this);

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
=======
    , m_proxyModel(nullptr)
    , m_selectedRecipeId(-1)
{
    ui->setupUi(this);
>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a

    // Setup proxy model for filtering
    RecetteTableModel *sourceModel = backend->recetteModel();
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(sourceModel);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setFilterKeyColumn(-1);

    // Connect search
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_searchLineEdit_textChanged);

    // Connect buttons
    connect(ui->btnAddRecipe, &QPushButton::clicked, this, &MainWindow::on_btnAddRecipe_clicked);
    connect(ui->btnDeleteRecipe, &QPushButton::clicked, this, &MainWindow::on_btnDeleteRecipe_clicked);
    connect(ui->btnAddIngredient, &QPushButton::clicked, this, &MainWindow::on_btnAddIngredient_clicked);
    connect(ui->btnAddInstruction, &QPushButton::clicked, this, &MainWindow::on_btnAddInstruction_clicked);

    // Connect recipe detail edits avec délai pour éviter trop de sauvegardes
    m_updateTimer = new QTimer(this);
    m_updateTimer->setSingleShot(true);
    m_updateTimer->setInterval(1000); // 1 seconde de délai
    connect(m_updateTimer, &QTimer::timeout, this, &MainWindow::updateRecipeDetails);
    
    connect(ui->recipeTitleEdit, &QLineEdit::textChanged, this, [this]() {
        m_updateTimer->start(); // Redémarrer le timer à chaque changement
    });
    connect(ui->recipeDescriptionEdit, &QTextEdit::textChanged, this, [this]() {
        m_updateTimer->start();
    });

    // Load recipes
    backend->chargerRecettes();
<<<<<<< HEAD
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
=======
    refreshRecipeList();

    // Show empty state initially
    clearRecipeDetails();
>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshRecipeList()
{
    // Clear existing cards
    for (QPushButton* card : m_recipeCards) {
        card->deleteLater();
    }
    m_recipeCards.clear();

    // Get filtered recipes
    QList<Recette> allRecettes = backend->recetteModel()->getRecettes();
    QList<Recette> filteredRecettes;

    // Apply search filter
    if (m_searchQuery.isEmpty()) {
        filteredRecettes = allRecettes;
    } else {
        QString query = m_searchQuery.toLower();
        for (const Recette &r : allRecettes) {
            if (r.getTitre().toLower().contains(query) ||
                r.getDescription().toLower().contains(query)) {
                filteredRecettes.append(r);
            }
        }
    }

    // Create cards
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->recipeListContainer->layout());
    if (!layout) return;

    // Remove spacer temporarily
    QLayoutItem *spacer = layout->takeAt(0);
    delete spacer;

    for (int i = 0; i < filteredRecettes.size(); ++i) {
        QPushButton *card = createRecipeCard(filteredRecettes[i], i);
        layout->addWidget(card);
        m_recipeCards.append(card);
    }

    // Add spacer back at the end
    layout->addStretch();
}

QPushButton* MainWindow::createRecipeCard(const Recette &recipe, int index)
{
    QPushButton *card = new QPushButton(ui->recipeListContainer);
    card->setObjectName(QString("recipeCard_%1").arg(recipe.getId()));
    card->setCheckable(true);
    card->setChecked(recipe.getId() == m_selectedRecipeId);

    // Create card layout
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(12, 12, 12, 12);
    cardLayout->setSpacing(12);

    // Thumbnail avec image
    QLabel *thumbnail = new QLabel(card);
    thumbnail->setFixedSize(64, 64);
    thumbnail->setScaledContents(true);
    thumbnail->setStyleSheet("background: rgba(245, 242, 232, 0.5); border-radius: 6px;");
    
    if (!recipe.getPhoto().isEmpty()) {
        QPixmap pixmap(recipe.getPhoto());
        if (!pixmap.isNull()) {
            thumbnail->setPixmap(pixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            // Si l'URL ne fonctionne pas, afficher un placeholder
            thumbnail->setText("📷");
            thumbnail->setAlignment(Qt::AlignCenter);
        }
    } else {
        thumbnail->setText("📷");
        thumbnail->setAlignment(Qt::AlignCenter);
    }
    cardLayout->addWidget(thumbnail);

    // Content
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setSpacing(4);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // Title
    QLabel *titleLabel = new QLabel(recipe.getTitre(), card);
    titleLabel->setStyleSheet("font-weight: 600; font-size: 14px; color: #2d2418;");
    titleLabel->setWordWrap(true);
    contentLayout->addWidget(titleLabel);

    // Description preview
    QString desc = recipe.getDescription();
    if (desc.length() > 50) desc = desc.left(50) + "...";
    QLabel *descLabel = new QLabel(desc, card);
    descLabel->setStyleSheet("font-size: 12px; color: #6b7280;");
    descLabel->setWordWrap(true);
    contentLayout->addWidget(descLabel);

    cardLayout->addLayout(contentLayout, 1);
    cardLayout->addStretch();

    // Connect click
    connect(card, &QPushButton::clicked, this, [this, recipe]() {
        m_selectedRecipeId = recipe.getId();
        // Charger la recette complète avec ingrédients et instructions
        Recette completeRecipe = backend->obtenirRecetteComplete(recipe.getId());
        displayRecipeDetails(completeRecipe);
        refreshRecipeList(); // Refresh to update selection
    });

    return card;
}

void MainWindow::displayRecipeDetails(const Recette &recipe)
{
    ui->recipeTitleEdit->setText(recipe.getTitre());
    ui->recipeDescriptionEdit->setPlainText(recipe.getDescription());

    // Afficher l'image dans l'onglet Détails
    displayRecipeImage(recipe.getPhoto());

    // Afficher les ingrédients
    displayIngredients(recipe);

    // Afficher les instructions
    displayInstructions(recipe);

    // Update stats
    int ingredientCount = recipe.getIngredients().size();
    int instructionCount = recipe.getNombreInstructions();
    ui->timeLabel->setText(QString("%1 ingrédients").arg(ingredientCount));
    ui->servingsLabel->setText(QString("%1 instructions").arg(instructionCount));

    // Enable delete button
    ui->btnDeleteRecipe->setEnabled(true);
}

void MainWindow::clearRecipeDetails()
{
    ui->recipeTitleEdit->clear();
    ui->recipeDescriptionEdit->clear();
    ui->timeLabel->setText("0 min total");
    ui->servingsLabel->setText("0 portions");
    ui->btnDeleteRecipe->setEnabled(false);
    m_selectedRecipeId = -1;
}

void MainWindow::updateRecipeDetails()
{
    if (m_selectedRecipeId < 0) return;

    QString titre = ui->recipeTitleEdit->text();
    QString description = ui->recipeDescriptionEdit->toPlainText();
    QString photo = m_currentPhotoUrl;

    bool success = backend->mettreAJourRecette(m_selectedRecipeId, titre, description, photo);
    if (success) {
        refreshRecipeList();
        // Ne pas recharger complètement pour éviter de perdre le focus
        // Juste mettre à jour la liste
    }
}

void MainWindow::on_btnAddRecipe_clicked()
{
    AjouterRecetteDialog dlg(backend, this);
    if (dlg.exec() == QDialog::Accepted) {
        backend->chargerRecettes();
        refreshRecipeList();
        clearRecipeDetails();
    }
}

void MainWindow::on_btnDeleteRecipe_clicked()
{
    if (m_selectedRecipeId < 0) return;

    int ret = QMessageBox::question(this, "Supprimer", "Voulez-vous vraiment supprimer cette recette ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        bool success = backend->supprimerRecette(m_selectedRecipeId);
        if (success) {
            refreshRecipeList();
            clearRecipeDetails();
        } else {
            QMessageBox::warning(this, "Erreur", "Impossible de supprimer la recette");
        }
    }
}

void MainWindow::displayRecipeImage(const QString &photoUrl)
{
    m_currentPhotoUrl = photoUrl;
    
    // Trouver ou créer le widget d'image dans l'onglet Détails
    QWidget *detailsContent = ui->detailsContent;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(detailsContent->layout());
    if (!layout) return;

    // Chercher si une image existe déjà
    QLabel *imageLabel = detailsContent->findChild<QLabel*>("recipeImageLabel");
    QLineEdit *photoUrlEdit = detailsContent->findChild<QLineEdit*>("photoUrlEdit");
    
    if (!imageLabel) {
        // Créer le label d'image
        imageLabel = new QLabel(detailsContent);
        imageLabel->setObjectName("recipeImageLabel");
        imageLabel->setMinimumHeight(200);
        imageLabel->setMaximumHeight(300);
        imageLabel->setScaledContents(true);
        imageLabel->setStyleSheet("background: rgba(245, 242, 232, 0.5); border-radius: 8px;");
        imageLabel->setAlignment(Qt::AlignCenter);
        layout->insertWidget(0, imageLabel);
    }

    if (!photoUrlEdit) {
        // Créer le champ pour l'URL de la photo
        photoUrlEdit = new QLineEdit(detailsContent);
        photoUrlEdit->setObjectName("photoUrlEdit");
        photoUrlEdit->setPlaceholderText("URL de la photo...");
        connect(photoUrlEdit, &QLineEdit::textChanged, this, [this, imageLabel](const QString &url) {
            m_currentPhotoUrl = url;
            if (!url.isEmpty()) {
                QPixmap pixmap(url);
                if (!pixmap.isNull()) {
                    imageLabel->setPixmap(pixmap.scaled(imageLabel->width(), 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                } else {
                    imageLabel->setText("📷\nURL invalide");
                }
            } else {
                imageLabel->setText("📷\nAucune image");
            }
            // Sauvegarder automatiquement
            QTimer::singleShot(1000, this, &MainWindow::updateRecipeDetails);
        });
        layout->insertWidget(1, photoUrlEdit);
    }

    photoUrlEdit->setText(photoUrl);

    if (!photoUrl.isEmpty()) {
        QPixmap pixmap(photoUrl);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap.scaled(imageLabel->width(), 250, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            imageLabel->setText("📷\nURL d'image invalide");
        }
    } else {
        imageLabel->setText("📷\nAucune image");
    }
}

void MainWindow::displayIngredients(const Recette &recipe)
{
    QWidget *ingredientsContent = ui->ingredientsContent;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ingredientsContent->layout());
    if (!layout) return;

    // Nettoyer les widgets existants (sauf le spacer)
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget()->objectName().startsWith("ingredient_")) {
            delete item->widget();
        }
        delete item;
    }

    // Ajouter les ingrédients
    const QList<RecetteIngredient> &ingredients = recipe.getIngredients();
    for (const RecetteIngredient &ri : ingredients) {
        QWidget *ingWidget = new QWidget(ingredientsContent);
        ingWidget->setObjectName(QString("ingredient_%1").arg(ri.getIngredient().getId()));
        
        QHBoxLayout *ingLayout = new QHBoxLayout(ingWidget);
        ingLayout->setContentsMargins(12, 8, 12, 8);
        ingLayout->setSpacing(8);

        // Quantité
        QLabel *qteLabel = new QLabel(QString::number(ri.getQuantite()), ingWidget);
        qteLabel->setMinimumWidth(60);
        qteLabel->setAlignment(Qt::AlignCenter);
        ingLayout->addWidget(qteLabel);

        // Unité
        QLabel *unitLabel = new QLabel(uniteToString(ri.getUnite()), ingWidget);
        unitLabel->setMinimumWidth(80);
        ingLayout->addWidget(unitLabel);

        // Nom
        QLabel *nameLabel = new QLabel(ri.getIngredient().getNom(), ingWidget);
        nameLabel->setStyleSheet("font-weight: 500;");
        ingLayout->addWidget(nameLabel, 1);

        layout->addWidget(ingWidget);
    }

    // Remettre le spacer à la fin
    layout->addStretch();
}

void MainWindow::displayInstructions(const Recette &recipe)
{
    QWidget *instructionsContent = ui->instructionsContent;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(instructionsContent->layout());
    if (!layout) return;

    // Nettoyer les widgets existants
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget() && item->widget()->objectName().startsWith("instruction_")) {
            delete item->widget();
        }
        delete item;
    }

    // Ajouter les instructions
    const QList<QSharedPointer<Instruction>> &instructions = recipe.getInstructions();
    int order = 1;
    for (const QSharedPointer<Instruction> &inst : instructions) {
        QWidget *instWidget = new QWidget(instructionsContent);
        instWidget->setObjectName(QString("instruction_%1").arg(order));
        
        QHBoxLayout *instLayout = new QHBoxLayout(instWidget);
        instLayout->setContentsMargins(12, 12, 12, 12);
        instLayout->setSpacing(12);

        // Numéro d'ordre
        QLabel *orderLabel = new QLabel(QString::number(order), instWidget);
        orderLabel->setFixedSize(32, 32);
        orderLabel->setAlignment(Qt::AlignCenter);
        orderLabel->setStyleSheet("background: #d97706; color: white; border-radius: 16px; font-weight: bold;");
        instLayout->addWidget(orderLabel);

        // Contenu
        QTextEdit *contentEdit = new QTextEdit(instWidget);
        contentEdit->setReadOnly(true);
        contentEdit->setMaximumHeight(80);
        
        if (inst->estSimple()) {
            // Instruction simple : utiliser afficher() ou getContenu()
            contentEdit->setPlainText(inst->afficher());
        } else {
            // Instruction composée
            QSharedPointer<InstructionComposee> composee = inst.staticCast<InstructionComposee>();
            contentEdit->setPlainText(composee->getTitre());
        }
        
        instLayout->addWidget(contentEdit, 1);

        layout->addWidget(instWidget);
        order++;
    }

    // Remettre le spacer à la fin
    layout->addStretch();
}

void MainWindow::on_btnAddIngredient_clicked()
{
    if (m_selectedRecipeId < 0) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une recette d'abord");
        return;
    }
    // TODO: Ouvrir un dialog pour ajouter un ingrédient
    QMessageBox::information(this, "Info", "Ajouter ingrédient - Utilisez le dialog d'ajout de recette pour l'instant");
}

void MainWindow::on_btnAddInstruction_clicked()
{
    if (m_selectedRecipeId < 0) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une recette d'abord");
        return;
    }
    // TODO: Ouvrir un dialog pour ajouter une instruction
    QMessageBox::information(this, "Info", "Ajouter instruction - Utilisez le dialog d'ajout de recette pour l'instant");
}

void MainWindow::on_searchLineEdit_textChanged(const QString &text)
{
    m_searchQuery = text;
    refreshRecipeList();
}

void MainWindow::on_actionNouveau_triggered()
{
    on_btnAddRecipe_clicked();
}

void MainWindow::on_actionOuvrir_triggered()
{
    qDebug() << "Ouvrir Action triggered";
}

void MainWindow::on_actionSauvegarder_triggered()
{
    updateRecipeDetails();
}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionEdit_triggered()
{
    qDebug() << "Edit Action triggered";
}

void MainWindow::on_actionDelete_triggered()
{
    on_btnDeleteRecipe_clicked();
}

void MainWindow::on_actionRecherche_triggered()
{
    ui->searchLineEdit->setFocus();
}
<<<<<<< HEAD

void MainWindow::on_btnMyRecipes_clicked()
{
    AjouterRecetteDialog dlg(backend, this);
    if (dlg.exec() == QDialog::Accepted) {
        backend->chargerRecettes(); // rafraîchir la table
    }
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


=======
>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a
