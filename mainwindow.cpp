#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogHeader/ajouterrecettedialog.h"
#include "metiersHeader/recetteingredient.h"
#include "metiersHeader/instructioncomposee.h"
#include "metiersHeader/unite.h"
#include "dialogHeader/ajouteringredientdialog.h"
#include "dialogHeader/ajouterinstructiondialog.h"
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>

MainWindow::MainWindow(Backend *backend, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backend(backend)
    , m_ingredientModel(this)
    , m_instructionModel(backend->instructionService())
    , m_selectedRecipeId(-1)
{
    ui->setupUi(this);

    // Style pour la barre de menu
    menuBar()->setStyleSheet(
        "QMenuBar {"
        "    background-color: #f0f0f0;"
        "    color: black;"
        "    border-bottom: 1px solid #d0d0d0;"
        "}"
        "QMenuBar::item {"
        "    background-color: transparent;"
        "    padding: 4px 10px;"
        "}"
        "QMenuBar::item:selected {"
        "    background-color: #e67e22;"
        "    color: white;"
        "}"
        "QMenu {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid #d0d0d0;"
        "}"
        "QMenu::item:selected {"
        "    background-color: #e67e22;"
        "    color: white;"
        "}"
        );

    creerMenu();

    // Vue des ingrédients
    ui->ingredientTable->hide();
    m_ingredientsView = new QTableView(ui->tab1);
    m_ingredientsView->setModel(&m_ingredientModel);
    if (ui->verticalLayout_6) {
        ui->verticalLayout_6->insertWidget(0, m_ingredientsView);
    }

    // Vue des instructions
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

    // Connect search
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::on_searchLineEdit_textChanged);

    // Connect buttons
    connect(ui->btnAddRecipe, &QPushButton::clicked,
            this, &MainWindow::on_btnAddRecipe_clicked);
    connect(ui->btnDeleteRecipe, &QPushButton::clicked,
            this, &MainWindow::on_btnDeleteRecipe_clicked);
    connect(ui->btnAddIngredient, &QPushButton::clicked,
            this, &MainWindow::on_btnAddIngredient_clicked);
    connect(ui->btnAddInstruction, &QPushButton::clicked,
            this, &MainWindow::on_btnAddInstruction_clicked);

    // Connect recipe detail edits
    m_updateTimer = new QTimer(this);
    m_updateTimer->setSingleShot(true);
    m_updateTimer->setInterval(1000);
    connect(m_updateTimer, &QTimer::timeout,
            this, &MainWindow::updateRecipeDetails);

    connect(ui->recipeTitleEdit, &QLineEdit::textChanged, this, [this]() {
        m_updateTimer->start();
    });
    connect(ui->recipeDescriptionEdit, &QTextEdit::textChanged, this, [this]() {
        m_updateTimer->start();
    });

    // Load recipes
    backend->chargerRecettes();

    // Afficher les recettes avec les cartes
    refreshRecipeList();

    // Show empty state initially
    clearRecipeDetails();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creerMenu()
{
    // Menu Fichier
    QMenu *menuFichier = menuBar()->addMenu("Fichier");

    QAction *actionNouveau = new QAction("Nouveau", this);
    actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
    connect(actionNouveau, &QAction::triggered, this, &MainWindow::on_actionNouveau_triggered);
    menuFichier->addAction(actionNouveau);

    QAction *actionOuvrir = new QAction("Ouvrir", this);
    actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
    connect(actionOuvrir, &QAction::triggered, this, &MainWindow::on_actionOuvrir_triggered);
    menuFichier->addAction(actionOuvrir);

    QAction *actionSauvegarder = new QAction("Sauvegarder", this);
    actionSauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    connect(actionSauvegarder, &QAction::triggered, this, &MainWindow::on_actionSauvegarder_triggered);
    menuFichier->addAction(actionSauvegarder);

    menuFichier->addSeparator();

    QAction *actionQuitter = new QAction("Quitter", this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter, &QAction::triggered, this, &MainWindow::on_actionQuitter_triggered);
    menuFichier->addAction(actionQuitter);

    // Menu Édition
    QMenu *menuEdition = menuBar()->addMenu("Édition");

    QAction *actionEdit = new QAction("Modifier", this);
    actionEdit->setShortcut(QKeySequence("Ctrl+E"));
    connect(actionEdit, &QAction::triggered, this, &MainWindow::on_actionEdit_triggered);
    menuEdition->addAction(actionEdit);

    QAction *actionDelete = new QAction("Supprimer", this);
    actionDelete->setShortcut(QKeySequence("Delete"));
    connect(actionDelete, &QAction::triggered, this, &MainWindow::on_actionDelete_triggered);
    menuEdition->addAction(actionDelete);

    menuEdition->addSeparator();

    QAction *actionRecherche = new QAction("Rechercher", this);
    actionRecherche->setShortcut(QKeySequence("Ctrl+F"));
    connect(actionRecherche, &QAction::triggered, this, &MainWindow::on_actionRecherche_triggered);
    menuEdition->addAction(actionRecherche);

    // Menu Outils
    QMenu *menuOutils = menuBar()->addMenu("Outils");

    QAction *actionReinitialiser = new QAction("Réinitialiser (données test)", this);
    actionReinitialiser->setShortcut(QKeySequence("Ctrl+R"));
    connect(actionReinitialiser, &QAction::triggered, this, &MainWindow::on_actionRenitialiser_triggered);
    menuOutils->addAction(actionReinitialiser);
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

QPushButton* MainWindow::createRecipeCard(const Recette &recipe, int &index)
{
    QPushButton *card = new QPushButton(ui->recipeListContainer);
    card->setObjectName(QString("recipeCard_%1").arg(recipe.getId()));
    card->setCheckable(true);
    card->setChecked(recipe.getId() == m_selectedRecipeId);
    card->setMinimumHeight(100);
    card->setMaximumHeight(120);

    // Create card layout
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(12, 12, 12, 12);
    cardLayout->setSpacing(12);

    // Thumbnail simple sans image
    QLabel *thumbnail = new QLabel(card);
    thumbnail->setFixedSize(90, 90);
    thumbnail->setScaledContents(false);
    thumbnail->setAlignment(Qt::AlignCenter);
    thumbnail->setText("🍳");
    thumbnail->setStyleSheet(
        "QLabel { "
        "  background: rgba(245, 242, 232, 0.5); "
        "  border-radius: 8px; "
        "  border: 1px solid #e5ddd0; "
        "  font-size: 32px; "
        "  color: #9ca3af; "
        "}"
        );

    cardLayout->addWidget(thumbnail);

    // Content
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setSpacing(6);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // Title
    QLabel *titleLabel = new QLabel(recipe.getTitre(), card);
    titleLabel->setStyleSheet(
        "font-weight: 600; "
        "font-size: 15px; "
        "color: #2d2418; "
        "background: transparent;"
        );
    titleLabel->setWordWrap(true);
    titleLabel->setMaximumHeight(45);
    contentLayout->addWidget(titleLabel);

    // Description preview
    QString desc = recipe.getDescription();
    if (desc.length() > 60) desc = desc.left(60) + "...";
    QLabel *descLabel = new QLabel(desc, card);
    descLabel->setStyleSheet(
        "font-size: 13px; "
        "color: #6b7280; "
        "background: transparent;"
        );
    descLabel->setWordWrap(true);
    descLabel->setMaximumHeight(40);
    contentLayout->addWidget(descLabel);

    cardLayout->addLayout(contentLayout, 1);

    // Connect click
    connect(card, &QPushButton::clicked, this, [this, recipe]() {
        m_selectedRecipeId = recipe.getId();
        Recette completeRecipe = backend->obtenirRecetteComplete(recipe.getId());
        displayRecipeDetails(completeRecipe);
        refreshRecipeList();
    });

    return card;
}

void MainWindow::displayRecipeDetails(const Recette &recipe)
{
    ui->recipeTitleEdit->setText(recipe.getTitre());
    ui->recipeDescriptionEdit->setPlainText(recipe.getDescription());

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

    bool success = backend->mettreAJourRecette(m_selectedRecipeId, titre, description);
    if (success) {
        refreshRecipeList();
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

void MainWindow::displayIngredients(const Recette &recipe)
{
    QWidget *ingredientsContent = ui->ingredientsContent;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ingredientsContent->layout());
    if (!layout) return;

    // Nettoyer les widgets existants
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }

    const QList<RecetteIngredient> &ingredients = recipe.getIngredients();

    if (ingredients.isEmpty()) {
        QLabel *emptyLabel = new QLabel("Aucun ingrédient", ingredientsContent);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #9ca3af; padding: 40px; background: transparent;");
        layout->addWidget(emptyLabel);
        layout->addStretch();
        return;
    }

    // Ajouter les ingrédients un par un
    for (int i = 0; i < ingredients.size(); ++i) {
        const RecetteIngredient &ri = ingredients[i];

        QWidget *row = new QWidget(ingredientsContent);
        row->setObjectName(QString("ingredient_%1").arg(i));
        row->setMinimumHeight(50);
        row->setMaximumHeight(65);

        row->setStyleSheet(
            "QWidget { "
            "  background: transparent; "
            "  border: none; "
            "  border-bottom: 1px solid #f0ede5; "
            "  padding: 8px 4px; "
            "}"
            "QWidget:hover { "
            "  background: rgba(217, 119, 6, 0.03); "
            "}"
            );

        QHBoxLayout *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(8, 8, 8, 8);
        rowLayout->setSpacing(20);

        // Quantité + Unité
        QWidget *qteContainer = new QWidget(row);
        qteContainer->setFixedWidth(140);
        QHBoxLayout *qteLayout = new QHBoxLayout(qteContainer);
        qteLayout->setContentsMargins(0, 0, 0, 0);
        qteLayout->setSpacing(8);

        QLabel *qteLabel = new QLabel(QString::number(ri.getQuantite()), qteContainer);
        qteLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        qteLabel->setStyleSheet(
            "font-weight: 700; "
            "font-size: 18px; "
            "color: #d97706; "
            "background: transparent;"
            );
        qteLayout->addWidget(qteLabel);

        QLabel *unitLabel = new QLabel(uniteToString(ri.getUnite()), qteContainer);
        unitLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        unitLabel->setStyleSheet(
            "color: #9ca3af; "
            "font-size: 14px; "
            "font-weight: 500; "
            "background: transparent;"
            );
        qteLayout->addWidget(unitLabel);
        qteLayout->addStretch();

        rowLayout->addWidget(qteContainer);

        // Nom de l'ingrédient
        QLabel *nameLabel = new QLabel(ri.getIngredient().getNom(), row);
        nameLabel->setStyleSheet(
            "font-weight: 500; "
            "font-size: 16px; "
            "color: #2d2418; "
            "background: transparent;"
            );
        rowLayout->addWidget(nameLabel, 1);

        layout->addWidget(row);
    }

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
        delete item->widget();
        delete item;
    }

    m_currentInstructions = recipe.getInstructions();

    if (m_currentInstructions.isEmpty()) {
        QLabel *emptyLabel = new QLabel("Aucune instruction", instructionsContent);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #9ca3af; padding: 40px;");
        layout->addWidget(emptyLabel);
        layout->addStretch();
        return;
    }

    // Réinitialiser l'index
    m_currentInstructionIndex = 0;

    // ============ COMPTEUR ============
    QLabel *counterLabel = new QLabel(instructionsContent);
    counterLabel->setObjectName("counterLabel");
    counterLabel->setAlignment(Qt::AlignCenter);
    counterLabel->setStyleSheet(
        "font-size: 18px; "
        "font-weight: bold; "
        "color: #d97706; "
        "padding: 10px; "
        "background: transparent;"
        );
    layout->addWidget(counterLabel);

    // ============ ZONE D'INSTRUCTION ============
    QWidget *instructionZone = new QWidget(instructionsContent);
    instructionZone->setObjectName("instructionZone");
    instructionZone->setMinimumHeight(150);
    instructionZone->setStyleSheet(
        "QWidget#instructionZone { "
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #fef3c7, stop:1 #fde68a); "
        "  border: 3px solid #f59e0b; "
        "  border-radius: 12px; "
        "  padding: 24px; "
        "  margin: 20px 0; "
        "}"
        );

    QVBoxLayout *zoneLayout = new QVBoxLayout(instructionZone);
    zoneLayout->setSpacing(12);

    // Numéro + Texte
    QLabel *instructionLabel = new QLabel(instructionZone);
    instructionLabel->setObjectName("instructionLabel");
    instructionLabel->setWordWrap(true);
    instructionLabel->setTextFormat(Qt::RichText);
    instructionLabel->setStyleSheet(
        "font-size: 17px; "
        "line-height: 1.8; "
        "color: #2d2418; "
        "background: transparent;"
        );
    zoneLayout->addWidget(instructionLabel);

    layout->addWidget(instructionZone);

    // ============ BOUTONS DE NAVIGATION ============
    QWidget *navWidget = new QWidget(instructionsContent);
    QHBoxLayout *navLayout = new QHBoxLayout(navWidget);
    navLayout->setSpacing(20);
    navLayout->setContentsMargins(0, 20, 0, 20);

    QPushButton *btnPrev = new QPushButton("← Précédent", navWidget);
    btnPrev->setObjectName("btnPrev");
    btnPrev->setMinimumHeight(45);
    btnPrev->setCursor(Qt::PointingHandCursor);

    QPushButton *btnNext = new QPushButton("Suivant →", navWidget);
    btnNext->setObjectName("btnNext");
    btnNext->setMinimumHeight(45);
    btnNext->setCursor(Qt::PointingHandCursor);

    QString btnStyle =
        "QPushButton { "
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #f59e0b, stop:1 #d97706); "
        "  color: white; "
        "  border: none; "
        "  border-radius: 8px; "
        "  padding: 12px 32px; "
        "  font-size: 15px; "
        "  font-weight: bold; "
        "} "
        "QPushButton:hover { "
        "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #d97706, stop:1 #b45309); "
        "} "
        "QPushButton:pressed { "
        "  background: #92400e; "
        "} "
        "QPushButton:disabled { "
        "  background: #d1d5db; "
        "  color: #9ca3af; "
        "}";

    btnPrev->setStyleSheet(btnStyle);
    btnNext->setStyleSheet(btnStyle);

    navLayout->addWidget(btnPrev);
    navLayout->addStretch();
    navLayout->addWidget(btnNext);

    layout->addWidget(navWidget);
    layout->addStretch();

    // ============ CONNEXIONS ============
    connect(btnPrev, &QPushButton::clicked, this, [=]() {
        if (m_currentInstructionIndex > 0) {
            m_currentInstructionIndex--;
            updateInstructionDisplay();
        }
    });

    connect(btnNext, &QPushButton::clicked, this, [=]() {
        if (m_currentInstructionIndex < m_currentInstructions.size() - 1) {
            m_currentInstructionIndex++;
            updateInstructionDisplay();
        }
    });

    // Afficher la première instruction
    updateInstructionDisplay();
}

void MainWindow::updateInstructionDisplay()
{
    QWidget *instructionsContent = ui->instructionsContent;

    // Récupérer les widgets
    QLabel *counterLabel = instructionsContent->findChild<QLabel*>("counterLabel");
    QLabel *instructionLabel = instructionsContent->findChild<QLabel*>("instructionLabel");
    QPushButton *btnPrev = instructionsContent->findChild<QPushButton*>("btnPrev");
    QPushButton *btnNext = instructionsContent->findChild<QPushButton*>("btnNext");

    if (!counterLabel || !instructionLabel || !btnPrev || !btnNext) return;

    // Mettre à jour le compteur
    counterLabel->setText(QString("Étape %1 sur %2")
                              .arg(m_currentInstructionIndex + 1)
                              .arg(m_currentInstructions.size()));

    // Mettre à jour le texte de l'instruction
    QSharedPointer<Instruction> inst = m_currentInstructions[m_currentInstructionIndex];
    QString texte;

    if (inst->estSimple()) {
        texte = QString("<div style='font-size: 20px;'>"
                        "<span style='color: #f59e0b; font-weight: bold; font-size: 28px;'>%1.</span> "
                        "%2"
                        "</div>")
                    .arg(m_currentInstructionIndex + 1)
                    .arg(inst->afficher());
    } else {
        QSharedPointer<InstructionComposee> composee = inst.staticCast<InstructionComposee>();
        texte = QString("<div style='font-size: 20px;'>"
                        "<span style='color: #f59e0b; font-weight: bold; font-size: 28px;'>%1.</span> "
                        "<span style='font-weight: bold;'>📌 %2</span>"
                        "</div>")
                    .arg(m_currentInstructionIndex + 1)
                    .arg(composee->getTitre());

        const QList<QSharedPointer<Instruction>> &enfants = composee->getEnfants();
        if (!enfants.isEmpty()) {
            texte += "<div style='margin-left: 30px; margin-top: 15px;'>";
            for (int i = 0; i < enfants.size(); ++i) {
                if (!enfants[i].isNull() && enfants[i]->estSimple()) {
                    texte += QString("<div style='margin: 8px 0;'>• %1</div>")
                                 .arg(enfants[i]->afficher());
                }
            }
            texte += "</div>";
        }
    }

    instructionLabel->setText(texte);

    // Mettre à jour l'état des boutons
    btnPrev->setEnabled(m_currentInstructionIndex > 0);
    btnNext->setEnabled(m_currentInstructionIndex < m_currentInstructions.size() - 1);
}


void MainWindow::on_btnAddIngredient_clicked()
{
    if (m_selectedRecipeId < 0) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une recette d'abord");
        return;
    }

    AjouterIngredientDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) {
        QString nom = dlg.getNom();
        float qte = dlg.getQuantite();
        QString unite = dlg.getUnite();

        backend->ajouterIngredientARecette(m_selectedRecipeId, nom, qte, unite);

        Recette recette = backend->obtenirRecetteComplete(m_selectedRecipeId);
        displayRecipeDetails(recette);

        QMessageBox::information(this, "Succès",
                                 QString("Ingrédient '%1' ajouté avec succès").arg(nom));
    }
}

