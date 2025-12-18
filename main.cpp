#include "mainwindow.h"
#include "backend.h"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Backend backend ;
    MainWindow w(&backend);
    w.show();
    QSqlDatabase test = QSqlDatabase::addDatabase("QSQLITE", "TEST");
    test.setDatabaseName("foo.db");
    qDebug() << "OPEN ?" << test.open();


    return a.exec();
}
