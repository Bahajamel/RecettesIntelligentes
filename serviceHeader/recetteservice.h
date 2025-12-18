#ifndef RECETTESERVICE_H
#define RECETTESERVICE_H

#include "daoHeader/recettedao.h"
#include "daoHeader/recetteingredientdao.h"
#include "serviceHeader/instructionservice.h"
#include "serviceHeader/ingredientservice.h"

class RecetteService
{
public:
    RecetteService(RecetteDAO &rDao,
                   RecetteIngredientDAO &riDao,
                   IngredientService &ingService,
                   InstructionService &instService);

    int creerRecette(const QString &titre, const QString &description);
    bool mettreAJourRecette(int id, const QString &titre, const QString &description, const QString &photo);
    bool ajouterIngredient(int recetteId, const Ingredient &ingredient , float qte, UNITE unite);
    QList<Ingredient> ingredientsDeRecette(int recetteId);
    QList<QSharedPointer<Instruction>> instructionsDeRecette(int recetteId);
    RecetteIngredientDAO &m_riDao;
    QList<Recette> listerRecettes();
    Recette obtenirRecetteComplete(int id);

private:
    RecetteDAO &m_recDao;
    IngredientService &m_ingService;
    InstructionService &m_instService;
};

#endif
