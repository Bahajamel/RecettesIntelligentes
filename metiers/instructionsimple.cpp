#include "metiersHeader/instructionsimple.h"

InstructionSimple::InstructionSimple(const QString &titre)
    : m_titre(titre)
{}

bool InstructionSimple::estSimple() const {
    return true ;
}

