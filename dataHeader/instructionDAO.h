#ifndef INSTRUCTIONDAO_H
#define INSTRUCTIONDAO_H

#include <QSqlDatabase>
#include <QSharedPointer>
#include "modelsHeader/instruction.h"


class InstructionDAO
{
public:
    explicit InstructionDAO(const QSqlDatabase &db);

    int createSimple(int recetteId, int parentId, int ordre, const QString &texte);
    int createComposee(int recetteId, int parentId, int ordre, const QString &titre);

    QList<QSharedPointer<Instruction>> loadForRecette(int recetteId);

    bool deleteForRecette(int recetteId);
    QSharedPointer<Instruction> findById(int id);
    bool remove(int id);


private:
    QSqlDatabase m_db;

    QSharedPointer<Instruction> buildTree(
        int nodeId,
        const QMap<int, QVariantMap> &nodes,
        const QMap<int, QString> &simpleTexts,
        const QMap<int, QString> &composeeTitles
        );
};

#endif // INSTRUCTIONDAO_H
