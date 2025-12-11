#ifndef INGREDIENTMODEL_H
#define INGREDIENTMODEL_H

#include <QAbstractTableModel>
#include "serviceHeader/ingredientservice.h"
#include "metiersHeader/ingredient.h"

class IngredientTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit IngredientTableModel(IngredientService &service, QObject *parent = nullptr);

    // Surcharges nécessaires
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // Recharger les données
    void refresh();

    // Récupérer un ingrédient par ligne
    Ingredient getIngredientAt(int row) const;

private:
    IngredientService &m_service;
    QList<Ingredient> m_ingredients;
};

#endif // INGREDIENTTABLEMODEL_H
