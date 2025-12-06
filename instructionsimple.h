#ifndef INSTRUCTION_SIMPLE_H
#define INSTRUCTION_SIMPLE_H

#include "instruction.h"

class InstructionSimple : public Instruction
{
public:
    InstructionSimple(const QString &titre);
    bool estSimple() const override ;
    QString afficher() const override { return m_titre  ; };
private :
    QString m_titre ;
};

#endif
