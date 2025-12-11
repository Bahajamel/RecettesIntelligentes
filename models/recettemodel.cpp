#include "modelsHeader/recettemodel.h"

RecetteTableModel::RecetteTableModel(RecetteService &service, QObject *parent)
    : QAbstractTableModel(parent), m_service(service)
{}

// Charger ingrédients d’une recette
void RecetteTableModel::chargerRecette(int recetteId)
{
    beginResetModel();
    m_recetteId = recetteId;

    // IMPORTANT :
    // utiliser findByRecette pour récupérer quantité + unité
    m_lignes = m_service.m_riDao.findByRecette(recetteId);

    endResetModel();
}

int RecetteTableModel::rowCount(const QModelIndex &) const
{
    return m_lignes.size();
}

int RecetteTableModel::columnCount(const QModelIndex &) const
{
    return 4; // ID, Nom, Quantité, Unité
}

QVariant RecetteTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const RecetteIngredient &ri = m_lignes[index.row()];

    switch(index.column())
    {
    case 0: return ri.getIngredientId();
    case 1: return ri.getNom();
    case 2: return ri.getQuantite();
    case 3: return uniteToString(ri.getUnite());
    }

    return QVariant();
}

QVariant RecetteTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0: return "ID";
        case 1: return "Nom";
        case 2: return "Quantité";
        case 3: return "Unité";
        }
    }

    return QVariant();
}
