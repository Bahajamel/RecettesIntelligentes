#ifndef INSTRUCTION_SIMPLE_H
#define INSTRUCTION_SIMPLE_H

#include "instruction.h"

class InstructionSimple : public Instruction
{
public:
    InstructionSimple(const QString &titre);
    bool estSimple() const ;
private :
    QString m_titre ;
};

#endif
