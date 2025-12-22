#ifndef INSTRUCTIONTREEMODEL_H
#define INSTRUCTIONTREEMODEL_H

#include <QAbstractItemModel>
#include "ServiceLayerHeader/instructionservice.h"

class InstructionTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    InstructionTreeModel(InstructionService &service, QObject *parent = nullptr);

    QModelIndex index(int row, int col, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override { return 1; }
    QVariant data(const QModelIndex &index, int role) const override;

    void chargerRecette(int recetteId);

private:
    struct Node {
        QSharedPointer<Instruction> instr;
        Node *parent = nullptr;
        QList<Node*> children;
    };

    InstructionService &m_service;
    QList<Node*> m_roots;  // racines
    QList<Node*> m_all;    // pour delete
    Node* buildNodeTree(const QSharedPointer<Instruction>& instr, Node *parent);
};

#endif
