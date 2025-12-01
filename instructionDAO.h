#ifndef INSTRUCTIONDAO_H
#define INSTRUCTIONDAO_H

#include <QSqlDatabase>
#include <QVector>
#include "instruction.h"

class InstructionDAO
{
public:
    InstructionDAO(QSqlDatabase& db);

    bool insert(const Instruction& inst);
    bool update(const Instruction& inst);
    bool remove(int id);
    QVector<Instruction> getByRecette(int recetteId);
    QVector<Instruction> getChildren(int parentId);

private:
    QSqlDatabase m_db;
};

#endif // INSTRUCTIONDAO_H
