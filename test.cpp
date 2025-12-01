#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Drivers disponibles :" << QSqlDatabase::drivers();

    return a.exec();
}
