#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>

class Instruction
{
public:
    Instruction();
    Instruction(int id, const QString &contenu);
    virtual ~Instruction();

    int getId() const;
    virtual QString getContenu() const;
    bool estSimple() ;

protected:
    int m_id;
    QString m_contenu;
};

#endif

