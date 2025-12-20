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
    if (!m_dbManager.open()) {
        qCritical() << "ERREUR: Impossible d'ouvrir la base de données!";
        emit erreur("Impossible d'ouvrir la base de données. Vérifiez que le driver SQLite est disponible.");
        return;
    }
    
    // Charger les recettes existantes depuis la base de données
    chargerRecettes();
    
    // Si la base est vide, insérer les recettes de test (seulement la première fois)
    if (m_recetteModel.rowCount() == 0) {
        qDebug() << "Base de données vide, insertion des recettes de test...";
        insererRecettesTest();
    } else {
        qDebug() << "✓" << m_recetteModel.rowCount() << "recettes chargées depuis la base de données";
    }
}

RecetteTableModel* Backend::recetteModel()
{
    return &m_recetteModel;
}

QList<RecetteIngredient> Backend::ingredientsDeRecette(int recetteId)
{
    return m_riDAO.findByRecette(recetteId);
}

void Backend::chargerInstructionsDansModele(InstructionTreeModel &model, int recetteId)
{
    model.chargerRecette(recetteId);
}

InstructionService& Backend::instructionService()
{
    return m_instructionService;
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
    emit recettesModifiees();
    chargerRecettes(); // rafraîchir la vue
    return id ;
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

int Backend::ajouterInstructionComposee(int recetteId,
                                        int parentId,
                                        const QString &titre)
{
    return m_instructionService.ajouterComposee(
        recetteId,
        parentId,
        1,          // ordre par défaut
        titre
        );
}
void Backend::resetDatabase()
{
    m_dbManager.resetDatabase();
    chargerRecettes();
}
void Backend::insererRecettesTest()
{
    // Supprimer toutes les recettes existantes
    m_dbManager.resetDatabase();
    
    // Vider le modèle pour s'assurer qu'il est synchronisé
    chargerRecettes();
    
    // ---- Recette 1 : Pain ----
    int painId = creerRecette("Pain Maison", "Pain traditionnel fait à la maison");

    ajouterIngredientARecette(painId, "Farine", 500, "g");
    ajouterIngredientARecette(painId, "Eau", 300, "ml");
    ajouterIngredientARecette(painId, "Sel", 10, "g");
    ajouterIngredientARecette(painId, "Levure", 10, "g");

    int prep = ajouterInstructionComposee(painId, -1, "Préparation de la pâte");
    ajouterInstructionSimple(painId, prep, "Mélanger la farine et le sel");
    ajouterInstructionSimple(painId, prep, "Ajouter l’eau et la levure");
    ajouterInstructionSimple(painId, -1, "Cuire au four à 220°C pendant 30 minutes");

    // ---- Recette 2 : Pizza ----
    int pizzaId = creerRecette("Pizza Maison", "Pizza italienne classique");

    ajouterIngredientARecette(pizzaId, "Farine", 500, "g");
    ajouterIngredientARecette(pizzaId, "Eau", 300, "ml");
    ajouterIngredientARecette(pizzaId, "Levure", 10, "g");
    ajouterIngredientARecette(pizzaId, "Sauce tomate", 200, "g");
    ajouterIngredientARecette(pizzaId, "Mozzarella", 200, "g");

    int pate = ajouterInstructionComposee(pizzaId, -1, "Préparer la pâte");
    ajouterInstructionSimple(pizzaId, pate, "Mélanger farine, levure et eau");
    ajouterInstructionSimple(pizzaId, pate, "Pétrir la pâte");
    ajouterInstructionSimple(pizzaId, pate, "Laisser reposer 1 heure");

    ajouterInstructionSimple(pizzaId, -1, "Cuire au four à 250°C pendant 12 minutes");

    // ---- Recette 3 : Gâteau ----
    int gateauId = creerRecette("Gâteau au Chocolat", "Gâteau moelleux au chocolat");

    ajouterIngredientARecette(gateauId, "Chocolat noir", 200, "g");
    ajouterIngredientARecette(gateauId, "Beurre", 150, "g");
    ajouterIngredientARecette(gateauId, "Sucre", 150, "g");
    ajouterIngredientARecette(gateauId, "Farine", 100, "g");
    ajouterIngredientARecette(gateauId, "Œufs", 4, "pièce");

    ajouterInstructionSimple(gateauId, -1, "Faire fondre le chocolat et le beurre");
    ajouterInstructionSimple(gateauId, -1, "Ajouter le sucre");
    ajouterInstructionSimple(gateauId, -1, "Ajouter les œufs");
    ajouterInstructionSimple(gateauId, -1, "Ajouter la farine");
    ajouterInstructionSimple(gateauId, -1, "Cuire au four à 180°C pendant 25 minutes");

    // Rafraîchir le modèle pour afficher immédiatement les recettes de test
    chargerRecettes();
    emit recettesModifiees();
}




