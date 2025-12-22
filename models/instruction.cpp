#include "modelsHeader/instruction.h"

Instruction::Instruction()
    : m_id(-1),m_contenu("") , m_ordre(0)
{}

Instruction::Instruction(int id, int ordre , const QString &contenu)
    : m_id(id),  m_contenu(contenu) , m_ordre(ordre)
{}

Instruction::~Instruction() {}

int Instruction::getId() const {
    return m_id;
}

QString Instruction::getContenu() const {
    return m_contenu;
}

int Instruction::getOrdre() const {
    return m_ordre ;
}
