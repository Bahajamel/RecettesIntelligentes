#include "modelsHeader/recetteingredient.h"

// --------------------------------------------------
// Constructeur
// --------------------------------------------------
RecetteIngredient::RecetteIngredient(const Ingredient &ingredient,
                                     float quantite,
                                     UNITE unite)
    : m_ingredient(ingredient),
    m_quantite(quantite),
    m_unite(unite)
{
}

// --------------------------------------------------
// GETTERS
// --------------------------------------------------

// Retourne l'ID de l'ingrédient
int RecetteIngredient::getIngredientId() const
{
    return m_ingredient.getId();
}

// Retourne le nom de l'ingrédient
QString RecetteIngredient::getNom() const
{
    return m_ingredient.getNom();
}

// Quantité utilisée dans la recette
float RecetteIngredient::getQuantite() const
{
    return m_quantite;
}

// Unité (GRAMME, ML, PIECE…)
UNITE RecetteIngredient::getUnite() const
{
    return m_unite;
}
Ingredient RecetteIngredient::getIngredient() const {
    return m_ingredient ;
}

// --------------------------------------------------
// SETTERS
// --------------------------------------------------

void RecetteIngredient::setIngredient(const Ingredient &ingredient)
{
    m_ingredient = ingredient;
}

void RecetteIngredient::setQuantite(float quantite)
{
    m_quantite = quantite;
}

void RecetteIngredient::setUnite(UNITE unite)
{
    m_unite = unite;
}
