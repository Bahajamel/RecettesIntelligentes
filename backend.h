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
#include "modelsHeader/ingredientmodel.h"
#include "modelsHeader/recettemodel.h"
#include "modelsHeader/recetteingredientmodel.h"


class Backend : public QObject
{
    Q_OBJECT

public:
    explicit Backend(QObject *parent = nullptr);

    // DAO
    IngredientDAO *ingredientDAO;
    RecetteDAO *recetteDAO;
    RecetteIngredientDAO *riDAO;
    InstructionDAO *instructionDAO;

    // Services
    IngredientService *ingredientService;
    RecetteService *recetteService;
    InstructionService *instructionService;

    // Models
    IngredientTableModel *ingredientModel;
    RecetteTableModel *recetteModel;
    RecetteIngredientTableModel *recetteIngredientModel;

private:
    DatabaseManager dbManager;
};

#endif
