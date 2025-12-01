#include "instruction.h"

Instruction::Instruction()
    : m_id(-1), m_contenu("")
{}

Instruction::Instruction(int id, const QString &contenu)
    : m_id(id), m_contenu(contenu)
{}

Instruction::~Instruction() {}

int Instruction::getId() const {
    return m_id;
}

QString Instruction::getContenu() const {
    return m_contenu;
}
