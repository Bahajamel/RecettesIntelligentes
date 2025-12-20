#include "mainwindow.h"
#include "backend.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD

    // Vérifier que le driver SQLite est disponible
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "ERREUR CRITIQUE: Le driver QSQLITE n'est pas disponible!";
        qCritical() << "Drivers disponibles:" << QSqlDatabase::drivers();
        return -1;
    }

=======
>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a
    Backend backend;
    MainWindow w(&backend);

    QFile styleFile(":/StyleSheet/style.qss");   // ou "StyleSheet/style.qss" si pas de .qrc
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);                  // utiliser 'a'
    }

    w.show();

<<<<<<< HEAD
=======
    QSqlDatabase test = QSqlDatabase::addDatabase("QSQLITE", "TEST");
    test.setDatabaseName("foo.db");
    qDebug() << "OPEN ?" << test.open();

>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a
    return a.exec();
}
