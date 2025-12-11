#ifndef RECETETABLEMODEL_H
#define RECETETABLEMODEL_H

#include <QAbstractTableModel>
#include "serviceHeader/recetteservice.h"
#include "metiersHeader/recetteingredient.h"

class RecetteTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RecetteTableModel(RecetteService &service, QObject *parent = nullptr);

    void chargerRecette(int recetteId);

    // Surcharges du modèle
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    RecetteService &m_service;
    QList<RecetteIngredient> m_lignes;
    int m_recetteId = -1;
};

#endif // RECETETABLEMODEL_H
