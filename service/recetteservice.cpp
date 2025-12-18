#include "serviceHeader/recetteservice.h"
#include "metiersHeader/recette.h"
#include "metiersHeader/recetteingredient.h"




RecetteService::RecetteService(RecetteDAO &rDao,
                               RecetteIngredientDAO &riDao,
                               IngredientService &ingService,
                               InstructionService &instService)
    : m_recDao(rDao), m_riDao(riDao),
    m_ingService(ingService), m_instService(instService)
{}

int RecetteService::creerRecette(const QString &titre, const QString &description)
{
    Recette r ;
    r.setTitre(titre);
    r.setDescription(description);
    return m_recDao.creerRecette(titre,description);
}

bool RecetteService::ajouterIngredient(int recetteId, const Ingredient &ingredient , float qte, UNITE unite)
{
    RecetteIngredient ri (ingredient , qte , unite) ;
    return m_riDao.create(recetteId, ri);
}

QList<Ingredient> RecetteService::ingredientsDeRecette(int recetteId)
{
    return m_riDao.findIngredients(recetteId);
}

QList<QSharedPointer<Instruction>> RecetteService::instructionsDeRecette(int recetteId)
{
    return m_instService.chargerArbre(recetteId);
}
QList<Recette> RecetteService::listerRecettes()
{
    return m_recDao.obtenirToutesRecettes();
}



