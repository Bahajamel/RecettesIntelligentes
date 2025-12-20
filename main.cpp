#include "mainwindow.h"
#include "backend.h"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Vérifier que le driver SQLite est disponible
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "ERREUR CRITIQUE: Le driver QSQLITE n'est pas disponible!";
        qCritical() << "Drivers disponibles:" << QSqlDatabase::drivers();
        return -1;
    }

    Backend backend;
    MainWindow w(&backend);
    w.show();

    return a.exec();
}
