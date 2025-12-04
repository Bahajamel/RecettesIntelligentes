#include <QCoreApplication>
#include <QSqlDatabase>
#include <QDebug>
#include "databasemanager.h"
#include "recetteingredientdao.h"
#include "ingredientDAO.h"
#include "ingredient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Drivers disponibles :" << QSqlDatabase::drivers();

    DatabaseManager db("test.db");
    db.open();

    RecetteIngredientDAO ridb(db.database());
    IngredientDAO idao(db.database());

    // 1) créer un ingrédient
    Ingredient ing1;
    ing1.setNom("Sucre");
    int ingId = idao.create(ing1);

    // 2) créer un RecetteIngredient
    RecetteIngredient ri(Ingredient(ingId, "Sucre"), 100.0, UNITE::GRAMME);
    int id = ridb.create(1, ri); // recette_id = 1

    qDebug() << "ID créé =" << id;

    // 3) lire
    RecetteIngredient r2 = ridb.findOne(id);
    qDebug() << "Quantité =" << r2.getQuantite();

    // 4) update
    ri.setQuantite(150);
    ridb.update(id, ri);

    // 5) relecture
    RecetteIngredient r3 = ridb.findOne(id);
    qDebug() << "Nouvelle quantité =" << r3.getQuantite();

    // 6) suppression
    ridb.remove(id);


    return a.exec();
}
