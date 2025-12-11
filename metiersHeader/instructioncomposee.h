#ifndef INSTRUCTIONCOMPOSEE_H
#define INSTRUCTIONCOMPOSEE_H

#include "instruction.h"
#include <QString>
#include <QList>
#include <QSharedPointer>

/**
 * InstructionComposee :
 * représente une instruction pouvant contenir d'autres instructions.
 */
class InstructionComposee : public Instruction
{
public:
    InstructionComposee() = default;
    explicit InstructionComposee(const QString &titre);

    // ----------- Getters / Setters -----------
    QString getTitre() const;
    void setTitre(const QString &titre);

    // ----------- Gestion des enfants -----------
    void ajouterEnfant(const QSharedPointer<Instruction> &instr);
    const QList<QSharedPointer<Instruction>>& getEnfants() const;

    // Nombre d'enfants
    int getNombreEnfants() const;
    bool estSimple() const override { return false; }
    QString afficher() const override { return m_titre ;}
    QList<QSharedPointer<Instruction>> m_enfants;
private:
    QString m_titre;

};

#endif // INSTRUCTIONCOMPOSEE_H
