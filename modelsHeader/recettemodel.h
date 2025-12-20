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

<<<<<<< HEAD
    // Récupérer une recette à partir d'une ligne (pour afficher les détails)
    Recette recetteAt(int row) const;
=======
    // Get recipes
    QList<Recette> getRecettes() const;
    Recette getRecette(int row) const;

>>>>>>> 3567aa235b818089fe94588a01d93cf16570992a
private:
    RecetteService m_service ;
    QList<Recette> m_recettes;

};

#endif
