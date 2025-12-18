#ifndef RECETTEINGREDIENT_H
#define RECETTEINGREDIENT_H

#include "ingredient.h"
#include "unite.h"

class RecetteIngredient
{
public:
    RecetteIngredient() = default;
    RecetteIngredient(const Ingredient &ingredient, float quantite, UNITE unite);

    // --- Getters ---
    int getIngredientId() const;
    Ingredient getIngredient() const ;
    QString getNom() const;
    float getQuantite() const;
    UNITE getUnite() const;

    // --- Setters ---
    void setIngredient(const Ingredient &ingredient);
    void setQuantite(float quantite);
    void setUnite(UNITE unite);


    // attribut pour la recette
    int recetteId = -1;

private:
    Ingredient m_ingredient;
    float m_quantite = 0;
    UNITE m_unite = UNITE::GRAMME;
};

#endif // RECETTEINGREDIENT_H
