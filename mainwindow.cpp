#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