void MainWindow::on_btnAddInstruction_clicked()
{
    if (m_selectedRecipeId < 0) {
        QMessageBox::information(this, "Info", "Veuillez sélectionner une recette d'abord");
        return;
    }

    AjouterInstructionDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) {
        QString contenu = dlg.getContenu();
        int parentId = -1;

        if (dlg.estComposee()) {
            int instructionId = backend->ajouterInstructionComposee(
                m_selectedRecipeId,
                parentId,
                contenu
                );

            QMessageBox::information(this, "Succès",
                                     QString("Instruction composée '%1' ajoutée (ID: %2)").arg(contenu).arg(instructionId));
        } else {
            backend->ajouterInstructionSimple(
                m_selectedRecipeId,
                parentId,
                contenu
                );

            QMessageBox::information(this, "Succès",
                                     QString("Instruction '%1' ajoutée").arg(contenu));
        }

        Recette recette = backend->obtenirRecetteComplete(m_selectedRecipeId);
        displayRecipeDetails(recette);
    }
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

void MainWindow::on_actionRenitialiser_triggered()
{
    backend->insererRecettesTest();
}

void MainWindow::onRecetteSelectionChanged(const QItemSelection &selected, const QItemSelection &)
{
    if (!m_proxyModel || selected.indexes().isEmpty())
        return;

    QModelIndex proxyIndex = selected.indexes().first();
    QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);

    auto sourceModel = qobject_cast<RecetteTableModel*>(m_proxyModel->sourceModel());
    if (!sourceModel)
        return;

    int row = sourceIndex.row();
    Recette r = sourceModel->recetteAt(row);

    ui->titleLineEdit->setText(r.getTitre());
    ui->descriptionTextEdit->setPlainText(r.getDescription());

    auto ingredients = backend->ingredientsDeRecette(r.getId());
    m_ingredientModel.setRecetteIngredients(ingredients);

    backend->chargerInstructionsDansModele(m_instructionModel, r.getId());
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    if (m_proxyModel) {
        m_proxyModel->setFilterRegularExpression(QRegularExpression::escape(text));
    }
}
