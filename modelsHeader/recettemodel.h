#ifndef RECETETABLEMODEL_H
#define RECETETABLEMODEL_H

#include <QAbstractTableModel>
#include "metiersHeader/recette.h"
#include "serviceHeader/recetteservice.h"

class RecetteTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RecetteTableModel(RecetteService &recetteservice ,QObject *parent = nullptr  );

    // appelée par Backend
    void setRecettes(const QList<Recette> &recettes);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    void recharger();

    // Récupérer une recette à partir d'une ligne (pour afficher les détails)
    Recette recetteAt(int row) const;
private:
    RecetteService m_service ;
    QList<Recette> m_recettes;

};

#endif
