#ifndef RECETTEINGREDIENTDAO_H
#define RECETTEINGREDIENTDAO_H

#include <QSqlDatabase>
#include <QList>
#include "modelsHeader/recetteingredient.h"

class RecetteIngredientDAO
{
public:
    explicit RecetteIngredientDAO(const QSqlDatabase &db);

    // CREATE
    int create(int recetteId, const RecetteIngredient &ri);

    // READ
    QList<RecetteIngredient> findByRecette(int recetteId);
    RecetteIngredient findOne(int id);

    // UPDATE
    bool update(int id, const RecetteIngredient &ri);

    // utiliser pour ajouter un ingredient dans une recette
    bool add(int recetteId, int ingredientId, float quantite, UNITE &unite);

    // DELETE
    bool remove(int id);
    bool removeByRecette(int recetteId);
    QList<int> findRecettesByIngredient(int ingredientId);
    QList<Ingredient> findIngredients(int recetteId);

private:
    QSqlDatabase m_db;
};

#endif // RECETTEINGREDIENTDAO_H
