#include "instructionDAO.h"
#include "instruction.h"
#include "instructioncomposee.h"
#include "instructionsimple.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

InstructionDAO::InstructionDAO(const QSqlDatabase &db)
    : m_db(db)
{}

// ------------------ CREATE Simple --------------------
int InstructionDAO::createSimple(int recetteId, int parentId, int ordre, const QString &texte)
{
    QSqlQuery q(m_db);

    q.prepare("INSERT INTO instruction (recette_id, parent_id, ordre, type) "
              "VALUES (?, ?, ?, 'simple')");
    q.addBindValue(recetteId);
    q.addBindValue(parentId == -1 ? QVariant(): QVariant::fromValue(parentId));
    q.addBindValue(ordre);

    if (!q.exec()) {
        qWarning() << "Error create instruction simple:" << q.lastError();
        return -1;
    }

    int idInstr = q.lastInsertId().toInt();

    QSqlQuery qi(m_db);
    qi.prepare("INSERT INTO instruction_simple (instruction_id, texte) VALUES (?, ?)");
    qi.addBindValue(idInstr);
    qi.addBindValue(texte);

    qi.exec();

    return idInstr;
}

// ------------------ CREATE Composée --------------------
int InstructionDAO::createComposee(int recetteId, int parentId, int ordre, const QString &titre)
{
    QSqlQuery q(m_db);

    q.prepare("INSERT INTO instruction (recette_id, parent_id, ordre, type) "
              "VALUES (?, ?, ?, 'composee')");
    q.addBindValue(recetteId);
    q.addBindValue(parentId == -1 ? QVariant() : QVariant::fromValue(parentId));
    q.addBindValue(ordre);

    if (!q.exec()) {
        qWarning() << "Error create instruction composee:" << q.lastError();
        return -1;
    }

    int idInstr = q.lastInsertId().toInt();

    QSqlQuery qi(m_db);
    qi.prepare("INSERT INTO instruction_composee (instruction_id, titre) VALUES (?, ?)");
    qi.addBindValue(idInstr);
    qi.addBindValue(titre);

    qi.exec();

    return idInstr;
}

// ------------------ LOAD tree --------------------
QList<QSharedPointer<Instruction>> InstructionDAO::loadForRecette(int recetteId)
{
    QMap<int, QVariantMap> nodes;
    QMap<int, QString> simpleTexts;
    QMap<int, QString> composeeTitles;

    // 1) Charger les nœuds instruction
    QSqlQuery q(m_db);
    q.prepare("SELECT id, parent_id, type, ordre FROM instruction WHERE recette_id=?");
    q.addBindValue(recetteId);
    q.exec();

    while (q.next()) {
        QVariantMap map;
        int id = q.value("id").toInt();
        map["parent"] = q.value("parent_id");
        map["type"] = q.value("type");
        map["ordre"] = q.value("ordre");
        nodes[id] = map;
    }

    // 2) Charger simples
    QSqlQuery s(m_db);
    s.exec("SELECT instruction_id, texte FROM instruction_simple");
    while (s.next()) {
        simpleTexts[s.value(0).toInt()] = s.value(1).toString();
    }

    // 3) Charger composées
    QSqlQuery c(m_db);
    c.exec("SELECT instruction_id, titre FROM instruction_composee");
    while (c.next()) {
        composeeTitles[c.value(0).toInt()] = c.value(1).toString();
    }

    // 4) Trouver racines et construire l’arbre
    QList<QSharedPointer<Instruction>> roots;
    for (int id : nodes.keys()) {
        if (nodes[id]["parent"].isNull()) {
            roots.append(buildTree(id, nodes, simpleTexts, composeeTitles));
        }
    }

    // 5) Trier les racines par 'ordre'
    std::sort(roots.begin(), roots.end(),
              [](auto a, auto b){ return a->m_ordre < b->m_ordre; });

    return roots;
}

QSharedPointer<Instruction> InstructionDAO::buildTree(
    int nodeId,
    const QMap<int, QVariantMap> &nodes,
    const QMap<int, QString> &simpleTexts,
    const QMap<int, QString> &composeeTitles)
{
    QString type = nodes[nodeId]["type"].toString();
    int ordre = nodes[nodeId]["ordre"].toInt();

    QSharedPointer<Instruction> instr;
    instr.reset(new InstructionSimple(simpleTexts[nodeId]));

    if (type == "simple") {
    } else {
        instr.reset(new InstructionComposee(composeeTitles[nodeId]));
    }

    instr->m_id = nodeId;
    instr->m_ordre = ordre;

    // Chercher les enfants
    QList<int> children;
    for (int id : nodes.keys()) {
        if (!nodes[id]["parent"].isNull() &&
            nodes[id]["parent"].toInt() == nodeId)
        {
            children.append(id);
        }
    }

    // Tri des enfants
    std::sort(children.begin(), children.end(),
              [&](int a, int b){
                  return nodes[a]["ordre"].toInt() < nodes[b]["ordre"].toInt();
              });

    // Construire et ajouter enfants
    for (int cid : children) {
        auto child = buildTree(cid, nodes, simpleTexts, composeeTitles);
        if (!child.isNull()) {
            if (!instr->estSimple()) {
                auto comp = instr.dynamicCast<InstructionComposee>();
                comp->ajouterEnfant(child);
            }
        }
    }

    return instr;
}

// ------------------ DELETE all for recette --------------------
bool InstructionDAO::deleteForRecette(int recetteId)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM instruction WHERE recette_id=?");
    q.addBindValue(recetteId);
    return q.exec();
}
// --------------------- FINDById instruction --------------------
QSharedPointer<Instruction> InstructionDAO::findById(int id)
{
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT id, recette_id, parent, ordre, type, texte, titre
        FROM instruction
        WHERE id = :id
    )");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qWarning() << "InstructionDAO::findById exec error:" << q.lastError();
        return QSharedPointer<Instruction>(nullptr);
    }

    if (!q.next())
        return QSharedPointer<Instruction>(nullptr);

    QString type = q.value("type").toString();
    int ordre = q.value("ordre").toInt();

    QSharedPointer<Instruction> instr;

    if (type == "simple") {
        QString texte = q.value("texte").toString();
        instr.reset(new InstructionSimple(texte));
    }
    else {
        QString titre = q.value("titre").toString();
        instr.reset(new InstructionComposee(titre));
    }

    instr->m_id    = q.value("id").toInt();
    instr->m_ordre = ordre;
    instr->recetteId = q.value("recette_id").toInt();
    return instr;
}
// ---------------------- DELETE instruction ----------------------------
bool InstructionDAO::remove(int id)
{
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM instruction WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec()) {
        qWarning() << "InstructionDAO::remove error:" << q.lastError();
        return false;
    }

    return true;
}

