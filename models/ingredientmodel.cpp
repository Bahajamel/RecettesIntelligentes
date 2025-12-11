#include "modelsHeader/ingredientmodel.h"

IngredientTableModel::IngredientTableModel(IngredientService &service, QObject *parent)
    : QAbstractTableModel(parent), m_service(service)
{
    refresh();
}

int IngredientTableModel::rowCount(const QModelIndex &) const
{
    return m_ingredients.size();
}

int IngredientTableModel::columnCount(const QModelIndex &) const
{
    return 2;  // ID, Nom
}

QVariant IngredientTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Ingredient &ing = m_ingredients[index.row()];

    switch (index.column()) {
    case 0: return ing.getId();
    case 1: return ing.getNom();
    }
    return QVariant();
}

QVariant IngredientTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
    case 0: return "ID";
    case 1: return "Nom";
    }
    return QVariant();
}

void IngredientTableModel::refresh()
{
    beginResetModel();
    m_ingredients = m_service.listerIngredients();
    endResetModel();
}

Ingredient IngredientTableModel::getIngredientAt(int row) const
{
    if (row < 0 || row >= m_ingredients.size())
        return Ingredient();

    return m_ingredients[row];
}
