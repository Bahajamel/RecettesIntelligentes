#include "dataHeader/databasemanager.h"
#include "daoHeader/recetteDAO.h"
#include "daoHeader/ingredientDAO.h"
#include "daoHeader/recetteingredientdao.h"
#include "daoHeader/instructionDAO.h"
#include "metiersHeader/unite.h"
#include <QSqlQuery>
#include <QDebug>

void initializeSampleRecipes(DatabaseManager &dbManager)
{
    QSqlDatabase db = dbManager.database();
    if (!db.isOpen()) {
        qWarning() << "Database not open for initialization";
        return;
    }
//forecec
    QSqlQuery deleteAll(db);
    deleteAll.exec("DELETE FROM instruction");
    deleteAll.exec("DELETE FROM recette_ingredient");
    deleteAll.exec("DELETE FROM recette");
    deleteAll.exec("DELETE FROM ingredient");
    qDebug() << "🗑️ Toutes les données supprimées - Réinitialisation forcée";

    RecetteDAO recetteDAO(db);
    IngredientDAO ingredientDAO(db);
    RecetteIngredientDAO riDAO(db);
    InstructionDAO instructionDAO(db);

    qDebug() << "✓ Initialisation des recettes d'exemple...";

    // Vérifier si des recettes existent déjà
    QSqlQuery checkQuery(db);
    checkQuery.exec("SELECT COUNT(*) FROM recette");
    int count = 0;
    if (checkQuery.next()) {
        count = checkQuery.value(0).toInt();
    }
    
    // Si des recettes existent, supprimer les doublons "Pizza Maison" s'ils existent
    // Si des recettes existent déjà, ne rien faire
    if (count > 0) {
        qDebug() << "✓ Des recettes existent déjà (" << count << "), pas d'initialisation";
        return;
    }

    qDebug() << "✓ Initialisation des recettes d'exemple...";
    
    // Si aucune recette ou seulement des doublons supprimés, initialiser
    if (count == 0) {
        qDebug() << "✓ Initialisation des recettes d'exemple...";
    } else {
        qDebug() << "✓ Des recettes existent déjà, pas d'initialisation";
        return;
    }

    // ========== 1. PIZZA MARGHERITA ==========
    int pizzaId = recetteDAO.creerRecette(
        "Pizza Margherita",
        "Une pizza classique italienne avec tomate, mozzarella et basilic frais. Simple et délicieuse !"
    );
    recetteDAO.mettreAJourRecetteComplete(pizzaId, "Pizza Margherita",
        "Une pizza classique italienne avec tomate, mozzarella et basilic frais. Simple et délicieuse !",
        "" // Image: Pizza Margherita - sera ajoutée via l'interface
    );

    // Ingrédients Pizza
    int farineId = ingredientDAO.findOrCreate("Farine");
    int levureId = ingredientDAO.findOrCreate("Levure de boulanger");
    int tomateId = ingredientDAO.findOrCreate("Tomates");
    int mozzarellaId = ingredientDAO.findOrCreate("Mozzarella");
    int basilicId = ingredientDAO.findOrCreate("Basilic frais");
    int huileId = ingredientDAO.findOrCreate("Huile d'olive");

    UNITE uniteG = UNITE::GRAMME;
    UNITE uniteP = UNITE::PIECE;
    UNITE uniteM = UNITE::MILLILITRE;
    
    riDAO.add(pizzaId, farineId, 500, uniteG);
    riDAO.add(pizzaId, levureId, 10, uniteG);
    riDAO.add(pizzaId, tomateId, 400, uniteG);
    riDAO.add(pizzaId, mozzarellaId, 200, uniteG);
    riDAO.add(pizzaId, basilicId, 10, uniteP);
    riDAO.add(pizzaId, huileId, 30, uniteM);

    // Instructions Pizza
    instructionDAO.createSimple(pizzaId, 0, 1, "Préparer la pâte en mélangeant farine, levure et eau");
    instructionDAO.createSimple(pizzaId, 0, 2, "Laisser reposer la pâte 1 heure");
    instructionDAO.createSimple(pizzaId, 0, 3, "Étaler la pâte et ajouter la sauce tomate");
    instructionDAO.createSimple(pizzaId, 0, 4, "Ajouter la mozzarella et cuire au four 12 min à 220°C");
    instructionDAO.createSimple(pizzaId, 0, 5, "Ajouter le basilic frais avant de servir");

    // ========== 2. SHAKSHUKA ==========
    int shakshukaId = recetteDAO.creerRecette(
        "Shakshuka",
        "Œufs pochés dans une sauce tomate épicée, parfait pour le brunch !"
    );
    recetteDAO.mettreAJourRecetteComplete(shakshukaId, "Shakshuka",
        "Œufs pochés dans une sauce tomate épicée, parfait pour le brunch !",
        "" // Image: Shakshuka - sera ajoutée via l'interface
    );

    int oignonId = ingredientDAO.findOrCreate("Oignon");
    int poivronId = ingredientDAO.findOrCreate("Poivron");
    int ailId = ingredientDAO.findOrCreate("Ail");
    int oeufId = ingredientDAO.findOrCreate("Œufs");
    int cuminId = ingredientDAO.findOrCreate("Cumin");
    int paprikaId = ingredientDAO.findOrCreate("Paprika");
    int coriandreId = ingredientDAO.findOrCreate("Coriandre fraîche");
    int fetaId = ingredientDAO.findOrCreate("Feta");

    riDAO.add(shakshukaId, oignonId, 1, uniteP);
    riDAO.add(shakshukaId, poivronId, 2, uniteP);
    riDAO.add(shakshukaId, ailId, 2, uniteP);
    riDAO.add(shakshukaId, tomateId, 400, uniteG);
    riDAO.add(shakshukaId, oeufId, 4, uniteP);
    riDAO.add(shakshukaId, cuminId, 5, uniteG);
    riDAO.add(shakshukaId, paprikaId, 5, uniteG);
    riDAO.add(shakshukaId, coriandreId, 20, uniteG);
    riDAO.add(shakshukaId, fetaId, 100, uniteG);

    instructionDAO.createSimple(shakshukaId, 0, 1, "Faire revenir l'oignon et le poivron dans l'huile");
    instructionDAO.createSimple(shakshukaId, 0, 2, "Ajouter l'ail, les épices et les tomates");
    instructionDAO.createSimple(shakshukaId, 0, 3, "Laisser mijoter 10 minutes");
    instructionDAO.createSimple(shakshukaId, 0, 4, "Casser les œufs dans la sauce et couvrir 5 minutes");
    instructionDAO.createSimple(shakshukaId, 0, 5, "Garnir de coriandre et feta");

    // ========== 3. PANCAKES AUX MYRTILLES ==========
    int pancakesId = recetteDAO.creerRecette(
        "Pancakes aux Myrtilles",
        "Des pancakes moelleux et dorés, généreusement garnis de myrtilles fraîches et de sirop d'érable."
    );
    recetteDAO.mettreAJourRecetteComplete(pancakesId, "Pancakes aux Myrtilles",
        "Des pancakes moelleux et dorés, généreusement garnis de myrtilles fraîches et de sirop d'érable.",
        "" // Image: Pancakes aux myrtilles - sera ajoutée via l'interface
    );

    int myrtillesId = ingredientDAO.findOrCreate("Myrtilles");
    int laitId = ingredientDAO.findOrCreate("Lait");
    int oeufPancakeId = oeufId; // Réutiliser œufs
    int sucreId = ingredientDAO.findOrCreate("Sucre");
    int beurreId = ingredientDAO.findOrCreate("Beurre");
    int siropId = ingredientDAO.findOrCreate("Sirop d'érable");

    riDAO.add(pancakesId, farineId, 200, uniteG);
    riDAO.add(pancakesId, sucreId, 30, uniteG);
    riDAO.add(pancakesId, laitId, 250, uniteM);
    riDAO.add(pancakesId, oeufPancakeId, 2, uniteP);
    riDAO.add(pancakesId, beurreId, 30, uniteG);
    riDAO.add(pancakesId, myrtillesId, 150, uniteG);
    riDAO.add(pancakesId, siropId, 50, uniteM);

    instructionDAO.createSimple(pancakesId, 0, 1, "Mélanger farine, sucre et levure dans un bol");
    instructionDAO.createSimple(pancakesId, 0, 2, "Dans un autre bol, battre les œufs avec le lait et le beurre fondu");
    instructionDAO.createSimple(pancakesId, 0, 3, "Mélanger les ingrédients humides avec les secs");
    instructionDAO.createSimple(pancakesId, 0, 4, "Ajouter les myrtilles à la pâte");
    instructionDAO.createSimple(pancakesId, 0, 5, "Cuire les pancakes dans une poêle beurrée 2-3 min par côté");
    instructionDAO.createSimple(pancakesId, 0, 6, "Servir avec sirop d'érable et myrtilles fraîches");

    // ========== 4. ARANCINI (CROQUETTES DE RIZ) ==========
    int aranciniId = recetteDAO.creerRecette(
        "Arancini Siciliennes",
        "Des croquettes de riz crémeuses farcies au fromage, panées et frites. Un délice italien !"
    );
    recetteDAO.mettreAJourRecetteComplete(aranciniId, "Arancini Siciliennes",
        "Des croquettes de riz crémeuses farcies au fromage, panées et frites. Un délice italien !",
        "" // Image: Arancini - sera ajoutée via l'interface
    );

    int rizId = ingredientDAO.findOrCreate("Riz arborio");
    int bouillonId = ingredientDAO.findOrCreate("Bouillon de poulet");
    int parmesanId = ingredientDAO.findOrCreate("Parmesan");
    int chapelureId = ingredientDAO.findOrCreate("Chapelure");
    int citronId = ingredientDAO.findOrCreate("Citron");

    UNITE uniteL = UNITE::LITRE;
    riDAO.add(aranciniId, rizId, 300, uniteG);
    riDAO.add(aranciniId, bouillonId, 750, uniteM);
    riDAO.add(aranciniId, oignonId, 1, uniteP);
    riDAO.add(aranciniId, parmesanId, 100, uniteG);
    riDAO.add(aranciniId, mozzarellaId, 150, uniteG);
    riDAO.add(aranciniId, oeufId, 2, uniteP);
    riDAO.add(aranciniId, chapelureId, 200, uniteG);
    riDAO.add(aranciniId, citronId, 1, uniteP);

    instructionDAO.createSimple(aranciniId,0, 1, "Faire cuire le riz dans le bouillon jusqu'à absorption");
    instructionDAO.createSimple(aranciniId,0, 2, "Laisser refroidir et ajouter parmesan et œuf");
    instructionDAO.createSimple(aranciniId,0, 3, "Former des boules et insérer un morceau de mozzarella au centre");
    instructionDAO.createSimple(aranciniId,0, 4, "Passer dans l'œuf battu puis la chapelure");
    instructionDAO.createSimple(aranciniId,0, 5, "Frire dans l'huile chaude jusqu'à dorure");
    instructionDAO.createSimple(aranciniId,0, 6, "Servir avec quartiers de citron");

    qDebug() << "✓ Recettes d'exemple initialisées avec succès !";
}

