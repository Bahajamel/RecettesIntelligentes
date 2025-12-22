#include "dataHeader/recetteingredientdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

RecetteIngredientDAO::RecetteIngredientDAO(const QSqlDatabase &db)
    : m_db(db)
{}

// ---------------- CREATE ----------------
int RecetteIngredientDAO::create(int recetteId, const RecetteIngredient &ri)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO recette_ingredient (recette_id, ingredient_id, quantite, unite) "
              "VALUES (?, ?, ?, ?)");

    q.addBindValue(recetteId);
    q.addBindValue(ri.getIngredientId());
    q.addBindValue(ri.getQuantite());
    q.addBindValue(uniteToString(ri.getUnite()));

    if (!q.exec()) {
        qWarning() << "Error insert recette_ingredient:" << q.lastError();
        return -1;
    }

    return q.lastInsertId().toInt();
}

// ---------------- FIND BY RECETTE ----------------
QList<RecetteIngredient> RecetteIngredientDAO::findByRecette(int recetteId)
{
    QList<RecetteIngredient> list;

    QSqlQuery q(m_db);
    q.prepare(R"(
      SELECT ri.id, i.id, i.nom, ri.quantite, ri.unite
      FROM recette_ingredient ri
      JOIN ingredient i ON ri.ingredient_id = i.id
      WHERE ri.recette_id = ?
    )");
    q.addBindValue(recetteId);

    if (!q.exec()) return list;

    while (q.next()) {
        Ingredient ing(q.value(1).toInt(), q.value(2).toString());

        RecetteIngredient ri(
            ing,
            q.value(3).toFloat(),
            stringToUnite(q.value(4).toString())
            );
        ri.recetteId = recetteId;

        list.append(ri);
    }

    return list;
}
// ---------------- FIND BY INGREDIENT  ----------------
QList<int> RecetteIngredientDAO::findRecettesByIngredient(int ingredientId)
{
    QList<int> recettes;

    QSqlQuery q(m_db);
    q.prepare("SELECT recette_id FROM recette_ingredient WHERE ingredient_id = :id");
    q.bindValue(":id", ingredientId);

    if (!q.exec()) {
        qWarning() << "Erreur SELECT findRecettesByIngredient:" << q.lastError();
        return recettes;
    }

    while (q.next()) {
        recettes.append(q.value(0).toInt());
    }

    return recettes;
}

// ---------------- FIND ONE ----------------
RecetteIngredient RecetteIngredientDAO::findOne(int id)
{
    RecetteIngredient ri;

    QSqlQuery q(m_db);
    q.prepare(R"(
      SELECT ri.recette_id, i.id, i.nom, ri.quantite, ri.unite
      FROM recette_ingredient ri
      JOIN ingredient i ON ri.ingredient_id = i.id
      WHERE ri.id = ?
    )");
    q.addBindValue(id);

    if (q.exec() && q.next()) {
        ri.recetteId = q.value(0).toInt();

        Ingredient ing(q.value(1).toInt(), q.value(2).toString());
        ri.setIngredient(ing);

        ri.setQuantite(q.value(3).toFloat());
        ri.setUnite(stringToUnite(q.value(4).toString()));
    }

    return ri;
}

// ----------------FindIngredientsRecettes-
QList<Ingredient> RecetteIngredientDAO::findIngredients(int recetteId)
{
    QList<Ingredient> list;

    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT ingredient.id, ingredient.nom
        FROM recette_ingredient ri
        JOIN ingredient ON ingredient.id = ri.ingredient_id
        WHERE ri.recette_id = :r
    )");

    q.bindValue(":r", recetteId);

    if (!q.exec()) {
        qWarning() << "Erreur RecetteIngredientDAO::findIngredients:" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        int id = q.value(0).toInt();
        QString nom = q.value(1).toString();
        list.append(Ingredient(id, nom));
    }

    return list;
}

// ---------------- UPDATE ----------------
bool RecetteIngredientDAO::update(int id, const RecetteIngredient &ri)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
      UPDATE recette_ingredient
      SET ingredient_id=?, quantite=?, unite=?
      WHERE id=?
    )");

    q.addBindValue(ri.getIngredientId());
    q.addBindValue(ri.getQuantite());
    q.addBindValue(uniteToString(ri.getUnite()));
    q.addBindValue(id);

    return q.exec();
}

// ---------------- DELETE ----------------
bool RecetteIngredientDAO::remove(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM recette_ingredient WHERE id=?");
    q.addBindValue(id);
    return q.exec();
}

bool RecetteIngredientDAO::removeByRecette(int recetteId)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM recette_ingredient WHERE recette_id=?");
    q.addBindValue(recetteId);
    return q.exec();
}

// Pour ajouter un ingredient dans
bool RecetteIngredientDAO::add(int recetteId, int ingredientId, float quantite, UNITE &unite)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        INSERT INTO recette_ingredient (recette_id, ingredient_id, quantite, unite)
        VALUES (:r, :i, :q, :u)
    )");

    q.bindValue(":r", recetteId);
    q.bindValue(":i", ingredientId);
    q.bindValue(":q", quantite);
    q.bindValue(":u",uniteToString(unite));

    if (!q.exec()) {
        qWarning() << "Erreur RecetteIngredientDAO::add:" << q.lastError().text();
        return false;
    }

    return true;
}

