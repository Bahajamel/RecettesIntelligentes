#include "modelsHeader/recetteingredientmodel.h"

RecetteIngredientTableModel::RecetteIngredientTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void RecetteIngredientTableModel::setRecetteIngredients(const QList<RecetteIngredient> &list)
{
    beginResetModel();
    m_items = list;
    endResetModel();
}

int RecetteIngredientTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_items.size();
}

int RecetteIngredientTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return 3;  // Nom, Quantité, Unité
}

QVariant RecetteIngredientTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const RecetteIngredient &ri = m_items[index.row()];

    switch (index.column()) {
    case 0: return ri.getNom();
    case 1: return ri.getQuantite();
    case 2:
        switch (ri.getUnite()) {
        case UNITE::GRAMME: return "g";
        case UNITE::LITRE: return "L";
        case UNITE::PIECE: return "pièces";
        default: return "??";
        }
    default:
        return {};
    }
}

QVariant RecetteIngredientTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return {};

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Ingrédient";
        case 1: return "Quantité";
        case 2: return "Unité";
        }
    }

    return {};
}
