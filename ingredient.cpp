#include "ingredient.h"

Ingredient::Ingredient()
    : m_id(-1), m_nom(""), m_quantite(0.0f), m_unite(UNITE::GRAMME)
{}

Ingredient::Ingredient(int id, const QString &nom, float quantite, UNITE unite)
    : m_id(id), m_nom(nom), m_quantite(quantite), m_unite(unite)
{}

int Ingredient::getId() const        { return m_id; }
QString Ingredient::getNom() const   { return m_nom; }
float Ingredient::getQuantite() const { return m_quantite; }
UNITE Ingredient::getUnite() const   { return m_unite; }
