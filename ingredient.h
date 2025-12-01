#ifndef INGREDIENT_H
#define INGREDIENT_H
#include "unite.h"
#include <QString>


class Ingredient
{
public:
    Ingredient();
    Ingredient(int id, const QString &nom, float quantite, UNITE unite);

    int getId() const;
    QString getNom() const;
    float getQuantite() const;
    UNITE getUnite() const;

private:
    int m_id;
    QString m_nom;
    float m_quantite;
    UNITE m_unite;
};

#endif
