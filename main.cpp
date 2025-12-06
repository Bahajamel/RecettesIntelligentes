#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSqlDatabase test = QSqlDatabase::addDatabase("QSQLITE", "TEST");
    test.setDatabaseName("foo.db");
    qDebug() << "OPEN ?" << test.open();


    return a.exec();
}
