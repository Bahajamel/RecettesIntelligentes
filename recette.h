#ifndef RECETTE_H
#define RECETTE_H

#include <QString>
#include <QList>
#include <QSharedPointer>

#include "ingredient.h"
#include "unite.h"
#include "instruction.h"
#include "recetteingredient.h"

/**
 * Classe Recette : représente une recette contenant
 * - id, titre, description
 * - liste d'ingrédients (avec quantité + unité)
 * - liste d'instructions (arbre d'instructions : on conserve ici les racines)
 */
class Recette
{
public:
    Recette() = default;
    explicit Recette(int id, const QString &titre, const QString &description = QString());

    // --- structure pour stocker un ingrédient lié à la recette ---

    // ---- Getters / Setters pour id, titre, description ----
    int getId() const;
    void setId(int id);

    QString getTitre() const;
    void setTitre(const QString &titre);

    QString getDescription() const;
    void setDescription(const QString &description);

    // ---- opérations sur ingrédients ---
    void ajouterIngredient(const Ingredient &ingredient ,const float &quantite ,UNITE unite) ;
    // Récupérer la liste (const ref pour éviter copie)
    const QList<RecetteIngredient>& getIngredients() const;

    // ---- opérations sur instructions ----
    // Ajoute une instruction (racine). L'instruction peut être simple ou composée.
    void ajouterInstruction(const QSharedPointer<Instruction> &instr);

    // Récupérer la liste des instructions racines
    const QList<QSharedPointer<Instruction>>& getInstructions() const;

    // Nombre d'instructions racines
    int getNombreInstructions() const;

private:
    int m_id = -1;
    QString m_titre;
    QString m_description;

    QList<RecetteIngredient> m_ingredients;
    QList<QSharedPointer<Instruction>> m_instructions; // racines (parent_id == NULL)
};

#endif // RECETTE_H
