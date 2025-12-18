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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
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
    QWidget *centralwidget;
    QWidget *sidebarWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *logoLabel;
    QPushButton *btnAllRecipes;
    QPushButton *btnMyRecipes;
    QWidget *recettesWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *searchLineEdit;
    QListView *recetteListView;
    QScrollArea *detailsScrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *descriptionTextEdit;
    QTabWidget *tabWidget;
    QWidget *tab1;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *ingredientTable;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *tab2;
    QListWidget *instructionList;
    QWidget *navigation;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnPrevInstruction;
    QSpacerItem *horizontalSpacer;
    QLabel *instructionCounterLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnNextInstruction;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnAddInstruction;
    QPushButton *btnAddSubInstruction;
    QPushButton *btnRemoveInstruction;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line;
    QLineEdit *titleLineEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuAffihce;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(897, 751);
        actionNouveau = new QAction(MainWindow);
        actionNouveau->setObjectName("actionNouveau");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        actionNouveau->setIcon(icon);
        actionOuvrir = new QAction(MainWindow);
        actionOuvrir->setObjectName("actionOuvrir");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        actionOuvrir->setIcon(icon1);
        actionSauvegarder = new QAction(MainWindow);
        actionSauvegarder->setObjectName("actionSauvegarder");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        actionSauvegarder->setIcon(icon2);
        actionExporter = new QAction(MainWindow);
        actionExporter->setObjectName("actionExporter");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::GoUp));
        actionExporter->setIcon(icon3);
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName("actionQuitter");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionQuitter->setIcon(icon4);
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName("actionEdit");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::MailMessageNew));
        actionEdit->setIcon(icon5);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::EditDelete));
        actionDelete->setIcon(icon6);
        actionRecherche = new QAction(MainWindow);
        actionRecherche->setObjectName("actionRecherche");
        QIcon icon7(QIcon::fromTheme(QIcon::ThemeIcon::EditFind));
        actionRecherche->setIcon(icon7);
        actionSideBar = new QAction(MainWindow);
        actionSideBar->setObjectName("actionSideBar");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sidebarWidget = new QWidget(centralwidget);
        sidebarWidget->setObjectName("sidebarWidget");
        sidebarWidget->setEnabled(true);
        sidebarWidget->setGeometry(QRect(-1, 10, 151, 641));
        sidebarWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(3, 61, 112);"));
        verticalLayoutWidget = new QWidget(sidebarWidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 10, 151, 171));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(17);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(2, 0, 0, 16);
        logoLabel = new QLabel(verticalLayoutWidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 600 9pt \"Segoe UI\";"));
        logoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        logoLabel->setWordWrap(false);
        logoLabel->setMargin(13);

        verticalLayout->addWidget(logoLabel);

        btnAllRecipes = new QPushButton(verticalLayoutWidget);
        btnAllRecipes->setObjectName("btnAllRecipes");
        btnAllRecipes->setMaximumSize(QSize(16777215, 16777215));
        btnAllRecipes->setBaseSize(QSize(0, 0));
        btnAllRecipes->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        btnAllRecipes->setStyleSheet(QString::fromUtf8("font: 600 9pt \"Segoe UI\";\n"
"gridline-color: rgb(255, 255, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(255, 255, 255);"));
        btnAllRecipes->setIconSize(QSize(20, 20));

        verticalLayout->addWidget(btnAllRecipes);

        btnMyRecipes = new QPushButton(verticalLayoutWidget);
        btnMyRecipes->setObjectName("btnMyRecipes");
        btnMyRecipes->setStyleSheet(QString::fromUtf8("font: 600 9pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
"border-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(btnMyRecipes);

        btnMyRecipes->raise();
        logoLabel->raise();
        btnAllRecipes->raise();
        recettesWidget = new QWidget(centralwidget);
        recettesWidget->setObjectName("recettesWidget");
        recettesWidget->setGeometry(QRect(149, -1, 191, 651));
        verticalLayoutWidget_2 = new QWidget(recettesWidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(-1, 9, 191, 641));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(5, 2, 3, 3);
        searchLineEdit = new QLineEdit(verticalLayoutWidget_2);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));

        verticalLayout_2->addWidget(searchLineEdit);

        recetteListView = new QListView(verticalLayoutWidget_2);
        recetteListView->setObjectName("recetteListView");
        recetteListView->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        recetteListView->setAlternatingRowColors(false);
        recetteListView->setIconSize(QSize(80, 80));

        verticalLayout_2->addWidget(recetteListView);

        detailsScrollArea = new QScrollArea(centralwidget);
        detailsScrollArea->setObjectName("detailsScrollArea");
        detailsScrollArea->setGeometry(QRect(349, 14, 531, 641));
        detailsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 529, 639));
        descriptionTextEdit = new QTextEdit(scrollAreaWidgetContents);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setGeometry(QRect(11, 58, 511, 70));
        descriptionTextEdit->setMinimumSize(QSize(0, 70));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(10, 140, 501, 441));
        tab1 = new QWidget();
        tab1->setObjectName("tab1");
        verticalLayout_6 = new QVBoxLayout(tab1);
        verticalLayout_6->setObjectName("verticalLayout_6");
        ingredientTable = new QTabWidget(tab1);
        ingredientTable->setObjectName("ingredientTable");
        tab = new QWidget();
        tab->setObjectName("tab");
        ingredientTable->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        ingredientTable->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        ingredientTable->addTab(tab_3, QString());

        verticalLayout_6->addWidget(ingredientTable);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(41);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        horizontalLayout_4->setContentsMargins(28, -1, 42, 0);
        pushButton_3 = new QPushButton(tab1);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setBaseSize(QSize(0, 0));
        QIcon icon8(QIcon::fromTheme(QString::fromUtf8("list-add")));
        pushButton_3->setIcon(icon8);
        pushButton_3->setIconSize(QSize(10, 10));

        horizontalLayout_4->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(tab1);
        pushButton_4->setObjectName("pushButton_4");
        QIcon icon9(QIcon::fromTheme(QString::fromUtf8("list-remove")));
        pushButton_4->setIcon(icon9);
        pushButton_4->setIconSize(QSize(10, 10));

        horizontalLayout_4->addWidget(pushButton_4);


        verticalLayout_6->addLayout(horizontalLayout_4);

        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName("tab2");
        instructionList = new QListWidget(tab2);
        instructionList->setObjectName("instructionList");
        instructionList->setGeometry(QRect(10, 10, 481, 261));
        instructionList->setDragDropMode(QAbstractItemView::DragDropMode::InternalMove);
        navigation = new QWidget(tab2);
        navigation->setObjectName("navigation");
        navigation->setGeometry(QRect(60, 290, 371, 51));
        horizontalLayout_5 = new QHBoxLayout(navigation);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        btnPrevInstruction = new QPushButton(navigation);
        btnPrevInstruction->setObjectName("btnPrevInstruction");
        QIcon icon10(QIcon::fromTheme(QIcon::ThemeIcon::GoPrevious));
        btnPrevInstruction->setIcon(icon10);

        horizontalLayout_5->addWidget(btnPrevInstruction);

        horizontalSpacer = new QSpacerItem(20, 7, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        instructionCounterLabel = new QLabel(navigation);
        instructionCounterLabel->setObjectName("instructionCounterLabel");

        horizontalLayout_5->addWidget(instructionCounterLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        btnNextInstruction = new QPushButton(navigation);
        btnNextInstruction->setObjectName("btnNextInstruction");
        QIcon icon11(QIcon::fromTheme(QIcon::ThemeIcon::GoNext));
        btnNextInstruction->setIcon(icon11);
        btnNextInstruction->setCheckable(false);

        horizontalLayout_5->addWidget(btnNextInstruction);

        widget = new QWidget(tab2);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(60, 350, 371, 51));
        horizontalLayout_6 = new QHBoxLayout(widget);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        btnAddInstruction = new QPushButton(widget);
        btnAddInstruction->setObjectName("btnAddInstruction");

        horizontalLayout_6->addWidget(btnAddInstruction);

        btnAddSubInstruction = new QPushButton(widget);
        btnAddSubInstruction->setObjectName("btnAddSubInstruction");
        QIcon icon12(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd));
        btnAddSubInstruction->setIcon(icon12);
        btnAddSubInstruction->setIconSize(QSize(10, 10));

        horizontalLayout_6->addWidget(btnAddSubInstruction);

        btnRemoveInstruction = new QPushButton(widget);
        btnRemoveInstruction->setObjectName("btnRemoveInstruction");

        horizontalLayout_6->addWidget(btnRemoveInstruction);

        horizontalSpacer_3 = new QSpacerItem(52, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        line = new QFrame(tab2);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 340, 501, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        tabWidget->addTab(tab2, QString());
        titleLineEdit = new QLineEdit(scrollAreaWidgetContents);
        titleLineEdit->setObjectName("titleLineEdit");
        titleLineEdit->setGeometry(QRect(11, 11, 511, 40));
        titleLineEdit->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLineEdit->setFont(font);
        detailsScrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 897, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuAffihce = new QMenu(menubar);
        menuAffihce->setObjectName("menuAffihce");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuAffihce->menuAction());
        menuFile->addAction(actionNouveau);
        menuFile->addAction(actionOuvrir);
        menuFile->addAction(actionSauvegarder);
        menuFile->addAction(actionExporter);
        menuFile->addSeparator();
        menuFile->addAction(actionQuitter);
        menuEdit->addAction(actionEdit);
        menuEdit->addAction(actionDelete);
        menuEdit->addAction(actionRecherche);
        menuAffihce->addAction(actionSideBar);
        toolBar->addAction(actionNouveau);
        toolBar->addAction(actionSauvegarder);
        toolBar->addAction(actionEdit);
        toolBar->addAction(actionDelete);
        toolBar->addAction(actionRecherche);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        ingredientTable->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNouveau->setText(QCoreApplication::translate("MainWindow", "Nouveau", nullptr));
