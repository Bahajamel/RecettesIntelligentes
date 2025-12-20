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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNouveau;
    QAction *actionFr;
    QAction *actionModifier;
    QAction *actionSauvegarder;
    QAction *actionQuitter;
    QAction *actionQuitter_2;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *sidebarLayout;
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
    QWidget *instructionsTab;
    QVBoxLayout *instructionsTabLayout;
    QScrollArea *instructionsScrollArea;
    QWidget *instructionsContent;
    QVBoxLayout *instructionsContentLayout;
    QSpacerItem *verticalSpacer_4;
    QPushButton *btnAddInstruction;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuLangage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1217, 900);
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName("actionNouveau");
        actionNouveau->setCheckable(true);
        actionFr = new QAction(MainWindow);
        actionFr->setObjectName("actionFr");
        actionModifier = new QAction(MainWindow);
        actionModifier->setObjectName("actionModifier");
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName("actionSauvegarder");
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName("actionQuitter");
        actionQuitter_2 = new QAction(MainWindow);
        actionQuitter_2->setObjectName("actionQuitter_2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(24);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(16, 16, 16, 16);
        sidebarLayout = new QVBoxLayout();
        sidebarLayout->setSpacing(0);
        sidebarLayout->setObjectName("sidebarLayout");
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


        sidebarLayout->addLayout(headerLayout);

        recipeScrollArea = new QScrollArea(centralwidget);
        recipeScrollArea->setObjectName("recipeScrollArea");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(recipeScrollArea->sizePolicy().hasHeightForWidth());
        recipeScrollArea->setSizePolicy(sizePolicy);
        recipeScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        recipeScrollArea->setFrameShadow(QFrame::Shadow::Plain);
        recipeScrollArea->setWidgetResizable(true);
        recipeListContainer = new QWidget();
        recipeListContainer->setObjectName("recipeListContainer");
        recipeListContainer->setGeometry(QRect(0, 0, 330, 647));
        recipeListLayout = new QVBoxLayout(recipeListContainer);
        recipeListLayout->setSpacing(8);
        recipeListLayout->setObjectName("recipeListLayout");
        recipeListLayout->setContentsMargins(12, 8, 12, 8);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        recipeListLayout->addItem(verticalSpacer);

        recipeScrollArea->setWidget(recipeListContainer);

        sidebarLayout->addWidget(recipeScrollArea);

        footerLayout = new QHBoxLayout();
        footerLayout->setSpacing(8);
        footerLayout->setObjectName("footerLayout");
        footerLayout->setContentsMargins(12, 12, 12, 12);
        btnAddRecipe = new QPushButton(centralwidget);
        btnAddRecipe->setObjectName("btnAddRecipe");

        footerLayout->addWidget(btnAddRecipe);

        btnDeleteRecipe = new QPushButton(centralwidget);
        btnDeleteRecipe->setObjectName("btnDeleteRecipe");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        btnDeleteRecipe->setIcon(icon);

        footerLayout->addWidget(btnDeleteRecipe);


        sidebarLayout->addLayout(footerLayout);


        horizontalLayout->addLayout(sidebarLayout);

        detailLayout = new QVBoxLayout();
        detailLayout->setSpacing(0);
        detailLayout->setObjectName("detailLayout");
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

        detailHeaderLayout->addWidget(recipeDescriptionEdit);

        recipeStatsWidget = new QWidget(centralwidget);
        recipeStatsWidget->setObjectName("recipeStatsWidget");
        recipeStatsWidget->setMinimumSize(QSize(0, 0));
        recipeStatsWidget->setMaximumSize(QSize(16777215, 16777215));
        statsLayout = new QHBoxLayout(recipeStatsWidget);
        statsLayout->setSpacing(24);
        statsLayout->setObjectName("statsLayout");
        statsLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        timeLabel = new QLabel(recipeStatsWidget);
        timeLabel->setObjectName("timeLabel");

        statsLayout->addWidget(timeLabel);

        servingsLabel = new QLabel(recipeStatsWidget);
        servingsLabel->setObjectName("servingsLabel");

        statsLayout->addWidget(servingsLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statsLayout->addItem(horizontalSpacer);


        detailHeaderLayout->addWidget(recipeStatsWidget, 0, Qt::AlignmentFlag::AlignTop);


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
        detailsContent->setGeometry(QRect(0, 0, 775, 459));
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
        ingredientsContent->setGeometry(QRect(0, 0, 775, 430));
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
        instructionsContent->setGeometry(QRect(0, 0, 775, 430));
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

        recipeTabs->addTab(instructionsTab, QString());

        detailLayout->addWidget(recipeTabs);

        detailLayout->setStretch(0, 1);
        detailLayout->setStretch(1, 2);

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
        menuLangage = new QMenu(menuBar);
        menuLangage->setObjectName("menuLangage");
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuLangage->menuAction());
        menuFile->addAction(actionNouveau);
        menuFile->addAction(actionSauvegarder);
        menuFile->addSeparator();
        menuFile->addAction(actionQuitter_2);
        menuEdit->addAction(actionModifier);

        retranslateUi(MainWindow);

        recipeTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        actionNouveau->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        actionFr->setText(QCoreApplication::translate("MainWindow", "Fr", nullptr));
        actionModifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        actionSauvegarder->setText(QCoreApplication::translate("MainWindow", "Sauvegarder", nullptr));
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        actionQuitter_2->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        sidebarTitle->setText(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher une recette...", nullptr));
        btnAddRecipe->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        btnDeleteRecipe->setText(QString());
        recipeTitleEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Titre de la recette", nullptr));
        recipeDescriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Description de la recette...", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "0 instruction", nullptr));
        servingsLabel->setText(QCoreApplication::translate("MainWindow", "0 ingr\303\251dient", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(detailsTab), QCoreApplication::translate("MainWindow", "D\303\251tails", nullptr));
        btnAddIngredient->setText(QCoreApplication::translate("MainWindow", "Ajouter un ingr\303\251dient", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(ingredientsTab), QCoreApplication::translate("MainWindow", "Ingr\303\251dients", nullptr));
        btnAddInstruction->setText(QCoreApplication::translate("MainWindow", "Ajouter une instruction", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(instructionsTab), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuLangage->setTitle(QCoreApplication::translate("MainWindow", "Langage", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
