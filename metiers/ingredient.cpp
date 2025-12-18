#include "metiersHeader/ingredient.h"

Ingredient::Ingredient()
    : m_id(-1), m_nom("")
{}

Ingredient::Ingredient(int id, const QString &nom)
    : m_id(id), m_nom(nom)
{}

int Ingredient::getId() const        { return m_id; }
QString Ingredient::getNom() const   { return m_nom; }

void Ingredient::setNom(QString nom) {
    this->m_nom = nom ;
}
