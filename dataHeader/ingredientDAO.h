#ifndef INGREDIENTDAO_H
#define INGREDIENTDAO_H

#include <QSqlDatabase>
#include "modelsHeader/ingredient.h"

class IngredientDAO
{
public:
    explicit IngredientDAO(const QSqlDatabase &db);

    int create(const Ingredient &ing);
    Ingredient findById(int id);
    Ingredient findByName(const QString &name);
    int findOrCreate(const QString &name);
    QList<Ingredient> findAll();
    bool remove(int id);
    bool removeAll() ;

private:
    QSqlDatabase m_db;
};

#endif // INGREDIENTDAO_H
