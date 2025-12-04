#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSauvegarder_triggered();

    void on_actionQuitter_triggered();

    void on_actionEdit_triggered();

    void on_actionDelete_triggered();

    void on_actionRecherche_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
