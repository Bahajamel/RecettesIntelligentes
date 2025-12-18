#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>

class Instruction
{
public:
    Instruction();
    Instruction(int id, int ordre , const QString &contenu);
    virtual ~Instruction();

    int getId() const;
    virtual QString getContenu() const;
    int getOrdre() const ;
    virtual bool estSimple() const = 0 ;
    virtual QString afficher() const = 0;
    int m_id;
    QString m_contenu;
    int m_ordre ;
    int recetteId = -1;
};

#endif




