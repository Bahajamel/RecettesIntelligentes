#ifndef RECETTESERVICE_H
#define RECETTESERVICE_H

#include "recettedao.h"
#include "recetteingredientdao.h"
#include "instructionservice.h"
#include "ingredientservice.h"

class RecetteService
{
public:
    RecetteService(RecetteDAO &rDao,
                   RecetteIngredientDAO &riDao,
                   IngredientService &ingService,
                   InstructionService &instService);

    int creerRecette(const QString &titre, const QString &description);
    bool ajouterIngredient(int recetteId, const Ingredient &ingredient , float qte, UNITE unite);
    QList<Ingredient> ingredientsDeRecette(int recetteId);
    QList<QSharedPointer<Instruction>> instructionsDeRecette(int recetteId);

private:
    RecetteDAO &m_recDao;
    RecetteIngredientDAO &m_riDao;
    IngredientService &m_ingService;
    InstructionService &m_instService;
};

#endif
