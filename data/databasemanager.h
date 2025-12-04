#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class databasemanagerData;

class databasemanager
{
    Q_OBJECT
    QML_ELEMENT
public:
    databasemanager();
    databasemanager(const databasemanager &);
    databasemanager(databasemanager &&);
    databasemanager &operator=(const databasemanager &);
    databasemanager &operator=(databasemanager &&);
    ~databasemanager();

private:
    QSharedDataPointer<databasemanagerData> data;
};

#endif // DATABASEMANAGER_H
