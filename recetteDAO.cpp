#include "recetteDAO.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

int RecetteDAO::creerRecette(const QString &titre, const QString &description) {
    QSqlQuery query;
    query.prepare("INSERT INTO recettes (titre, description) VALUES (?, ?)");
    query.addBindValue(titre);
    query.addBindValue(description);

    if (!query.exec()) {
        qWarning() << "ERREUR création recette:" << query.lastError().text();
        return -1;
    }

    int id = query.lastInsertId().toInt();
    qDebug() << "✓ Recette créée avec ID:" << id;
    return id;
}

Recette RecetteDAO::obtenirRecette(int id) {
    Recette recette;
    recette.id = -1; // Valeur par défaut

    QSqlQuery query;
    query.prepare("SELECT id, titre, description, date_creation, date_modification FROM recettes WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "ERREUR lecture recette:" << query.lastError().text();
        return recette;
    }

    if (query.first()) {
        recette.id = query.value(0).toInt();
        recette.titre = query.value(1).toString();
        recette.description = query.value(2).toString();
        recette.dateCreation = query.value(3).toString();
        recette.dateModification = query.value(4).toString();
        qDebug() << "✓ Recette trouvée:" << recette.titre;
    } else {
        qWarning() << "ATTENTION : Recette avec ID" << id << "non trouvée";
    }

    return recette;
}

QList<Recette> RecetteDAO::obtenirToutesRecettes() {
    QList<Recette> recettes;

    QSqlQuery query;
    if (!query.exec("SELECT id, titre, description, date_creation, date_modification FROM recettes ORDER BY titre")) {
        qWarning() << "ERREUR lecture toutes recettes:" << query.lastError().text();
        return recettes;
    }

    while (query.next()) {
        Recette recette;
        recette.id = query.value(0).toInt();
        recette.titre = query.value(1).toString();
        recette.description = query.value(2).toString();
        recette.dateCreation = query.value(3).toString();
        recette.dateModification = query.value(4).toString();
        recettes.append(recette);
    }

    qDebug() << "✓ Total recettes trouvées:" << recettes.size();
    return recettes;
}

bool RecetteDAO::mettreAJourRecette(int id, const QString &titre, const QString &description) {
    QSqlQuery query;
    query.prepare("UPDATE recettes SET titre = ?, description = ?, date_modification = CURRENT_TIMESTAMP WHERE id = ?");
    query.addBindValue(titre);
    query.addBindValue(description);
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "ERREUR mise à jour recette:" << query.lastError().text();
        return false;
    }

    qDebug() << "✓ Recette" << id << "mise à jour";
    return true;
}

bool RecetteDAO::supprimerRecette(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM recettes WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qWarning() << "ERREUR suppression recette:" << query.lastError().text();
        return false;
    }

    qDebug() << "✓ Recette" << id << "supprimée";
    return true;
}

QList<Recette> RecetteDAO::rechercherParTitre(const QString &titre) {
    QList<Recette> recettes;

    QSqlQuery query;
    query.prepare("SELECT id, titre, description, date_creation, date_modification FROM recettes WHERE titre LIKE ? ORDER BY titre");
    query.addBindValue("%" + titre + "%");

    if (!query.exec()) {
        qWarning() << "ERREUR recherche recettes:" << query.lastError().text();
        return recettes;
    }

    while (query.next()) {
        Recette recette;
        recette.id = query.value(0).toInt();
        recette.titre = query.value(1).toString();
        recette.description = query.value(2).toString();
        recette.dateCreation = query.value(3).toString();
        recette.dateModification = query.value(4).toString();
        recettes.append(recette);
    }

    qDebug() << "✓ Recettes trouvées:" << recettes.size() << "pour" << titre;
    return recettes;
}

int RecetteDAO::obtenirNombreRecettes() {
    QSqlQuery query;
    if (!query.exec("SELECT COUNT(*) FROM recettes")) {
        qWarning() << "ERREUR comptage recettes:" << query.lastError().text();
        return 0;
    }

    query.first();
    int count = query.value(0).toInt();
    return count;
}
