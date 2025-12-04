#include "instructionservice.h"

InstructionService::InstructionService(InstructionDAO &dao)
    : m_instDao(dao)
{}

// ------------------------
// Vérifie parent valide
// ------------------------
bool InstructionService::checkParentValide(int parentId, int recetteId)
{
    if (parentId == -1) return true;

    QSharedPointer<Instruction> parent = m_instDao.findById(parentId);
    return parent->recetteId == recetteId;
}

// ------------------------
// Ajouter instruction simple
// ------------------------
int InstructionService::ajouterSimple(int recetteId, int parentId, int ordre, const QString &texte)
{
    if (!checkParentValide(parentId, recetteId))
        return -1;

    return m_instDao.createSimple(recetteId, parentId, ordre, texte);
}

// ------------------------
// Ajouter instruction composée
// ------------------------
int InstructionService::ajouterComposee(int recetteId, int parentId, int ordre, const QString &titre)
{
    if (!checkParentValide(parentId, recetteId))
        return -1;

    return m_instDao.createComposee(recetteId, parentId, ordre, titre);
}

// ------------------------
// Supprimer instruction
// ------------------------
bool InstructionService::supprimer(int id)
{
    return m_instDao.remove(id);
}

// ------------------------
// Charger l'arbre complet
// ------------------------
QList<QSharedPointer<Instruction>> InstructionService::chargerArbre(int recetteId)
{
    return m_instDao.loadForRecette(recetteId);
}
