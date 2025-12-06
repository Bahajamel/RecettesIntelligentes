#include <QCoreApplication>
#include <QDebug>

// Qt SQL
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

// Ton backend
#include "databaseManager.h"
#include "recetteDAO.h"
#include "recetteIngredientdao.h"
#include "ingredientDAO.h"
#include "IngredientService.h"
#include "instructionDAO.h"
#include "instructionService.h"
#include "recetteService.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    qDebug() << "\n=== TEST InstructionService ===";
    DatabaseManager dbm("test_instruction.db");
    if (!dbm.open()) {
        qWarning() << "Erreur ouverture DB !";
        return 0;
    }

    InstructionDAO instDAO(dbm.database());
    InstructionService instService(instDAO) ;
    IngredientDAO ingDAO(dbm.database()) ;
    RecetteIngredientDAO riDAO(dbm.database()) ;
    IngredientService ingService(ingDAO , riDAO) ;
    RecetteDAO rDAO (dbm.database()) ;
    RecetteService recetteService(rDAO , riDAO , ingService, instService) ;



    int recetteId = recetteService.creerRecette("Pâte à tarte", "Préparation de base");

    // -------------------------
    // 1) Racine 1
    // -------------------------
    int root1 = instService.ajouterComposee(recetteId, -1, 1, "Préparer la pâte");
    qDebug() << "Root 1 (composee) =" << root1;

    // enfants du root1
    int e1 = instService.ajouterSimple(recetteId, root1, 1, "Mélanger la farine");
    qDebug() << "  Enfant simple 1 =" << e1;

    int e2 = instService.ajouterSimple(recetteId, root1, 2, "Ajouter l'eau");
    qDebug() << "  Enfant simple 2 =" << e2;

    // -------------------------
    // 2) Racine 2
    // -------------------------
    int root2 = instService.ajouterComposee(recetteId, -1, 2, "Cuisson");
    qDebug() << "Root 2 (composee) =" << root2;

    int e3 = instService.ajouterSimple(recetteId, root2, 1, "Cuire 20 minutes");
    qDebug() << "  Enfant simple cuisson =" << e3;

    // -------------------------
    // AFFICHAGE ARBRE
    // -------------------------
    auto arbre = instService.chargerArbre(recetteId);
    instService.afficherArbre(arbre);




    return 0;
}

