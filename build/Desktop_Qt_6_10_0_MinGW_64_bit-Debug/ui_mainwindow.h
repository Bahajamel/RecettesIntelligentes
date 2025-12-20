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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
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
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *recipeListWidget;
    QVBoxLayout *sidebarLayout;
    QWidget *sidebarHeader;
    QVBoxLayout *headerLayout;
    QLabel *sidebarTitle;
    QLineEdit *searchLineEdit;
    QScrollArea *recipeScrollArea;
    QWidget *recipeListContainer;
    QVBoxLayout *recipeListLayout;
    QSpacerItem *verticalSpacer;
    QWidget *sidebarFooter;
    QHBoxLayout *footerLayout;
    QPushButton *btnAddRecipe;
    QPushButton *btnDeleteRecipe;
    QWidget *recipeDetailWidget;
    QVBoxLayout *detailLayout;
    QWidget *detailHeader;
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

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 900);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(24);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(16, 16, 16, 16);
        recipeListWidget = new QWidget(centralwidget);
        recipeListWidget->setObjectName("recipeListWidget");
        recipeListWidget->setMinimumSize(QSize(320, 0));
        recipeListWidget->setMaximumSize(QSize(320, 16777215));
        sidebarLayout = new QVBoxLayout(recipeListWidget);
        sidebarLayout->setSpacing(0);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(0, 0, 0, 0);
        sidebarHeader = new QWidget(recipeListWidget);
        sidebarHeader->setObjectName("sidebarHeader");
        sidebarHeader->setMinimumSize(QSize(0, 0));
        sidebarHeader->setMaximumSize(QSize(16777215, 16777215));
        headerLayout = new QVBoxLayout(sidebarHeader);
        headerLayout->setSpacing(12);
        headerLayout->setObjectName("headerLayout");
        headerLayout->setContentsMargins(16, 16, 16, 16);
        sidebarTitle = new QLabel(sidebarHeader);
        sidebarTitle->setObjectName("sidebarTitle");
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        sidebarTitle->setFont(font);

        headerLayout->addWidget(sidebarTitle);

        searchLineEdit = new QLineEdit(sidebarHeader);
        searchLineEdit->setObjectName("searchLineEdit");

        headerLayout->addWidget(searchLineEdit);


        sidebarLayout->addWidget(sidebarHeader);

        recipeScrollArea = new QScrollArea(recipeListWidget);
        recipeScrollArea->setObjectName("recipeScrollArea");
        recipeScrollArea->setWidgetResizable(true);
        recipeScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        recipeScrollArea->setFrameShadow(QFrame::Shadow::Plain);
        recipeListContainer = new QWidget();
        recipeListContainer->setObjectName("recipeListContainer");
        recipeListContainer->setGeometry(QRect(0, 0, 280, 500));
        recipeListLayout = new QVBoxLayout(recipeListContainer);
        recipeListLayout->setSpacing(8);
        recipeListLayout->setObjectName("recipeListLayout");
        recipeListLayout->setContentsMargins(12, 8, 12, 8);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        recipeListLayout->addItem(verticalSpacer);

        recipeScrollArea->setWidget(recipeListContainer);

        sidebarLayout->addWidget(recipeScrollArea);

        sidebarFooter = new QWidget(recipeListWidget);
        sidebarFooter->setObjectName("sidebarFooter");
        sidebarFooter->setMinimumSize(QSize(0, 0));
        sidebarFooter->setMaximumSize(QSize(16777215, 16777215));
        footerLayout = new QHBoxLayout(sidebarFooter);
        footerLayout->setSpacing(8);
        footerLayout->setObjectName("footerLayout");
        footerLayout->setContentsMargins(12, 12, 12, 12);
        btnAddRecipe = new QPushButton(sidebarFooter);
        btnAddRecipe->setObjectName("btnAddRecipe");

        footerLayout->addWidget(btnAddRecipe);

        btnDeleteRecipe = new QPushButton(sidebarFooter);
        btnDeleteRecipe->setObjectName("btnDeleteRecipe");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        btnDeleteRecipe->setIcon(icon);

        footerLayout->addWidget(btnDeleteRecipe);


        sidebarLayout->addWidget(sidebarFooter);


        horizontalLayout->addWidget(recipeListWidget);

        recipeDetailWidget = new QWidget(centralwidget);
        recipeDetailWidget->setObjectName("recipeDetailWidget");
        detailLayout = new QVBoxLayout(recipeDetailWidget);
        detailLayout->setSpacing(0);
        detailLayout->setObjectName("detailLayout");
        detailLayout->setContentsMargins(0, 0, 0, 0);
        detailHeader = new QWidget(recipeDetailWidget);
        detailHeader->setObjectName("detailHeader");
        detailHeader->setMinimumSize(QSize(0, 0));
        detailHeader->setMaximumSize(QSize(16777215, 16777215));
        detailHeaderLayout = new QVBoxLayout(detailHeader);
        detailHeaderLayout->setSpacing(16);
        detailHeaderLayout->setObjectName("detailHeaderLayout");
        detailHeaderLayout->setContentsMargins(24, 24, 24, 24);
        recipeTitleEdit = new QLineEdit(detailHeader);
        recipeTitleEdit->setObjectName("recipeTitleEdit");
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        recipeTitleEdit->setFont(font1);

        detailHeaderLayout->addWidget(recipeTitleEdit);

        recipeDescriptionEdit = new QTextEdit(detailHeader);
        recipeDescriptionEdit->setObjectName("recipeDescriptionEdit");
        recipeDescriptionEdit->setMaximumHeight(80);

        detailHeaderLayout->addWidget(recipeDescriptionEdit);

        recipeStatsWidget = new QWidget(detailHeader);
        recipeStatsWidget->setObjectName("recipeStatsWidget");
        recipeStatsWidget->setMinimumSize(QSize(0, 0));
        recipeStatsWidget->setMaximumSize(QSize(16777215, 16777215));
        statsLayout = new QHBoxLayout(recipeStatsWidget);
        statsLayout->setSpacing(24);
        statsLayout->setObjectName("statsLayout");
        timeLabel = new QLabel(recipeStatsWidget);
        timeLabel->setObjectName("timeLabel");

        statsLayout->addWidget(timeLabel);

        servingsLabel = new QLabel(recipeStatsWidget);
        servingsLabel->setObjectName("servingsLabel");

        statsLayout->addWidget(servingsLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statsLayout->addItem(horizontalSpacer);


        detailHeaderLayout->addWidget(recipeStatsWidget);


        detailLayout->addWidget(detailHeader);

        recipeTabs = new QTabWidget(recipeDetailWidget);
        recipeTabs->setObjectName("recipeTabs");
        detailsTab = new QWidget();
        detailsTab->setObjectName("detailsTab");
        detailsTabLayout = new QVBoxLayout(detailsTab);
        detailsTabLayout->setSpacing(0);
        detailsTabLayout->setObjectName("detailsTabLayout");
        detailsTabLayout->setContentsMargins(24, 24, 24, 24);
        detailsScrollArea = new QScrollArea(detailsTab);
        detailsScrollArea->setObjectName("detailsScrollArea");
        detailsScrollArea->setWidgetResizable(true);
        detailsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        detailsContent = new QWidget();
        detailsContent->setObjectName("detailsContent");
        detailsContent->setGeometry(QRect(0, 0, 500, 400));
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
        ingredientsScrollArea->setWidgetResizable(true);
        ingredientsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        ingredientsContent = new QWidget();
        ingredientsContent->setObjectName("ingredientsContent");
        ingredientsContent->setGeometry(QRect(0, 0, 500, 400));
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
        instructionsScrollArea->setWidgetResizable(true);
        instructionsScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        instructionsContent = new QWidget();
        instructionsContent->setObjectName("instructionsContent");
        instructionsContent->setGeometry(QRect(0, 0, 500, 400));
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


        horizontalLayout->addWidget(recipeDetailWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        recipeTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        sidebarTitle->setText(QCoreApplication::translate("MainWindow", "Mes Recettes", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Rechercher une recette...", nullptr));
        btnAddRecipe->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
        btnDeleteRecipe->setText(QString());
        recipeTitleEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Titre de la recette", nullptr));
        recipeDescriptionEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Description de la recette...", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "0 min total", nullptr));
        servingsLabel->setText(QCoreApplication::translate("MainWindow", "0 portions", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(detailsTab), QCoreApplication::translate("MainWindow", "D\303\251tails", nullptr));
        btnAddIngredient->setText(QCoreApplication::translate("MainWindow", "Ajouter un ingr\303\251dient", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(ingredientsTab), QCoreApplication::translate("MainWindow", "Ingr\303\251dients", nullptr));
        btnAddInstruction->setText(QCoreApplication::translate("MainWindow", "Ajouter une instruction", nullptr));
        recipeTabs->setTabText(recipeTabs->indexOf(instructionsTab), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
