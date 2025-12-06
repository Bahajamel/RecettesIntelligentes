#include "ingredientDAO.h"
#include "ingredient.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

IngredientDAO::IngredientDAO(const QSqlDatabase &db)
    : m_db(db)
{}

int IngredientDAO::create(const Ingredient &ing)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO ingredient (nom) VALUES (?)");
    q.addBindValue(ing.getNom());

    if (!q.exec()) {
        qWarning() << "Ingredient create error:" << q.lastError();
        return -1;
    }
    return q.lastInsertId().toInt();
}

Ingredient IngredientDAO::findById(int id)
{
    Ingredient ing;
    QSqlQuery q(m_db);
    q.prepare("SELECT id, nom FROM ingredient WHERE id=?");
    q.addBindValue(id);
    if (q.exec() && q.next()) {
        ing.m_id = q.value(0).toInt();
        ing.m_nom = q.value(1).toString();
    }
    return ing;
}

Ingredient IngredientDAO::findByName(const QString &name)
{
    Ingredient ing;
    QSqlQuery q(m_db);
    q.prepare("SELECT id, nom FROM ingredient WHERE nom=?");
    q.addBindValue(name);

    if (q.exec() && q.next()) {
        ing.m_id = q.value(0).toInt();
        ing.m_nom = q.value(1).toString();
    }
    return ing;
}

int IngredientDAO::findOrCreate(const QString &name)
{
    Ingredient found = findByName(name);
    if (found.m_id != -1)
        return found.m_id;

    Ingredient ing;
    ing.m_nom = name;
    return create(ing);
}

QList<Ingredient> IngredientDAO::findAll()
{
    QList<Ingredient> list;
    QSqlQuery q("SELECT id, nom FROM ingredient", m_db);

    while (q.next()) {
        Ingredient ing;
        ing.m_id = q.value(0).toInt();
        ing.m_nom = q.value(1).toString();
        list.append(ing);
    }
    return list;
}

bool IngredientDAO::remove(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM ingredient WHERE id=?");
    q.addBindValue(id);
    return q.exec();
}
bool IngredientDAO::removeAll()
{
    QSqlQuery q(m_db);
    if (!q.exec("DELETE FROM ingredient")) {
        qWarning() << "Ingredient removeAll error:" << q.lastError();
        return false;
    }
    return true;
}

