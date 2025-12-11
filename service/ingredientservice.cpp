#include "serviceHeader/ingredientservice.h"

IngredientService::IngredientService(IngredientDAO &dao, RecetteIngredientDAO &riDao)
    : m_ingDao(dao), m_riDao(riDao)
{}

// évite les doublons
int IngredientService::ajouterIngredient(const QString &nom)
{
    Ingredient exist = m_ingDao.findByName(nom);

    if (exist.getId() != -1)
        return exist.getId();

    Ingredient ing(0, nom);
    return m_ingDao.create(ing);
}

// on supprime uniquement si NON utilisé dans une recette
bool IngredientService::supprimerIngredient(int id)
{
    QList<int> usages = m_riDao.findRecettesByIngredient(id);

    if (!usages.isEmpty()) {
        qWarning() << "Impossible : ingrédient utilisé dans recettes" << usages;
        return false;
    }

    return m_ingDao.remove(id);
}

Ingredient IngredientService::trouverParNom(const QString &nom)
{
    return m_ingDao.findByName(nom);
}

QList<Ingredient> IngredientService::listerIngredients()
{
    return m_ingDao.findAll();
}
Ingredient IngredientService::getIngredient(int id) {
    return m_ingDao.findById(id);
}
