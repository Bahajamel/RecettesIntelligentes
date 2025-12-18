#ifndef RECETTEINGREDIENTMODEL_H
#define RECETTEINGREDIENTMODEL_H

#include <QAbstractTableModel>
#include "metiersHeader/recetteingredient.h"

class RecetteIngredientTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RecetteIngredientTableModel(QObject *parent = nullptr);

    // Mise à jour de la liste
    void setRecetteIngredients(const QList<RecetteIngredient> &list);

    // QAbstractTableModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QList<RecetteIngredient> m_items;
};

#endif // RECETTEINGREDIENTTABLEMODEL_H
