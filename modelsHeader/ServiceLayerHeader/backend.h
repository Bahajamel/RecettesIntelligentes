#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include "dataHeader/databasemanager.h"

// DAO
#include "dataHeader/ingredientDAO.h"
#include "dataHeader/recetteDAO.h"
#include "dataHeader/recetteingredientdao.h"
#include "dataHeader/instructionDAO.h"

// Services
#include "modelsHeader/ServiceLayerHeader/ingredientService.h"
#include "modelsHeader/ServiceLayerHeader/instructionService.h"
#include "modelsHeader/ServiceLayerHeader/recetteService.h"

// Models
#include "modelsHeader/recettemodel.h"
#include "modelsHeader/instructiontreemodel.h"
#include "modelsHeader/recetteingredient.h"


class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

    RecetteTableModel* recetteModel();
    QList<RecetteIngredient> ingredientsDeRecette(int recetteId);
    void chargerInstructionsDansModele(InstructionTreeModel &model, int recetteId);
    InstructionService& instructionService();

public slots:
    void chargerRecettes();
    int creerRecette(const QString &titre, const QString &description);
    void ajouterIngredientARecette(int recetteId, const QString &nom, float qte, const QString &unite);
    int ajouterInstructionSimple(int recetteId, int parentId, const QString &texte);
    int ajouterInstructionComposee(int recetteId, int parentId, const QString &titre);
    void resetDatabase();
    void insererRecettesTest() ;
    Recette obtenirRecetteComplete(int id);
    bool mettreAJourRecette(int id, const QString &titre, const QString &description);
    bool supprimerRecette(int id);

signals :
    void erreur(const QString &message);
    void recettesModifiees();

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
