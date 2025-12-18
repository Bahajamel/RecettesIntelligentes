#include "modelsHeader/recettemodel.h"
RecetteTableModel::RecetteTableModel(RecetteService &recetteservice ,QObject *parent)
    : QAbstractTableModel(parent) , m_service(recetteservice)
{}

void RecetteTableModel::setRecettes(const QList<Recette> &recettes)
{
    beginResetModel();
    m_recettes = recettes;
    endResetModel();
}

int RecetteTableModel::rowCount(const QModelIndex &) const
{
    return m_recettes.size();
}

int RecetteTableModel::columnCount(const QModelIndex &) const
{
    return 2; // Titre | Description
}

QVariant RecetteTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Recette &r = m_recettes.at(index.row());

    if (index.column() == 0)
        return r.getTitre();
    if (index.column() == 1)
        return r.getDescription();

    return QVariant();
}

QVariant RecetteTableModel::headerData(int section,
                                       Qt::Orientation orientation,
                                       int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    if (section == 0) return "Titre";
    if (section == 1) return "Description";

    return QVariant();
}
void RecetteTableModel::recharger()
{
    beginResetModel();
    m_recettes = m_service.listerRecettes();
    endResetModel();
}
