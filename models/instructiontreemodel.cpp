#include "modelsHeader/instructiontreemodel.h"
#include "metiersHeader/instructioncomposee.h"
#include "metiersHeader/instructionsimple.h"

InstructionTreeModel::InstructionTreeModel(
    InstructionService &service,
    QObject *parent)
    : QAbstractItemModel(parent), m_service(service)
{}


void InstructionTreeModel::chargerRecette(int recetteId)
{
    beginResetModel();

    // delete ancien arbre
    for (Node *n : m_all) delete n;
    m_all.clear();
    m_roots.clear();

    auto racines = m_service.chargerArbre(recetteId);

    for (auto &rootInstr : racines) {
        Node* r = buildNodeTree(rootInstr, nullptr);
        m_roots.append(r);
    }

    endResetModel();
}


QModelIndex InstructionTreeModel::index(int row, int col, const QModelIndex &parentIdx) const
{
    if (col != 0) return QModelIndex();

    Node *parent = nullptr;

    if (!parentIdx.isValid())
        parent = nullptr;
    else
        parent = static_cast<Node*>(parentIdx.internalPointer());

    Node *child = parent ? parent->children.value(row) : m_roots.value(row);

    if (!child) return QModelIndex();
    return createIndex(row, col, child);
}


QModelIndex InstructionTreeModel::parent(const QModelIndex &childIdx) const
{
    if (!childIdx.isValid()) return QModelIndex();

    Node *child = static_cast<Node*>(childIdx.internalPointer());
    if (!child || !child->parent) return QModelIndex();

    Node *parent = child->parent;

    int row;
    if (!parent->parent)
        row = m_roots.indexOf(parent);
    else
        row = parent->parent->children.indexOf(parent);

    return createIndex(row, 0, parent);
}


int InstructionTreeModel::rowCount(const QModelIndex &parentIdx) const
{
    Node *parent = nullptr;

    if (parentIdx.isValid())
        parent = static_cast<Node*>(parentIdx.internalPointer());

    return parent ? parent->children.size() : m_roots.size();
}


QVariant InstructionTreeModel::data(const QModelIndex &idx, int role) const
{
    if (!idx.isValid() || role != Qt::DisplayRole)
        return QVariant();

    Node *n = static_cast<Node*>(idx.internalPointer());
    if (n->instr->estSimple()) {
        auto s = n->instr.dynamicCast<InstructionSimple>();
        return s->afficher(); // ton texte
    } else {
        auto c = n->instr.dynamicCast<InstructionComposee>();
        return c->afficher(); // titre
    }
}



InstructionTreeModel::Node*
InstructionTreeModel::buildNodeTree(
    const QSharedPointer<Instruction> &instr,
    Node *parent)
{
    Node *node = new Node;
    node->instr = instr;
    node->parent = parent;

    m_all.append(node);

    if (!instr->estSimple()) {
        auto comp = instr.dynamicCast<InstructionComposee>();
        for (auto &childInstr : comp->m_enfants) {
            Node *child = buildNodeTree(childInstr, node);
            node->children.append(child);
        }
    }
    return node;
}

