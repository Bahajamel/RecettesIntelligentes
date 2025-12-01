#ifndef RECETTEMODEL_H
#define RECETTEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "recette.h"
#include "../database/recette_dao.h"

class RecetteModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit RecetteModel(QObject *parent = nullptr);

    // Qt Model overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitreRole,
        DescriptionRole
    };

    // CRUD
    bool chargerDepuisBD();
    bool ajouterRecette(const Recette &recette);
    bool supprimerRecette(int id);
    bool modifierRecette(const Recette &recette);

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<Recette> m_recettes;
    RecetteDAO m_recetteDAO;
};

#endif
