#ifndef INSTRUCTION_SIMPLE_H
#define INSTRUCTION_SIMPLE_H

#include "instruction.h"

class InstructionSimple : public Instruction
{
public:
    InstructionSimple(int id, const QString &contenu);
};

#endif
