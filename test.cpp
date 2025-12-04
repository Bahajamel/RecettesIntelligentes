#include <QtTest>
#include "databasemanager.h"
#include "recetteingredientdao.h"
#include "ingredientservice.h"
#include "instructionservice.h"
#include "recetteservice.h"

class TestRecetteService : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase()
    {
        // 1. Base SQLite en mémoire
        DatabaseManager dbMan(":memory:");
        QVERIFY(dbMan.open());

        // 2. Créer RecetteIngredientDAO
        QSqlDatabase dbRef = dbMan.database();
        RecetteIngredientDAO riDao(dbRef);

        // 3.Créer IngredientDAO
        IngredientDAO inDao(dbRef) ;

        // 4. Créer InstructionDAO
        InstructionDAO iDao (dbRef) ;

        // 5. Créer RecetteDAO
        RecetteDAO rDao (dbRef) ;

        // 6. Créer les services (selon leurs constructeurs réels)
        IngredientService ingService(inDao , riDao );
        InstructionService instService(iDao);

        // 7. Créer RecetteService
        RecetteService service(rDao,riDao, ingService, instService );

        // 8. Ajouter recette et ingrédient pour le test
        int recetteId = RecetteDAO::creerRecette("Tarte", "Test tarte");

        int ingId = ingService.ajouterIngredient("Sucre"); // ou méthode réelle de ton service

        UNITE unite = UNITE::GRAMME;
        bool ok = service.ajouterIngredient(recetteId, ingService.getIngredient(ingId), 50.0f, unite);
        QVERIFY(ok);

        // 9. Lire et vérifier
        QList<Ingredient> list = service.ingredientsDeRecette(recetteId);
        QCOMPARE(list.size(), 1);
        QCOMPARE(list[0].getNom(), QString("Sucre"));
    }
};



