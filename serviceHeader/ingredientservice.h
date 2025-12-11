#ifndef INGREDIENTSERVICE_H
#define INGREDIENTSERVICE_H

#include "daoHeader/ingredientDAO.h"
#include "daoHeader/recetteingredientdao.h"

class IngredientService
{
public:
    IngredientService(IngredientDAO &dao, RecetteIngredientDAO &riDao);

    int ajouterIngredient(const QString &nom);
    bool supprimerIngredient(int id);
    Ingredient trouverParNom(const QString &nom);
    QList<Ingredient> listerIngredients();
    Ingredient getIngredient(int id) ;

private:
    IngredientDAO &m_ingDao;
    RecetteIngredientDAO &m_riDao;
};

#endif
