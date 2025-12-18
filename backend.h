#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "dataHeader/databasemanager.h"

// DAO
#include "daoHeader/ingredientDAO.h"
#include "daoHeader/recetteDAO.h"
#include "daoHeader/recetteingredientdao.h"
#include "daoHeader/instructionDAO.h"

// Services
#include "serviceHeader/ingredientService.h"
#include "serviceHeader/instructionService.h"
#include "serviceHeader/recetteService.h"

// Models
#include "modelsHeader/recettemodel.h"


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    RecetteTableModel* recetteModel();

public slots:
    void chargerRecettes();
    int creerRecette(const QString &titre, const QString &description);
<<<<<<< HEAD
    void ajouterIngredientARecette(const int &id , const QString &nom , const float &qte , const QString &unite);
=======
    void ajouterIngredientARecette(int &id , QString &nom , float &qte , QString &unite);
>>>>>>> Baha

signals:
    void erreur(const QString &message);

private:
    DatabaseManager m_dbManager;

    // DAO
    RecetteDAO m_recetteDAO;
    IngredientDAO m_ingredientDAO;
    RecetteIngredientDAO m_riDAO;
    InstructionDAO m_instructionDAO;

    // Services
    IngredientService m_ingredientService;
    InstructionService m_instructionService;
    RecetteService m_recetteService;

    // Models
    RecetteTableModel m_recetteModel;
};

#endif


