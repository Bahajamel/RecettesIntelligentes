#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
public:
    explicit DatabaseManager(const QString &path);
    ~DatabaseManager();

    bool open();
    void close();
    bool resetDatabase() ;

    QSqlDatabase database() const;

private:
    bool createTables();

    QString m_path;
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H
