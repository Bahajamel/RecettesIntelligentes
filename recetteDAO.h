#ifndef RECETTEDAO_H
#define RECETTEDAO_H
#include "recette.h"
#include <QString>
#include <QList>
#include <QVariant>
#include <QSqlDatabase>



class RecetteDAO {
public:
    // Créer une nouvelle recette
    explicit RecetteDAO(const QSqlDatabase &db) ;

    int creerRecette(const QString &titre, const QString &description);

    // Obtenir une recette par ID
    Recette obtenirRecette(int id);

    // Obtenir toutes les recettes
    QList<Recette> obtenirToutesRecettes();

    // Mettre à jour une recette
    bool mettreAJourRecette(int id, const QString &titre, const QString &description);

    // Supprimer une recette
    bool supprimerRecette(int id);

    // Chercher des recettes par titre
    QList<Recette> rechercherParTitre(const QString &titre);

    // Obtenir le nombre total de recettes
    int obtenirNombreRecettes();

private :
    QSqlDatabase m_db;
};

#endif // RECETTEDAO_H