#if QT_CONFIG(shortcut)
        actionNouveau->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOuvrir->setText(QCoreApplication::translate("MainWindow", "Ouvrir", nullptr));
#if QT_CONFIG(shortcut)
        actionOuvrir->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSauvegarder->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSauvegarder->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionExporter->setText(QCoreApplication::translate("MainWindow", "Exporter", nullptr));
#if QT_CONFIG(shortcut)
        actionExporter->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuitter->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
#if QT_CONFIG(shortcut)
        actionQuitter->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionEdit->setText(QCoreApplication::translate("MainWindow", "Edit", nullptr));
#if QT_CONFIG(shortcut)
        actionEdit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
#if QT_CONFIG(shortcut)
        actionDelete->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRecherche->setText(QCoreApplication::translate("MainWindow", "Recherche", nullptr));
#if QT_CONFIG(shortcut)
        actionRecherche->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSideBar->setText(QCoreApplication::translate("MainWindow", "SideBar", nullptr));
        logoLabel->setText(QCoreApplication::translate("MainWindow", "Recettes", nullptr));
        btnAllRecipes->setText(QCoreApplication::translate("MainWindow", "Toutres les Recettes", nullptr));
        btnMyRecipes->setText(QCoreApplication::translate("MainWindow", "Mes recettes", nullptr));
        searchLineEdit->setText(QCoreApplication::translate("MainWindow", "Rechercher une recette...", nullptr));
        descriptionTextEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Description de la recette</p></body></html>", nullptr));
        ingredientTable->setTabText(ingredientTable->indexOf(tab), QCoreApplication::translate("MainWindow", "Nom", nullptr));
        ingredientTable->setTabText(ingredientTable->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Quantit\303\251", nullptr));
        ingredientTable->setTabText(ingredientTable->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Unit\303\251", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QCoreApplication::translate("MainWindow", "Ingr\303\251dients", nullptr));
        btnPrevInstruction->setText(QCoreApplication::translate("MainWindow", "Pr\303\251c\303\251dent", nullptr));
        instructionCounterLabel->setText(QCoreApplication::translate("MainWindow", "1 / 5", nullptr));
        btnNextInstruction->setText(QCoreApplication::translate("MainWindow", "Suivant", nullptr));
        btnAddInstruction->setText(QCoreApplication::translate("MainWindow", "Ajouter Instruction", nullptr));
        btnAddSubInstruction->setText(QCoreApplication::translate("MainWindow", "Sous-\303\251tape", nullptr));
        btnRemoveInstruction->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QCoreApplication::translate("MainWindow", "Instructions", nullptr));
        titleLineEdit->setText(QCoreApplication::translate("MainWindow", "Titre de la recette", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuAffihce->setTitle(QCoreApplication::translate("MainWindow", "Affiche", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
