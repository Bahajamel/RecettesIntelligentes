#include "dataHeader/databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlDriver>

DatabaseManager::DatabaseManager(const QString &path)
    : m_path(path)
{
    // Vérifier que le driver SQLite est disponible
    if (!QSqlDatabase::isDriverAvailable("QSQLITE")) {
        qCritical() << "ERREUR: Le driver QSQLITE n'est pas disponible!";
        qCritical() << "Drivers disponibles:" << QSqlDatabase::drivers();
    }
    
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
    if (!m_db.isValid()) {
        qCritical() << "ERREUR: La connexion à la base de données n'est pas valide!";
        qCritical() << "Driver:" << m_db.driverName();
        return false;
    }
    
    if (!m_db.open()) {
        qCritical() << "ERREUR ouverture DB:" << m_db.lastError().text();
        qCritical() << "Chemin DB:" << m_path;
        return false;
    }
    
    qDebug() << "✓ Base de données ouverte avec succès:" << m_path;

    // Active les foreign keys
    QSqlQuery pragma(m_db);
    if (!pragma.exec("PRAGMA foreign_keys = ON;")) {
        qWarning() << "Erreur activation foreign keys:" << pragma.lastError().text();
    }

    // Création des tables
    bool success = createTables();
    if (success) {
        qDebug() << "✓ Tables créées/vérifiées avec succès";
    }
    return success;
}

void DatabaseManager::close()
{
    if (m_db.isOpen()) {
        // Vérifier si la connexion est encore utilisée avant de la supprimer
        QStringList connections = QSqlDatabase::connectionNames();
        if (connections.contains("GESTION_RECETTES_CONN")) {
            m_db.close();
            // Ne pas supprimer immédiatement la connexion si elle est encore référencée
            // Elle sera supprimée automatiquement à la fin du programme
        }
    }
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
            description TEXT,
            photo TEXT
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

// Migration: Ajouter colonne photo si elle n'existe pas
QSqlQuery checkCol(m_db);
if (checkCol.exec("PRAGMA table_info(recette)")) {
    bool hasPhoto = false;
    while (checkCol.next()) {
        if (checkCol.value(1).toString() == "photo") {
            hasPhoto = true;
            break;
        }
    }
    if (!hasPhoto) {
        if (!q.exec("ALTER TABLE recette ADD COLUMN photo TEXT")) {
            qWarning() << "Erreur ajout colonne photo:" << q.lastError().text();
        } else {
            qDebug() << "✓ Colonne photo ajoutée à la table recette";
        }
    }
}

return true;
}


bool DatabaseManager::resetDatabase()
{
    if (!m_db.isOpen()) {
        qWarning() << "ERREUR: La base de données n'est pas ouverte pour resetDatabase()";
        return false;
    }
    
    QSqlQuery q(m_db);

    // Désactiver les foreign keys pour permettre la suppression
    if (!q.exec("PRAGMA foreign_keys = OFF")) {
        qWarning() << "Erreur désactivation foreign keys:" << q.lastError().text();
    }

    // Supprimer dans l'ordre pour respecter les dépendances
    QStringList deleteQueries = {
        "DELETE FROM instruction_simple",
        "DELETE FROM instruction_composee",
        "DELETE FROM instruction",
        "DELETE FROM recette_ingredient",
        "DELETE FROM recette",
        "DELETE FROM ingredient"
    };

    bool allSuccess = true;
    for (const QString &sql : deleteQueries) {
        if (!q.exec(sql)) {
            qWarning() << "Erreur lors de la suppression:" << sql << "-" << q.lastError().text();
            allSuccess = false;
        } else {
            qDebug() << "✓ Supprimé:" << sql << "-" << q.numRowsAffected() << "lignes affectées";
        }
    }

    // Réactiver les foreign keys
    if (!q.exec("PRAGMA foreign_keys = ON")) {
        qWarning() << "Erreur activation foreign keys:" << q.lastError().text();
    }

    if (allSuccess) {
        qDebug() << "✓ Base de données réinitialisée (toutes les données supprimées)";
    } else {
        qWarning() << "⚠ Certaines suppressions ont échoué";
    }
    
    return allSuccess;
}
