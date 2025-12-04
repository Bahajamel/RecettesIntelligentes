#ifndef INGREDIENTSERVICE_H
#define INGREDIENTSERVICE_H

#include "ingredientdao.h"
#include "recetteingredientdao.h"

class IngredientService
{
public:
    IngredientService(IngredientDAO &dao, RecetteIngredientDAO &riDao);

    int ajouterIngredient(const QString &nom);
    bool supprimerIngredient(int id);
    Ingredient trouverParNom(const QString &nom);
    QList<Ingredient> listerIngredients();

private:
    IngredientDAO &m_ingDao;
    RecetteIngredientDAO &m_riDao;
};

#endif
