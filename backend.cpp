#include "backend.h"
#include "metiersHeader/unite.h"

Backend::Backend(QObject *parent)
    : QObject(parent),

    // 1️⃣ Database
    m_dbManager("app.db"),

    // 2️⃣ DAO
    m_recetteDAO(m_dbManager.database()),
    m_ingredientDAO(m_dbManager.database()),
    m_riDAO(m_dbManager.database()),
    m_instructionDAO(m_dbManager.database()),

    // 3️⃣ Services
    m_ingredientService(m_ingredientDAO, m_riDAO),
    m_instructionService(m_instructionDAO),
    m_recetteService(m_recetteDAO, m_riDAO, m_ingredientService, m_instructionService),

    // 4️⃣ Models
    m_recetteModel(m_recetteService)
{
    m_dbManager.open();
    chargerRecettes() ;
}

RecetteTableModel* Backend::recetteModel()
{
    return &m_recetteModel;
}

void Backend::chargerRecettes()
{
    QList<Recette> recettes = m_recetteService.listerRecettes();
    m_recetteModel.setRecettes(recettes);
}
int Backend::creerRecette(const QString &titre, const QString &description)
{
    int id = m_recetteService.creerRecette(titre, description);
    if (id < 0) {
        emit erreur("Impossible de créer la recette");
        return 0;
    }
    return id ;
    chargerRecettes(); // rafraîchir la vue
}

void Backend::ajouterIngredientARecette(int recetteId,
                                        const QString &nom,
                                        float qte,
                                        const QString &uniteStr)
{

    int ingredientId = m_ingredientService.ajouterIngredient(nom);


    UNITE unite = stringToUnite(uniteStr);


    m_recetteService.ajouterIngredient(
        recetteId,
        m_ingredientService.getIngredient(ingredientId),
        qte,
        unite
        );
}

// ---------------- INSTRUCTION SIMPLE ----------------
void Backend::ajouterInstructionSimple(int recetteId,
                                       int parentId,
                                       const QString &texte)
{
    m_instructionService.ajouterSimple(
        recetteId,
        parentId,
        1,          // ordre par défaut
        texte
        );
}

// ---------------- INSTRUCTION COMPOSÉE ----------------
void Backend::ajouterInstructionComposee(int recetteId,
                                         int parentId,
                                         const QString &titre)
{
    m_instructionService.ajouterComposee(
        recetteId,
        parentId,
        1,          // ordre par défaut
        titre
        );
}



