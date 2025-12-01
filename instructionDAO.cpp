#include "instructionDAO.h"
#include "instruction.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

InstructionDAO::InstructionDAO(QSqlDatabase& db)
    : m_db(db)
{}

bool InstructionDAO::insert(const Instruction& inst)
{
    QSqlQuery q(m_db);
    q.prepare("INSERT INTO instruction (recette_id, contenu, type, ordre, parent_id) "
              "VALUES (?, ?, ?, ?, ?)");
    q.addBindValue(inst.getrecetteId());
    q.addBindValue(inst.getcontenu());
    q.addBindValue(inst.type());
    q.addBindValue(inst.ordre());
    q.addBindValue(inst.parentId());

    return q.exec();
}

bool InstructionDAO::update(const Instruction& inst)
{
    QSqlQuery q(m_db);
    q.prepare("UPDATE instruction SET contenu=?, type=?, ordre=?, parent_id=? "
              "WHERE id=?");
    q.addBindValue(inst.contenu());
    q.addBindValue(inst.type());
    q.addBindValue(inst.ordre());
    q.addBindValue(inst.parentId());
    q.addBindValue(inst.id());

    return q.exec();
}

bool InstructionDAO::remove(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM instruction WHERE id=?");
    q.addBindValue(id);
    return q.exec();
}

QVector<Instruction> InstructionDAO::getByRecette(int recetteId)
{
    QVector<Instruction> list;
    QSqlQuery q(m_db);
    q.prepare("SELECT id, recette_id, contenu, type, ordre, parent_id "
              "FROM instruction WHERE recette_id=? ORDER BY ordre ASC");
    q.addBindValue(recetteId);
    q.exec();

    while (q.next()) {
        list.append(Instruction(
            q.value(0).toInt(),
            q.value(1).toInt(),
            q.value(2).toString(),
            q.value(3).toString(),
            q.value(4).toInt(),
            q.value(5).toInt()
            ));
    }
    return list;
}

QVector<Instruction> InstructionDAO::getChildren(int parentId)
{
    QVector<Instruction> list;

    QSqlQuery q(m_db);
    q.prepare("SELECT id, recette_id, contenu, type, ordre, parent_id "
              "FROM instruction WHERE parent_id=? ORDER BY ordre ASC");
    q.addBindValue(parentId);
    q.exec();

    while (q.next()) {
        list.append(Instruction(
            q.value(0).toInt(),
            q.value(1).toInt(),
            q.value(2).toString(),
            q.value(3).toString(),
            q.value(4).toInt(),
            q.value(5).toInt()
            ));
    }
    return list;
}
