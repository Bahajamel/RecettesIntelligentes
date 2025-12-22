#include "modelsHeader/instructioncomposee.h"

// -------- Constructeur --------
InstructionComposee::InstructionComposee(const QString &titre)
    : m_titre(titre)
{}

// -------- Getters / Setters --------
QString InstructionComposee::getTitre() const
{
    return m_titre;
}

void InstructionComposee::setTitre(const QString &titre)
{
    m_titre = titre;
}

// -------- Gestion des enfants --------
void InstructionComposee::ajouterEnfant(const QSharedPointer<Instruction> &instr)
{
    if (!instr.isNull()) {
        m_enfants.append(instr);
    }
}

const QList<QSharedPointer<Instruction>>& InstructionComposee::getEnfants() const
{
    return m_enfants;
}

int InstructionComposee::getNombreEnfants() const
{
    return m_enfants.size();
}
