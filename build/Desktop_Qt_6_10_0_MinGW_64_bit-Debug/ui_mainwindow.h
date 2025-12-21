/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouveau;
    QAction *actionOuvrir;
    QAction *actionSauvegarder;
    QAction *actionExporter;
    QAction *actionQuitter;
    QAction *actionEdit;
    QAction *actionDelete;
    QAction *actionRecherche;
    QAction *actionSideBar;
    QAction *actionRenitialiser;
    QAction *actionFran_ais;
    QAction *actionEnglish;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *headerLayout;
    QLabel *sidebarTitle;
    QLineEdit *searchLineEdit;
    QScrollArea *recipeScrollArea;
    QWidget *recipeListContainer;
    QVBoxLayout *recipeListLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *footerLayout;
    QPushButton *btnAddRecipe;
    QPushButton *btnDeleteRecipe;
    QTableView *tableViewRecettes;
    QVBoxLayout *detailLayout;
    QVBoxLayout *detailHeaderLayout;
    QLineEdit *recipeTitleEdit;
    QTextEdit *recipeDescriptionEdit;
    QWidget *recipeStatsWidget;
    QHBoxLayout *statsLayout;
    QLabel *timeLabel;
    QLabel *servingsLabel;
    QSpacerItem *horizontalSpacer;
    QTabWidget *recipeTabs;
    QWidget *detailsTab;
    QVBoxLayout *detailsTabLayout;
    QScrollArea *detailsScrollArea;
    QWidget *detailsContent;
    QVBoxLayout *detailsContentLayout;
    QSpacerItem *verticalSpacer_2;
    QWidget *ingredientsTab;
    QVBoxLayout *ingredientsTabLayout;
    QScrollArea *ingredientsScrollArea;
    QWidget *ingredientsContent;
    QVBoxLayout *ingredientsContentLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *btnAddIngredient;
    QWidget *tab1;
    QVBoxLayout *verticalLayout_6;
    QTableView *ingredientTable;
    QWidget *instructionsTab;
    QVBoxLayout *instructionsTabLayout;
    QScrollArea *instructionsScrollArea;
    QWidget *instructionsContent;
    QVBoxLayout *instructionsContentLayout;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnAddInstruction;
    QWidget *tab2;
    QVBoxLayout *verticalLayout_7;
    QListWidget *instructionList;
    QWidget *navigation;
    QWidget *widget;
    QWidget *hiddenCompatibilityWidget;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *titleLineEdit;
    QTextEdit *descriptionTextEdit;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAffiche;
    QMenu *menuLangue;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1217, 700);
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName("actionNouveau");
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName("actionOuvrir");
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName("actionSauvegarder");
        actionExporter = new QAction(MainWindow);
        actionExporter->setObjectName("actionExporter");
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName("actionQuitter");
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName("actionEdit");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionRecherche = new QAction(MainWindow);
        actionRecherche->setObjectName("actionRecherche");
        actionSideBar = new QAction(MainWindow);
        actionSideBar->setObjectName("actionSideBar");
        actionRenitialiser = new QAction(MainWindow);
        actionRenitialiser->setObjectName("actionRenitialiser");
        actionFran_ais = new QAction(MainWindow);
        actionFran_ais->setObjectName("actionFran_ais");
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName("actionEnglish");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(24);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(16, 16, 16, 16);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        headerLayout = new QVBoxLayout();
        headerLayout->setSpacing(12);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(16, 16, 16, 16);
        sidebarTitle = new QLabel(centralwidget);
        sidebarTitle->setObjectName("sidebarTitle");
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        sidebarTitle->setFont(font);

        headerLayout->addWidget(sidebarTitle);

        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName("searchLineEdit");

        headerLayout->addWidget(searchLineEdit);


        verticalLayout_2->addLayout(headerLayout);

        recipeScrollArea = new QScrollArea(centralwidget);
        recipeScrollArea->setObjectName("recipeScrollArea");
        recipeScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        recipeScrollArea->setWidgetResizable(true);
        recipeListContainer = new QWidget();
        recipeListContainer->setObjectName("recipeListContainer");
        recipeListContainer->setGeometry(QRect(0, 0, 330, 423));
        recipeListLayout = new QVBoxLayout(recipeListContainer);
        recipeListLayout->setSpacing(8);
        recipeListLayout->setObjectName("recipeListLayout");
        recipeListLayout->setContentsMargins(12, 8, 12, 8);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        recipeListLayout->addItem(verticalSpacer);

        recipeScrollArea->setWidget(recipeListContainer);

        verticalLayout_2->addWidget(recipeScrollArea);

        footerLayout = new QHBoxLayout();
        footerLayout->setSpacing(8);
        footerLayout->setObjectName("footerLayout");
        footerLayout->setContentsMargins(12, 12, 12, 12);
        btnAddRecipe = new QPushButton(centralwidget);
        btnAddRecipe->setObjectName("btnAddRecipe");

        footerLayout->addWidget(btnAddRecipe);

        btnDeleteRecipe = new QPushButton(centralwidget);
        btnDeleteRecipe->setObjectName("btnDeleteRecipe");

        footerLayout->addWidget(btnDeleteRecipe);


        verticalLayout_2->addLayout(footerLayout);

        tableViewRecettes = new QTableView(centralwidget);
        tableViewRecettes->setObjectName("tableViewRecettes");
        tableViewRecettes->setVisible(false);

        verticalLayout_2->addWidget(tableViewRecettes);


        horizontalLayout->addLayout(verticalLayout_2);

        detailLayout = new QVBoxLayout();
        detailLayout->setSpacing(0);
        detailLayout->setObjectName("detailLayout");
        detailLayout->setContentsMargins(0, 0, 0, 0);
        detailHeaderLayout = new QVBoxLayout();
        detailHeaderLayout->setSpacing(16);
        detailHeaderLayout->setObjectName("detailHeaderLayout");
        detailHeaderLayout->setContentsMargins(24, 24, 24, 24);
        recipeTitleEdit = new QLineEdit(centralwidget);
        recipeTitleEdit->setObjectName("recipeTitleEdit");
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        recipeTitleEdit->setFont(font1);

        detailHeaderLayout->addWidget(recipeTitleEdit);

        recipeDescriptionEdit = new QTextEdit(centralwidget);
        recipeDescriptionEdit->setObjectName("recipeDescriptionEdit");
        recipeDescriptionEdit->setMaximumSize(QSize(16777215, 100));

        detailHeaderLayout->addWidget(recipeDescriptionEdit);

        recipeStatsWidget = new QWidget(centralwidget);
        recipeStatsWidget->setObjectName("recipeStatsWidget");
        statsLayout = new QHBoxLayout(recipeStatsWidget);
        statsLayout->setSpacing(24);
        statsLayout->setObjectName("statsLayout");
        statsLayout->setContentsMargins(0, 0, 0, 0);
        timeLabel = new QLabel(recipeStatsWidget);
        timeLabel->setObjectName("timeLabel");

        statsLayout->addWidget(timeLabel);

        servingsLabel = new QLabel(recipeStatsWidget);
        servingsLabel->setObjectName("servingsLabel");

        statsLayout->addWidget(servingsLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statsLayout->addItem(horizontalSpacer);


        detailHeaderLayout->addWidget(recipeStatsWidget);


        detailLayout->addLayout(detailHeaderLayout);

        recipeTabs = new QTabWidget(centralwidget);
        recipeTabs->setObjectName("recipeTabs");
        detailsTab = new QWidget();
        detailsTab->setObjectName("detailsTab");
        detailsTabLayout = new QVBoxLayout(detailsTab);
        detailsTabLayout->setSpacing(0);
        detailsTabLayout->setObjectName("detailsTabLayout");
        detailsTabLayout->setContentsMargins(24, 24, 24, 24);
        detailsScrollArea = new QScrollArea(detailsTab);
        detailsScrollArea->setObjectName("detailsScrollArea");
        detailsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        detailsScrollArea->setWidgetResizable(true);
        detailsContent = new QWidget();
        detailsContent->setObjectName("detailsContent");
        detailsContent->setGeometry(QRect(0, 0, 775, 223));
        detailsContentLayout = new QVBoxLayout(detailsContent);
        detailsContentLayout->setSpacing(24);
        detailsContentLayout->setObjectName("detailsContentLayout");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        detailsContentLayout->addItem(verticalSpacer_2);

        detailsScrollArea->setWidget(detailsContent);

        detailsTabLayout->addWidget(detailsScrollArea);

        recipeTabs->addTab(detailsTab, QString());
        ingredientsTab = new QWidget();
        ingredientsTab->setObjectName("ingredientsTab");
        ingredientsTabLayout = new QVBoxLayout(ingredientsTab);
        ingredientsTabLayout->setSpacing(0);
        ingredientsTabLayout->setObjectName("ingredientsTabLayout");
        ingredientsTabLayout->setContentsMargins(24, 24, 24, 24);
        ingredientsScrollArea = new QScrollArea(ingredientsTab);
        ingredientsScrollArea->setObjectName("ingredientsScrollArea");
        ingredientsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        ingredientsScrollArea->setWidgetResizable(true);
        ingredientsContent = new QWidget();
        ingredientsContent->setObjectName("ingredientsContent");
        ingredientsContent->setGeometry(QRect(0, 0, 775, 194));
        ingredientsContentLayout = new QVBoxLayout(ingredientsContent);
        ingredientsContentLayout->setSpacing(8);
        ingredientsContentLayout->setObjectName("ingredientsContentLayout");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        ingredientsContentLayout->addItem(verticalSpacer_3);

        ingredientsScrollArea->setWidget(ingredientsContent);

        ingredientsTabLayout->addWidget(ingredientsScrollArea);

        btnAddIngredient = new QPushButton(ingredientsTab);
        btnAddIngredient->setObjectName("btnAddIngredient");

        ingredientsTabLayout->addWidget(btnAddIngredient);

        tab1 = new QWidget(ingredientsTab);
        tab1->setObjectName("tab1");
        tab1->setVisible(false);
        verticalLayout_6 = new QVBoxLayout(tab1);
        verticalLayout_6->setObjectName("verticalLayout_6");
        ingredientTable = new QTableView(tab1);
        ingredientTable->setObjectName("ingredientTable");
        ingredientTable->setVisible(false);

        verticalLayout_6->addWidget(ingredientTable);


        ingredientsTabLayout->addWidget(tab1);

        recipeTabs->addTab(ingredientsTab, QString());
        instructionsTab = new QWidget();
        instructionsTab->setObjectName("instructionsTab");
        instructionsTabLayout = new QVBoxLayout(instructionsTab);
        instructionsTabLayout->setSpacing(0);
        instructionsTabLayout->setObjectName("instructionsTabLayout");
        instructionsTabLayout->setContentsMargins(24, 24, 24, 24);
        instructionsScrollArea = new QScrollArea(instructionsTab);
        instructionsScrollArea->setObjectName("instructionsScrollArea");
        instructionsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        instructionsScrollArea->setWidgetResizable(true);
        instructionsContent = new QWidget();
        instructionsContent->setObjectName("instructionsContent");
        instructionsContent->setGeometry(QRect(0, 0, 775, 194));
        instructionsContentLayout = new QVBoxLayout(instructionsContent);
        instructionsContentLayout->setSpacing(12);
        instructionsContentLayout->setObjectName("instructionsContentLayout");
        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        instructionsContentLayout->addItem(verticalSpacer_4);

        instructionsScrollArea->setWidget(instructionsContent);

        instructionsTabLayout->addWidget(instructionsScrollArea);

        btnAddInstruction = new QPushButton(instructionsTab);
        btnAddInstruction->setObjectName("btnAddInstruction");

        instructionsTabLayout->addWidget(btnAddInstruction);

        tab2 = new QWidget(instructionsTab);
        tab2->setObjectName("tab2");
        tab2->setVisible(false);
        verticalLayout_7 = new QVBoxLayout(tab2);
        verticalLayout_7->setObjectName("verticalLayout_7");
        instructionList = new QListWidget(tab2);
        instructionList->setObjectName("instructionList");
        instructionList->setVisible(false);

        verticalLayout_7->addWidget(instructionList);

        navigation = new QWidget(tab2);
        navigation->setObjectName("navigation");
        navigation->setVisible(false);

        verticalLayout_7->addWidget(navigation);

        widget = new QWidget(tab2);
        widget->setObjectName("widget");
        widget->setVisible(false);

        verticalLayout_7->addWidget(widget);


        instructionsTabLayout->addWidget(tab2);

        recipeTabs->addTab(instructionsTab, QString());

        detailLayout->addWidget(recipeTabs);

        hiddenCompatibilityWidget = new QWidget(centralwidget);
        hiddenCompatibilityWidget->setObjectName("hiddenCompatibilityWidget");
        hiddenCompatibilityWidget->setVisible(false);
        verticalLayout_8 = new QVBoxLayout(hiddenCompatibilityWidget);
        verticalLayout_8->setObjectName("verticalLayout_8");
        titleLineEdit = new QLineEdit(hiddenCompatibilityWidget);
        titleLineEdit->setObjectName("titleLineEdit");

        verticalLayout_8->addWidget(titleLineEdit);

        descriptionTextEdit = new QTextEdit(hiddenCompatibilityWidget);
        descriptionTextEdit->setObjectName("descriptionTextEdit");

        verticalLayout_8->addWidget(descriptionTextEdit);


        detailLayout->addWidget(hiddenCompatibilityWidget);


        horizontalLayout->addLayout(detailLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1217, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName("menuEdit");
        menuAffiche = new QMenu(menuBar);
        menuAffiche->setObjectName("menuAffiche");
        menuLangue = new QMenu(menuAffiche);
        menuLangue->setObjectName("menuLangue");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuAffiche->menuAction());
        menuFile->addAction(actionNouveau);
        menuFile->addSeparator();
        menuFile->addAction(actionQuitter);
        menuEdit->addAction(actionDelete);
        menuEdit->addAction(actionRecherche);
        menuAffiche->addAction(actionSideBar);
        menuAffiche->addAction(actionRenitialiser);
        menuAffiche->addAction(menuLangue->menuAction());

        retranslateUi(MainWindow);

        recipeTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        actionNouveau->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        actionOuvrir->setText(QCoreApplication::translate("MainWindow", "Ouvrir", nullptr));
        actionSauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        actionExporter->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        actionEdit->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        actionRecherche->setText(QCoreApplication::translate("MainWindow", "Rechercher", nullptr));
        actionSideBar->setText(QCoreApplication::translate("MainWindow", "Barre lat\303\251rale", nullptr));
        actionRenitialiser->setText(QCoreApplication::translate("MainWindow", "R\303\251initialiser", nullptr));
        actionFran_ais->setText(QCoreApplication::translate("MainWindow", "Fran\303\247ais", nullptr));
        actionEnglish->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        sidebarTitle->setText(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher une recette...", nullptr));
        btnAddRecipe->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        btnDeleteRecipe->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        recipeTitleEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Titre de la recette", nullptr));
        recipeDescriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Description de la recette...", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "0 ingr\303\251dients", nullptr));
        servingsLabel->setText(QCoreApplication::translate("MainWindow", "0 instructions", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(detailsTab), QCoreApplication::translate("MainWindow", "D\303\251tails", nullptr));
        btnAddIngredient->setText(QCoreApplication::translate("MainWindow", "Ajouter un ingr\303\251dient", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(ingredientsTab), QCoreApplication::translate("MainWindow", "Ingr\303\251dients", nullptr));
        btnAddInstruction->setText(QCoreApplication::translate("MainWindow", "Ajouter une instruction", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(instructionsTab), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        titleLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Titre (compat)", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Description (compat)", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuAffiche->setTitle(QCoreApplication::translate("MainWindow", "Affichage", nullptr));
        menuLangue->setTitle(QCoreApplication::translate("MainWindow", "Langue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
