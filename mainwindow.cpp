#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterrecettedialog.h"
#include "metiersHeader/recetteingredient.h"
#include "metiersHeader/instructioncomposee.h"
#include "metiersHeader/unite.h"
#include "ajouteringredientdialog.h"
#include "ajouterinstructiondialog.h"
#include "ImageDropLabel.h"
#include <QVBoxLayout>
#include <QRegularExpression>
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
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileDialog>
#include <QFileInfo>
#include <QActionGroup>
#include <QEvent>
#include <QTranslator>
#include <QSettings>
#include <QMenu>


MainWindow::MainWindow(Backend *backend, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , backend(backend)
    , m_ingredientModel(this)
    , m_instructionModel(backend->instructionService())
    , m_proxyModel(nullptr)          // Déplacé ici
    , m_selectedRecipeId(-1)         // Déplacé ici
{

    ui->setupUi(this);

    QSettings settings("VotreCompagnie", "RecettesApp");
    QString language = settings.value("language", "fr").toString(); // "fr" par défaut
    loadLanguage(language);

    // Setup proxy model for filtering
    RecetteTableModel *sourceModel = backend->recetteModel();
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(sourceModel);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    m_proxyModel->setFilterKeyColumn(-1);
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

    // Connect search
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &MainWindow::onSearchTextChanged);

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
    connect(m_updateTimer, &QTimer::timeout,
            this, &MainWindow::updateRecipeDetails);

    connect(ui->recipeTitleEdit, &QLineEdit::textChanged, this, [this]() {
        m_updateTimer->start(); // Redémarrer le timer à chaque changement
    });
    connect(ui->recipeDescriptionEdit, &QTextEdit::textChanged, this, [this]() {
        m_updateTimer->start();
    });

    // Load recipes
    backend->chargerRecettes();
    if (sourceModel) {
        connect(backend, &Backend::recettesModifiees,
                sourceModel, &RecetteTableModel::recharger);
    }

    // Réagir à la sélection d'une recette pour afficher les détails
    if (ui->tableViewRecettes->selectionModel()) {
        connect(ui->tableViewRecettes->selectionModel(),
                &QItemSelectionModel::selectionChanged,
                this, &MainWindow::onRecetteSelectionChanged);
    }

    // Sélectionner la première recette si disponible
    if (m_proxyModel && m_proxyModel->rowCount() > 0) {
        ui->tableViewRecettes->selectRow(0);
    }

    refreshRecipeList();

    // Show empty state initially
    clearRecipeDetails();

    // Créer le menu de langue
    setupLanguageMenu();
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

QPushButton* MainWindow::createRecipeCard(const Recette &recipe, int &index)
{
    QPushButton *card = new QPushButton(ui->recipeListContainer);
    card->setObjectName(QString("recipeCard_%1").arg(recipe.getId()));
    card->setCheckable(true);
    card->setChecked(recipe.getId() == m_selectedRecipeId);
    card->setMinimumHeight(110);
    card->setMaximumHeight(140);
    card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // Layout principal avec marges généreuses
    QHBoxLayout *cardLayout = new QHBoxLayout(card);
    cardLayout->setContentsMargins(16, 16, 16, 16);
    cardLayout->setSpacing(16);

    // ========== THUMBNAIL ==========
    QLabel *thumbnail = new QLabel(card);
    thumbnail->setFixedSize(70, 70);
    thumbnail->setScaledContents(false);
    thumbnail->setAlignment(Qt::AlignCenter);

    // Style pour le thumbnail
    thumbnail->setStyleSheet(
        "QLabel { "
        "  background: #f5f2e8; "
        "  border-radius: 8px; "
        "  border: 1px solid #e5ddd0; "
        "}"
        );

    if (!recipe.getPhoto().isEmpty()) {
        QPixmap pixmap(recipe.getPhoto());
        if (!pixmap.isNull()) {
            // Centrer l'image sans déformation
            QPixmap scaled = pixmap.scaled(70, 70, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

            // Crop au centre si nécessaire
            if (scaled.width() > 70 || scaled.height() > 70) {
                int x = (scaled.width() - 70) / 2;
                int y = (scaled.height() - 70) / 2;
                scaled = scaled.copy(x, y, 70, 70);
            }

            thumbnail->setPixmap(scaled);
            thumbnail->setStyleSheet(
                "QLabel { "
                "  background: transparent; "
                "  border: none; "
                "  border-radius: 8px; "
                "}"
                );
        } else {
            thumbnail->setText("📷");
            thumbnail->setStyleSheet(
                "QLabel { "
                "  background: #f5f2e8; "
                "  border-radius: 8px; "
                "  border: 1px solid #e5ddd0; "
                "  font-size: 28px; "
                "  color: #9ca3af; "
                "}"
                );
        }
    } else {
        thumbnail->setText("📷");
        thumbnail->setStyleSheet(
            "QLabel { "
            "  background: #f5f2e8; "
            "  border-radius: 8px; "
            "  border: 1px solid #e5ddd0; "
            "  font-size: 28px; "
            "  color: #9ca3af; "
            "}"
            );
    }

    cardLayout->addWidget(thumbnail);

    // ========== CONTENT (Titre + Description) ==========
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setSpacing(6);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // Titre - GRAS et visible
    QLabel *titleLabel = new QLabel(recipe.getTitre(), card);
    titleLabel->setStyleSheet(
        "QLabel { "
        "  font-weight: 700; "
        "  font-size: 16px; "
        "  color: #2d2418; "
        "  background: transparent; "
        "}"
        );
    titleLabel->setWordWrap(true);
    contentLayout->addWidget(titleLabel);

    // Description - 3 lignes visibles comme dans l'image
    QString desc = recipe.getDescription();
    if (desc.length() > 80) {
        desc = desc.left(80) + "...";
    }

    QLabel *descLabel = new QLabel(desc, card);
    descLabel->setStyleSheet(
        "QLabel { "
        "  font-size: 13px; "
        "  color: #6b7280; "
        "  background: transparent; "
        "  line-height: 1.4; "
        "}"
        );
    descLabel->setWordWrap(true);
    descLabel->setMinimumHeight(45); // Assurer 3 lignes
    descLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    contentLayout->addWidget(descLabel);

    // Ajouter stretch pour pousser le contenu vers le haut
    contentLayout->addStretch();

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

    // Afficher l'image dans l'onglet Détails
    displayRecipeImage(recipe.getPhoto());

    // Afficher les ingrédients
    displayIngredients(recipe);

    // Afficher les instructions
    displayInstructions(recipe);

    // Update stats
    int ingredientCount = recipe.getIngredients().size();
    int instructionCount = recipe.getNombreInstructions();
    ui->timeLabel->setText(tr("%1 ingrédients").arg(ingredientCount));
    ui->servingsLabel->setText(tr("%1 instructions").arg(instructionCount));

    // Enable delete button
    ui->btnDeleteRecipe->setEnabled(true);
}

void MainWindow::clearRecipeDetails()
{
    ui->recipeTitleEdit->clear();
    ui->recipeDescriptionEdit->clear();
    ui->timeLabel->setText(tr("0 min total"));
    ui->servingsLabel->setText(tr("0 portions"));
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

    int ret = QMessageBox::question(this, tr("Supprimer"),
                                    tr("Voulez-vous vraiment supprimer cette recette ?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        bool success = backend->supprimerRecette(m_selectedRecipeId);
        if (success) {
            refreshRecipeList();
            clearRecipeDetails();
        } else {
            QMessageBox::warning(this, tr("Erreur"),
                                 tr("Impossible de supprimer la recette"));
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
        QLabel *emptyLabel = new QLabel(tr("Aucun ingrédient"), ingredientsContent);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #9ca3af; padding: 40px; background: transparent;");
        layout->addWidget(emptyLabel);
        layout->addStretch();
        return;
    }

    // Ajouter les ingrédients un par un (sans cadre global)
    for (int i = 0; i < ingredients.size(); ++i) {
        const RecetteIngredient &ri = ingredients[i];

        QWidget *row = new QWidget(ingredientsContent);
        row->setObjectName(QString("ingredient_%1").arg(i));
        row->setMinimumHeight(50);
        row->setMaximumHeight(65);

        // Style élégant sans bordure
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

        // Quantité + Unité ensemble (plus compact)
        QWidget *qteContainer = new QWidget(row);
        qteContainer->setFixedWidth(140);
        QHBoxLayout *qteLayout = new QHBoxLayout(qteContainer);
        qteLayout->setContentsMargins(0, 0, 0, 0);
        qteLayout->setSpacing(8);

        // Quantité
        QLabel *qteLabel = new QLabel(QString::number(ri.getQuantite()), qteContainer);
        qteLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        qteLabel->setStyleSheet(
            "font-weight: 700; "
            "font-size: 18px; "
            "color: #d97706; "
            "background: transparent;"
            );
        qteLayout->addWidget(qteLabel);

        // Unité
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

        // Nom de l'ingrédient (plus grand, plus lisible)
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
        if (item->widget() && item->widget()->objectName().startsWith("instruction_")) {
            delete item->widget();
        }
        delete item;
    }

    const QList<QSharedPointer<Instruction>> &instructions = recipe.getInstructions();

    qDebug() << "📝 [DISPLAY] Affichage de" << instructions.size() << "instructions";

    if (instructions.isEmpty()) {
        QLabel *emptyLabel = new QLabel(tr("Aucune instruction"), instructionsContent);
        emptyLabel->setAlignment(Qt::AlignCenter);
        emptyLabel->setStyleSheet("color: #9ca3af; padding: 40px; background: transparent;");
        layout->addWidget(emptyLabel);
        layout->addStretch();
        return;
    }

    // Ajouter les instructions avec un meilleur design
    int order = 1;
    for (const QSharedPointer<Instruction> &inst : instructions) {
        if (inst.isNull()) {
            qWarning() << "   ⚠️ Instruction nulle ignorée";
            continue;
        }

        QWidget *instWidget = new QWidget(instructionsContent);
        instWidget->setObjectName(QString("instruction_%1").arg(order));
        instWidget->setStyleSheet(
            "QWidget#instruction_" + QString::number(order) + " { "
                                                              "  background: #ffffff; "
                                                              "  border: 1px solid #e5ddd0; "
                                                              "  border-radius: 8px; "
                                                              "  padding: 16px; "
                                                              "  margin-bottom: 12px; "
                                                              "}"
                                                              "QWidget#instruction_" + QString::number(order) + ":hover { "
                                       "  background: #fefcf8; "
                                       "  border-color: #d97706; "
                                       "}"
            );

        QHBoxLayout *instLayout = new QHBoxLayout(instWidget);
        instLayout->setContentsMargins(12, 12, 12, 12);
        instLayout->setSpacing(16);

        // Numéro d'ordre avec style moderne
        QLabel *orderLabel = new QLabel(QString::number(order), instWidget);
        orderLabel->setFixedSize(40, 40);
        orderLabel->setAlignment(Qt::AlignCenter);
        orderLabel->setStyleSheet(
            "QLabel { "
            "  background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
            "    stop:0 #f59e0b, stop:1 #d97706); "
            "  color: white; "
            "  border-radius: 20px; "
            "  font-weight: bold; "
            "  font-size: 16px; "
            "}"
            );
        instLayout->addWidget(orderLabel);

        // Contenu de l'instruction
        QLabel *contentLabel = new QLabel(instWidget);
        contentLabel->setWordWrap(true);
        contentLabel->setTextFormat(Qt::PlainText);
        contentLabel->setStyleSheet(
            "QLabel { "
            "  color: #2d2418; "
            "  font-size: 15px; "
            "  line-height: 1.6; "
            "  background: transparent; "
            "  padding: 4px; "
            "}"
            );

        QString texte;
        if (inst->estSimple()) {
            // Instruction simple - utiliser afficher() qui retourne m_titre
            texte = inst->afficher();
            qDebug() << "   ✓ Instruction" << order << "(simple):" << texte;
        } else {
            // Instruction composée
            QSharedPointer<InstructionComposee> composee = inst.staticCast<InstructionComposee>();
            texte = "📌 " + composee->getTitre();
            qDebug() << "   ✓ Instruction" << order << "(composée):" << composee->getTitre();

            // Ajouter les sous-instructions
            const QList<QSharedPointer<Instruction>> &enfants = composee->getEnfants();
            if (!enfants.isEmpty()) {
                texte += "\n";
                for (int i = 0; i < enfants.size(); ++i) {
                    if (!enfants[i].isNull() && enfants[i]->estSimple()) {
                        QString sousTexte = enfants[i]->afficher();
                        texte += QString("\n  %1. %2").arg(i + 1).arg(sousTexte);
                    }
                }
            }
        }

        if (texte.isEmpty()) {
            texte = "⚠️ Contenu manquant";
            qWarning() << "   ️ Texte vide pour instruction" << order;
        }

        contentLabel->setText(texte);
        instLayout->addWidget(contentLabel, 1);

        layout->addWidget(instWidget);
        order++;
    }

    qDebug() << "✅ [DISPLAY]" << (order - 1) << "instructions affichées";

    // Ajouter un espacement à la fin
    layout->addStretch();
}


// Dans mainwindow.cpp, modifiez displayRecipeImage :

void MainWindow::displayRecipeImage(const QString &photoUrl)
{
    m_currentPhotoUrl = photoUrl;

    QWidget *detailsContent = ui->detailsContent;
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(detailsContent->layout());
    if (!layout) return;

    // Chercher si une image existe déjà
    ImageDropLabel *imageLabel = detailsContent->findChild<ImageDropLabel*>("recipeImageLabel");
    QLineEdit *photoUrlEdit = detailsContent->findChild<QLineEdit*>("photoUrlEdit");
    QPushButton *browseBtn = detailsContent->findChild<QPushButton*>("browsePhotoBtn");

    if (!imageLabel) {
        // Créer le label d'image avec drag & drop
        imageLabel = new ImageDropLabel(detailsContent);
        imageLabel->setObjectName("recipeImageLabel");
        imageLabel->setText("📷\n\nGlissez une image ici\nou cliquez sur Parcourir");
        imageLabel->setMinimumHeight(200);
        imageLabel->setMaximumHeight(300);

        // Connecter le signal de drop - AVEC SAUVEGARDE
        connect(imageLabel, &ImageDropLabel::imageDropped, this, [this](const QString &filePath) {
            // 🔥 SAUVEGARDER L'IMAGE DANS LE DOSSIER DE L'APP
            QString cheminSauvegarde = backend->sauvegarderImage(filePath);

            if (cheminSauvegarde.isEmpty()) {
                QMessageBox::warning(this, "Erreur", "Impossible de sauvegarder l'image");
                return;
            }

            m_currentPhotoUrl = cheminSauvegarde;

            QLineEdit *edit = ui->detailsContent->findChild<QLineEdit*>("photoUrlEdit");
            if (edit) edit->setText(cheminSauvegarde);

            // Mettre à jour l'affichage
            ImageDropLabel *label = ui->detailsContent->findChild<ImageDropLabel*>("recipeImageLabel");
            if (label) {
                QPixmap pixmap(cheminSauvegarde);
                if (!pixmap.isNull()) {
                    label->setPixmap(pixmap.scaled(label->width(), 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    label->setStyleSheet("QLabel { background: transparent; border: none; border-radius: 12px; }");
                }
            }

            // Sauvegarder immédiatement
            QTimer::singleShot(500, this, &MainWindow::updateRecipeDetails);
        });

        layout->insertWidget(0, imageLabel);
    }

    if (!photoUrlEdit) {
        // Layout horizontal pour URL + bouton
        QWidget *urlWidget = new QWidget(detailsContent);
        QHBoxLayout *urlLayout = new QHBoxLayout(urlWidget);
        urlLayout->setContentsMargins(0, 0, 0, 0);
        urlLayout->setSpacing(8);

        // Champ URL (en lecture seule pour éviter les erreurs)
        photoUrlEdit = new QLineEdit(urlWidget);
        photoUrlEdit->setObjectName("photoUrlEdit");
        photoUrlEdit->setPlaceholderText("Chemin de l'image...");
        photoUrlEdit->setReadOnly(true); // Lecture seule
        photoUrlEdit->setStyleSheet(
            "QLineEdit { "
            "  background: #f5f2e8; "
            "  border: 1px solid #e5ddd0; "
            "  border-radius: 8px; "
            "  padding: 10px 12px; "
            "  color: #6b7280; "
            "}"
            );
        urlLayout->addWidget(photoUrlEdit, 1);

        // Bouton parcourir
        browseBtn = new QPushButton("📁 Parcourir", urlWidget);
        browseBtn->setObjectName("browsePhotoBtn");
        browseBtn->setFixedWidth(120);
        connect(browseBtn, &QPushButton::clicked, this, [this, photoUrlEdit]() {
            QString filePath = QFileDialog::getOpenFileName(
                this,
                "Choisir une image",
                QDir::homePath(),
                "Images (*.png *.jpg *.jpeg *.gif *.bmp *.webp)"
                );

            if (!filePath.isEmpty()) {
                // 🔥 SAUVEGARDER L'IMAGE
                QString cheminSauvegarde = backend->sauvegarderImage(filePath);

                if (cheminSauvegarde.isEmpty()) {
                    QMessageBox::warning(this, "Erreur", "Impossible de sauvegarder l'image");
                    return;
                }

                m_currentPhotoUrl = cheminSauvegarde;
                photoUrlEdit->setText(cheminSauvegarde);

                // Afficher l'image
                ImageDropLabel *label = ui->detailsContent->findChild<ImageDropLabel*>("recipeImageLabel");
                if (label) {
                    QPixmap pixmap(cheminSauvegarde);
                    if (!pixmap.isNull()) {
                        label->setPixmap(pixmap.scaled(label->width(), 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                        label->setStyleSheet("QLabel { background: transparent; border: none; border-radius: 12px; }");
                    }
                }

                // Sauvegarder
                QTimer::singleShot(500, this, &MainWindow::updateRecipeDetails);
            }
        });
        urlLayout->addWidget(browseBtn);

        layout->insertWidget(1, urlWidget);
    }

    photoUrlEdit->setText(photoUrl);

    // Afficher l'image
    if (!photoUrl.isEmpty()) {
        QPixmap pixmap(photoUrl);
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap.scaled(imageLabel->width(), 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
            imageLabel->setStyleSheet("QLabel { background: transparent; border: none; border-radius: 12px; }");
        } else {
            imageLabel->clear();
            imageLabel->setText("📷\nImage introuvable");
            imageLabel->setStyleSheet(
                "QLabel { "
                "  background: rgba(245, 242, 232, 0.3); "
                "  border: 2px dashed #e5ddd0; "
                "  border-radius: 12px; "
                "  color: #dc2626; "
                "}"
                );
        }
    } else {
        imageLabel->clear();
        imageLabel->setText(tr("📷\n\nGlissez une image ici\nou cliquez sur Parcourir"));
        imageLabel->setStyleSheet(
            "QLabel { "
            "  background: rgba(245, 242, 232, 0.3); "
            "  border: 2px dashed #e5ddd0; "
            "  border-radius: 12px; "
            "  color: #6b7280; "
            "}"
            );
    }
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

        // Récupérer la recette mise à jour (par valeur)
        Recette recette = backend->obtenirRecetteComplete(m_selectedRecipeId);
        displayRecipeDetails(recette);

        QMessageBox::information(this, tr("Succès"),
                                 tr(("Ingrédient '%1' ajouté avec succès")).arg(nom));
    }
}



void MainWindow::on_btnAddInstruction_clicked()
{
    if (m_selectedRecipeId < 0) {
        QMessageBox::information(this, tr("Info"), tr("Veuillez sélectionner une recette d'abord"));
        return;
    }

    AjouterInstructionDialog dlg(this);

    if (dlg.exec() == QDialog::Accepted) {
        QString contenu = dlg.getContenu();
        int parentId = -1;  // Instruction au niveau racine par défaut

        if (dlg.estComposee()) {
            // Ajouter une instruction composée
            int instructionId = backend->ajouterInstructionComposee(
                m_selectedRecipeId,
                parentId,
                contenu
                );

            QMessageBox::information(this, "Succès",
                                     QString("Instruction composée '%1' ajoutée (ID: %2)").arg(contenu).arg(instructionId));
        } else {
            // Ajouter une instruction simple
            backend->ajouterInstructionSimple(
                m_selectedRecipeId,
                parentId,
                contenu
                );

            QMessageBox::information(this, "Succès",
                                     QString("Instruction '%1' ajoutée").arg(contenu));
        }

        // Rafraîchir l'affichage
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



// Nouvelle méthode : Charger une langue
// Charger la langue au démarrage
void MainWindow::loadLanguage(const QString &language)
{
    // Retirer l'ancien traducteur si présent
    qApp->removeTranslator(&m_translator);

    QString qmPath;
    if (language == "fr") qmPath = ":/RecettesIntelligentes_fr_FR.qm";
    else if (language == "en") qmPath = ":/RecettesIntelligentes_en_AS.qm";
    else {
        qWarning() << "Langue inconnue:" << language;
        return;
    }

    if (m_translator.load(qmPath)) {
        qApp->installTranslator(&m_translator);
        m_currentLanguage = language;

        // Sauvegarder la préférence
        QSettings settings("VotreCompagnie", "RecettesApp");
        settings.setValue("language", language);

        qDebug() << "✓ Langue chargée:" << language;
    } else {
        qWarning() << "⚠️ Impossible de charger" << qmPath;
    }
}

// Changer la langue dynamiquement via menu
void MainWindow::changeLanguage(const QString &language)
{
    if (m_currentLanguage == language) return;

    qApp->removeTranslator(&m_translator);

    QString qmPath;
    if (language == "fr") qmPath = ":/RecettesIntelligentes_fr_FR.qm";
    else if (language == "en") qmPath = ":/RecettesIntelligentes_en_AS.qm";
    else {
        qWarning() << "Langue inconnue:" << language;
        return;
    }

    if (m_translator.load(qmPath)) {
        qApp->installTranslator(&m_translator);
        m_currentLanguage = language;

        QSettings settings("VotreCompagnie", "RecettesApp");
        settings.setValue("language", language);

        // Qt va émettre automatiquement QEvent::LanguageChange
        // Donc changeEvent() appellera ui->retranslateUi()
    } else {
        qWarning() << "Impossible de charger" << qmPath;
    }
}

// Mettre à jour les textes dynamiques (labels, boutons créés dynamiquement)
void MainWindow::retranslateUi()
{
    if (m_selectedRecipeId >= 0) {
        Recette recette = backend->obtenirRecetteComplete(m_selectedRecipeId);
        int ingredientCount = recette.getIngredients().size();
        int instructionCount = recette.getNombreInstructions();

        ui->timeLabel->setText(tr("%1 ingrédients").arg(ingredientCount));
        ui->servingsLabel->setText(tr("%1 instructions").arg(instructionCount));
    }

    if (ui->searchLineEdit->text().isEmpty()) {
        ui->searchLineEdit->setPlaceholderText(tr("Rechercher une recette..."));
    }
}

// Mettre à jour le menu de langue
void MainWindow::retranslateLanguageMenu()
{
    if (actionFrancais) actionFrancais->setText(tr("Français"));
    if (actionEnglish) actionEnglish->setText(tr("English"));
}

// Créer le menu de langue
void MainWindow::setupLanguageMenu()
{
    QActionGroup *languageGroup = new QActionGroup(this);
    languageGroup->setExclusive(true);

    actionFrancais = new QAction(tr("Français"), this);
    actionFrancais->setCheckable(true);
    actionFrancais->setData("fr");

    actionEnglish = new QAction(tr("English"), this);
    actionEnglish->setCheckable(true);
    actionEnglish->setData("en");

    languageGroup->addAction(actionFrancais);
    languageGroup->addAction(actionEnglish);

    ui->menuLangue->addAction(actionFrancais);
    ui->menuLangue->addAction(actionEnglish);

    actionFrancais->setChecked(m_currentLanguage == "fr");
    actionEnglish->setChecked(m_currentLanguage == "en");

    connect(languageGroup, &QActionGroup::triggered, this,
            [this](QAction *action) {
                changeLanguage(action->data().toString());
            });
}

// Gérer l'événement LanguageChange
void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);        // widgets du .ui
        retranslateUi();                 // éléments dynamiques
        retranslateLanguageMenu();       // menu langue
    }
    QMainWindow::changeEvent(event);
}
