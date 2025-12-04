#ifndef INGREDIENT_H
#define INGREDIENT_H
#include "unite.h"
#include <QString>


class Ingredient
{
public:
    Ingredient();
    Ingredient(int id, const QString &nom);

    int getId() const;
    QString getNom() const;
    void setNom(QString nom) ;
    int m_id;
    QString m_nom;

};

#endif
