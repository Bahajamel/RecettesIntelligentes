#include "mainwindow.h"
#include "backend.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QDebug>
#include <QTranslator>
#include <QSettings>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Appliquer le style
    QFile styleFile(":/StyleSheet/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);
    }

    // Vérifier driver SQLite
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "ERREUR CRITIQUE: Le driver QSQLITE n'est pas disponible!";
        qCritical() << "Drivers disponibles:" << QSqlDatabase::drivers();
        return -1;
    }

    // Créer le backend
    Backend backend;

    // Créer la fenêtre principale
    MainWindow w(&backend);
    w.show();

    // Test de base de la DB
    QSqlDatabase test = QSqlDatabase::addDatabase("QSQLITE", "TEST");
    test.setDatabaseName("foo.db");
    qDebug() << "OPEN ?" << test.open();

    return a.exec();
}
