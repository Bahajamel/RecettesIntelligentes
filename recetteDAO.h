#ifndef RECETTEDAO_H
#define RECETTEDAO_H
#include "recette.h"
#include <QString>
#include <QList>
#include <QVariant>



class RecetteDAO {
public:
    // Créer une nouvelle recette
    static int creerRecette(const QString &titre, const QString &description);

    // Obtenir une recette par ID
    static Recette obtenirRecette(int id);

    // Obtenir toutes les recettes
    static QList<Recette> obtenirToutesRecettes();

    // Mettre à jour une recette
    static bool mettreAJourRecette(int id, const QString &titre, const QString &description);

    // Supprimer une recette
    static bool supprimerRecette(int id);

    // Chercher des recettes par titre
    static QList<Recette> rechercherParTitre(const QString &titre);

    // Obtenir le nombre total de recettes
    static int obtenirNombreRecettes();
};

#endif // RECETTEDAO_H
