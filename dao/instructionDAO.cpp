#include "daoHeader/instructionDAO.h"
#include "metiersHeader/instruction.h"
#include "metiersHeader/instructioncomposee.h"
#include "metiersHeader/instructionsimple.h"
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

    q.prepare(
        "INSERT INTO instruction (recette_id, parent_id, ordre, type) "
        "VALUES (?, ?, ?, 'simple')"
        );

    q.addBindValue(recetteId);

    // 🔥 NULL SQL correct
    if (parentId == -1)
        q.addBindValue(QVariant(QVariant::Int)); // NULL
    else
        q.addBindValue(parentId);

    q.addBindValue(ordre);

    if (!q.exec()) {
        qWarning() << "Error create instruction simple:" << q.lastError();
        return -1;
    }

    int idInstr = q.lastInsertId().toInt();

    QSqlQuery qi(m_db);
    qi.prepare(
        "INSERT INTO instruction_simple (instruction_id, texte) "
        "VALUES (?, ?)"
        );
    qi.addBindValue(idInstr);
    qi.addBindValue(texte);

    if (!qi.exec()) {
        qWarning() << "Error insert instruction_simple:" << qi.lastError();
        return -1;
    }

    return idInstr;
}


// ------------------ CREATE Composée --------------------
int InstructionDAO::createComposee(int recetteId, int parentId, int ordre, const QString &titre)
{
    QSqlQuery q(m_db);

    q.prepare(
        "INSERT INTO instruction (recette_id, parent_id, ordre, type) "
        "VALUES (?, ?, ?, 'composee')"
        );

    q.addBindValue(recetteId);

    if (parentId == -1)
        q.addBindValue(QVariant(QVariant::Int)); // NULL
    else
        q.addBindValue(parentId);

    q.addBindValue(ordre);

    if (!q.exec()) {
        qWarning() << "Error create instruction composee:" << q.lastError();
        return -1;
    }

    int idInstr = q.lastInsertId().toInt();

    QSqlQuery qi(m_db);
    qi.prepare(
        "INSERT INTO instruction_composee (instruction_id, titre) "
        "VALUES (?, ?)"
        );
    qi.addBindValue(idInstr);
    qi.addBindValue(titre);

    if (!qi.exec()) {
        qWarning() << "Error insert instruction_composee:" << qi.lastError();
        return -1;
    }

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

    if (!q.exec()) {
        qDebug() << "❌ ERREUR SQL instruction:" << q.lastError().text();
        return QList<QSharedPointer<Instruction>>();
    }

    qDebug() << "🔍 Recherche instructions pour recette" << recetteId;
    int count = 0;
    while (q.next()) {
        QVariantMap map;
        int id = q.value("id").toInt();
        map["parent"] = q.value("parent_id");
        map["type"] = q.value("type");
        map["ordre"] = q.value("ordre");
        nodes[id] = map;
        count++;
        qDebug() << "  → Instruction trouvée: ID=" << id << "type=" << map["type"];
    }
    qDebug() << "✅ Total:" << count << "instructions trouvées";

    // 2) Charger simples
    QSqlQuery s(m_db);
    s.prepare("SELECT instruction_id, texte FROM instruction_simple WHERE instruction_id IN (SELECT id FROM instruction WHERE recette_id=?)");
    s.addBindValue(recetteId);
    if (!s.exec()) {
        qDebug() << "❌ ERREUR SQL instruction_simple:" << s.lastError().text();
    } else {
        while (s.next()) {
            simpleTexts[s.value(0).toInt()] = s.value(1).toString();
            qDebug() << "  → Simple:" << s.value(1).toString();
        }
    }

    // 3) Charger composées
    QSqlQuery c(m_db);
    c.prepare("SELECT instruction_id, titre FROM instruction_composee WHERE instruction_id IN (SELECT id FROM instruction WHERE recette_id=?)");
    c.addBindValue(recetteId);
    if (!c.exec()) {
        qDebug() << "❌ ERREUR SQL instruction_composee:" << c.lastError().text();
    } else {
        while (c.next()) {
            composeeTitles[c.value(0).toInt()] = c.value(1).toString();
            qDebug() << "  → Composée:" << c.value(1).toString();
        }
    }

    // 4) Trouver racines et construire l'arbre
    QList<QSharedPointer<Instruction>> roots;
    for (int id : nodes.keys()) {
        if (nodes[id]["parent"].isNull()) {
            roots.append(buildTree(id, nodes, simpleTexts, composeeTitles));
        }
    }

    // 5) Trier les racines par 'ordre'
    std::sort(roots.begin(), roots.end(),
              [](auto a, auto b){ return a->m_ordre < b->m_ordre; });

    qDebug() << "📦 Retour de" << roots.size() << "instructions racines";
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


    if (type == "simple") {
        instr.reset(new InstructionSimple(simpleTexts[nodeId]));
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
    // lire les infos générales de instruction
    QSqlQuery q(m_db);
    q.prepare(R"(
        SELECT id, recette_id, parent_id, ordre, type
        FROM instruction
        WHERE id = :id
    )");

    q.bindValue(":id", id);

    if (!q.exec()) {
        qWarning() << "findById error:" << q.lastError();
        return nullptr;
    }

    if (!q.next())
        return nullptr;

    QString type = q.value("type").toString();
    int ordre = q.value("ordre").toInt();
    int recetteId = q.value("recette_id").toInt();

    QSharedPointer<Instruction> instr;

    if (type == "simple") {
        // LIRE LE TEXTE DANS instruction_simple
        QSqlQuery qs(m_db);
        qs.prepare("SELECT texte FROM instruction_simple WHERE instruction_id = :id");
        qs.bindValue(":id", id);
        qs.exec();
        qs.next();

        QString texte = qs.value(0).toString();

        instr.reset(new InstructionSimple(texte));
    }
    else {
        // LIRE LE TITRE DANS instruction_composee
        QSqlQuery qc(m_db);
        qc.prepare("SELECT titre FROM instruction_composee WHERE instruction_id = :id");
        qc.bindValue(":id", id);
        qc.exec();
        qc.next();

        QString titre = qc.value(0).toString();

        instr.reset(new InstructionComposee(titre));
    }

    instr->m_id        = id;
    instr->m_ordre     = ordre;
    instr->recetteId = recetteId;

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


