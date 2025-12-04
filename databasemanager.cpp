#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(const QString &path)
    : m_path(path)
{
    // Connexion nommée (important pour éviter collisions Qt)
    m_db = QSqlDatabase::addDatabase("QSQLITE", "GESTION_RECETTES_CONN");
    m_db.setDatabaseName(m_path);
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open()
{
    if (!m_db.open()) {
        qWarning() << "Erreur ouverture DB:" << m_db.lastError().text();
        return false;
    }

    // Active les foreign keys
    QSqlQuery pragma(m_db);
    pragma.exec("PRAGMA foreign_keys = ON;");

    // Création des tables
    return createTables();
}

void DatabaseManager::close()
{
    if (m_db.isOpen())
        m_db.close();

    QSqlDatabase::removeDatabase("GESTION_RECETTES_CONN");
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

bool DatabaseManager::createTables()
{
    QSqlQuery q(m_db);

    QStringList queries = {

    // ------------------- Table Recette -------------------
    R"(
        CREATE TABLE IF NOT EXISTS recette (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            titre TEXT NOT NULL,
            description TEXT
        );
        )",

        // ------------------- Ingredient -------------------
        R"(
        CREATE TABLE IF NOT EXISTS ingredient (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            nom TEXT NOT NULL UNIQUE
        );
        )",

        // ------------------- Recette_Ingredient -------------------
        R"(
        CREATE TABLE IF NOT EXISTS recette_ingredient (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            recette_id INTEGER NOT NULL,
            ingredient_id INTEGER NOT NULL,
            quantite REAL,
            unite TEXT,
            FOREIGN KEY(recette_id) REFERENCES recette(id) ON DELETE CASCADE,
            FOREIGN KEY(ingredient_id) REFERENCES ingredient(id) ON DELETE CASCADE
        );
        )",

        // ------------------- Instruction -------------------
        R"(
        CREATE TABLE IF NOT EXISTS instruction (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            recette_id INTEGER NOT NULL,
            parent_id INTEGER,
            ordre INTEGER DEFAULT 0,
            type TEXT NOT NULL,
            FOREIGN KEY(recette_id) REFERENCES recette(id) ON DELETE CASCADE,
            FOREIGN KEY(parent_id) REFERENCES instruction(id) ON DELETE CASCADE
        );
        )",

        // ------------------- Instruction Simple -------------------
        R"(
        CREATE TABLE IF NOT EXISTS instruction_simple (
            instruction_id INTEGER PRIMARY KEY,
            texte TEXT NOT NULL,
            FOREIGN KEY(instruction_id) REFERENCES instruction(id) ON DELETE CASCADE
        );
        )",

        // ------------------- Instruction Composée -------------------
        R"(
        CREATE TABLE IF NOT EXISTS instruction_composee (
            instruction_id INTEGER PRIMARY KEY,
            titre TEXT NOT NULL,
            FOREIGN KEY(instruction_id) REFERENCES instruction(id) ON DELETE CASCADE
        );
        )"
};

// Exécution des requêtes une à une
for (const QString &sql : queries) {
    if (!q.exec(sql)) {
        qWarning() << "Erreur creation table:\n" << sql
                   << "\n->" << q.lastError().text();
        return false;
    }
}

return true;
}
