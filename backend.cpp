#include "backend.h"

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
<<<<<<< HEAD
int Backend::creerRecette(const QString &titre, const QString &description)
=======
void Backend::creerRecette(const QString &titre, const QString &description)
>>>>>>> Baha
{
    int id = m_recetteService.creerRecette(titre, description);
    if (id < 0) {
        emit erreur("Impossible de créer la recette");
<<<<<<< HEAD
        return 0;
    }
    return id ;
    chargerRecettes(); // rafraîchir la vue
}

void Backend::ajouterIngredientARecette(const int &id , const QString &Ingredient , const float &qte , const QString &unite) {
    Ingredient ing = static_cast<Ingredient>(Ingredient) ;
    UNITE unit = static_cast<UNITE> unite ;


}

=======
        return;
    }
    chargerRecettes(); // rafraîchir la vue
}

>>>>>>> Baha
