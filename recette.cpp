#include "recette.h"

// ---------- Constructeur ----------
Recette::Recette(int id, const QString &titre, const QString &description)
    : m_id(id), m_titre(titre), m_description(description)
{}

// ---------- Getters / Setters ----------
int Recette::getId() const
{
    return m_id;
}

void Recette::setId(int id)
{
    m_id = id;
}

QString Recette::getTitre() const
{
    return m_titre;
}

void Recette::setTitre(const QString &titre)
{
    m_titre = titre;
}

QString Recette::getDescription() const
{
    return m_description;
}

void Recette::setDescription(const QString &description)
{
    m_description = description;
}

// ---------- Ingrédients ----------
void Recette::ajouterIngredient(const RecetteIngredient &ri)
{
    m_ingredients.append(ri);
}

void Recette::ajouterIngredient(const Ingredient &ingredient, double quantite, UNITE unite)
{
    RecetteIngredient ri;
    ri.ingredient = ingredient;
    ri.quantite = quantite;
    ri.unite = unite;
    m_ingredients.append(ri);
}

const QList<Recette::RecetteIngredient>& Recette::getIngredients() const
{
    return m_ingredients;
}

// ---------- Instructions ----------
void Recette::ajouterInstruction(const QSharedPointer<Instruction> &instr)
{
    if (!instr.isNull()) {
        m_instructions.append(instr);
    }
}

const QList<QSharedPointer<Instruction>>& Recette::getInstructions() const
{
    return m_instructions;
}

int Recette::getNombreInstructions() const
{
    return m_instructions.size();
}
