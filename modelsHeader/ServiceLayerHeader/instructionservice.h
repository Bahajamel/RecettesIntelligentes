#ifndef INSTRUCTIONSERVICE_H
#define INSTRUCTIONSERVICE_H

#include "dataHeader/instructiondao.h"

class InstructionService
{
public:
    InstructionService(InstructionDAO &dao);

    int ajouterSimple(int recetteId, int parentId, int ordre, const QString &texte);
    int ajouterComposee(int recetteId, int parentId, int ordre, const QString &titre);
    bool supprimer(int id);
    QList<QSharedPointer<Instruction>> chargerArbre(int recetteId);
    void afficherArbre(const QList<QSharedPointer<Instruction>> &racines);


private:
    bool checkParentValide(int parentId, int recetteId);

private:
    InstructionDAO &m_instDao;
    void afficherNoeud(const QSharedPointer<Instruction> &instr, int profondeur);
};

#endif
