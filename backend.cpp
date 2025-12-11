#include "backend.h"

Backend::Backend(QObject *parent)
    : QObject(parent),
    dbManager("app.db")
{
    dbManager.open();

    // DAO
    ingredientDAO = new IngredientDAO(dbManager.database());
    recetteDAO = new RecetteDAO(dbManager.database());
    riDAO = new RecetteIngredientDAO(dbManager.database());
    instructionDAO = new InstructionDAO(dbManager.database());

    // SERVICES
    ingredientService = new IngredientService(*ingredientDAO, *riDAO);
    instructionService = new InstructionService(*instructionDAO);
    recetteService = new RecetteService(*recetteDAO, *riDAO, *ingredientService, *instructionService);

    // MODELS
    ingredientModel = new IngredientTableModel(*ingredientService);
    recetteModel = new RecetteTableModel(*recetteService);
    recetteIngredientModel = new RecetteIngredientTableModel();
}
