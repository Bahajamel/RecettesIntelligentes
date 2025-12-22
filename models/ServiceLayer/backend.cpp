#include "modelsHeader/ServiceLayerHeader/backend.h"
#include "modelsHeader/unite.h"
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

    chargerRecettes();

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
int Backend::creerRecette(const QString &titre, const QString &description )
{
    int id = m_recetteService.creerRecette(titre, description ) ;
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


int Backend::ajouterInstructionSimple(int recetteId,
                                       int parentId,
                                       const QString &texte)
{
    int ordre = 0;
    int id = m_instructionService.ajouterSimple(
        recetteId,
        parentId,
        ordre++,          // ordre par défaut
        texte
        );
    return id;
}

int Backend::ajouterInstructionComposee(int recetteId,
                                        int parentId,
                                        const QString &titre)
{
    int ordre = 0 ;
    int id = m_instructionService.ajouterComposee(
    recetteId,
    parentId,
    ordre ++,
    titre
    );

    return id ;
}

Recette Backend::obtenirRecetteComplete(int id)
{
    return m_recetteService.obtenirRecetteComplete(id);
}

bool Backend::mettreAJourRecette(int id, const QString &titre, const QString &description)
{
    bool success = m_recetteService.mettreAJourRecette(id, titre, description);
    if (success) {
        chargerRecettes(); // rafraîchir la vue
    }
    return success;
}

bool Backend::supprimerRecette(int id)
{
    bool success = m_recetteDAO.supprimerRecette(id);
    if (success) {
        chargerRecettes(); // rafraîchir la vue
    }
    return success;
}


void Backend::resetDatabase()
{
    m_dbManager.resetDatabase();
    chargerRecettes();
}
void Backend::insererRecettesTest()
{
    // ---- Recette 1 : Pain ----
    int painId = creerRecette("Pain Maison", "Pain traditionnel fait à la maison");
    ajouterIngredientARecette(painId, "Farine", 500, "g");
    ajouterIngredientARecette(painId, "Eau", 300, "ml");
    ajouterIngredientARecette(painId, "Sel", 10, "g");
    ajouterIngredientARecette(painId, "Levure", 10, "g");
    int prep = ajouterInstructionComposee(painId, -1, "Préparation de la pâte");
    ajouterInstructionSimple(painId, prep, "Mélanger la farine et le sel");
    ajouterInstructionSimple(painId, prep, "Ajouter l'eau et la levure");
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

    // ---- Recette 3 : Gâteau au Chocolat ----
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

    // ---- Recette 4 : Omelette ----
    int omeletteId = creerRecette("Omelette", "Omelette simple et rapide");
    ajouterIngredientARecette(omeletteId, "Œufs", 3, "pièce");
    ajouterIngredientARecette(omeletteId, "Lait", 50, "ml");
    ajouterIngredientARecette(omeletteId, "Sel", 2, "g");
    ajouterIngredientARecette(omeletteId, "Poivre", 1, "g");
    ajouterIngredientARecette(omeletteId, "Beurre", 10, "g");
    int prepOmelette = ajouterInstructionComposee(omeletteId, -1, "Préparation de l'omelette");
    ajouterInstructionSimple(omeletteId, prepOmelette, "Battre les œufs avec le lait, le sel et le poivre");
    ajouterInstructionSimple(omeletteId, prepOmelette, "Faire chauffer le beurre dans une poêle");
    ajouterInstructionSimple(omeletteId, -1, "Verser le mélange d'œufs dans la poêle et cuire jusqu'à consistance désirée");

    // ---- Recette 5 : Salade César ----
    int cesarId = creerRecette("Salade César", "Salade verte avec poulet et croûtons");
    ajouterIngredientARecette(cesarId, "Laitue", 200, "g");
    ajouterIngredientARecette(cesarId, "Poulet grillé", 150, "g");
    ajouterIngredientARecette(cesarId, "Parmesan", 50, "g");
    ajouterIngredientARecette(cesarId, "Croûtons", 50, "g");
    ajouterIngredientARecette(cesarId, "Sauce César", 50, "ml");
    int prepCesar = ajouterInstructionComposee(cesarId, -1, "Préparation de la salade");
    ajouterInstructionSimple(cesarId, prepCesar, "Couper la laitue et disposer dans un saladier");
    ajouterInstructionSimple(cesarId, prepCesar, "Ajouter le poulet, le parmesan et les croûtons");
    ajouterInstructionSimple(cesarId, -1, "Verser la sauce César et mélanger délicatement");

    // ---- Recette 6 : Quiche Lorraine ----
    int quicheId = creerRecette("Quiche Lorraine", "Tarte salée aux lardons et crème");
    ajouterIngredientARecette(quicheId, "Pâte brisée", 1, "pièce");
    ajouterIngredientARecette(quicheId, "Lardons", 200, "g");
    ajouterIngredientARecette(quicheId, "Œufs", 3, "pièce");
    ajouterIngredientARecette(quicheId, "Crème fraîche", 200, "ml");
    ajouterIngredientARecette(quicheId, "Gruyère râpé", 100, "g");
    ajouterInstructionSimple(quicheId, -1, "Étaler la pâte dans un moule");
    ajouterInstructionSimple(quicheId, -1, "Faire revenir les lardons");
    ajouterInstructionSimple(quicheId, -1, "Battre les œufs avec la crème");
    ajouterInstructionSimple(quicheId, -1, "Verser sur la pâte, ajouter les lardons et le fromage");
    ajouterInstructionSimple(quicheId, -1, "Cuire au four à 180°C pendant 35 minutes");

    // ---- Recette 7 : Ratatouille ----
    int ratatouilleId = creerRecette("Ratatouille", "Plat provençal aux légumes du soleil");
    ajouterIngredientARecette(ratatouilleId, "Aubergines", 2, "pièce");
    ajouterIngredientARecette(ratatouilleId, "Courgettes", 2, "pièce");
    ajouterIngredientARecette(ratatouilleId, "Poivrons", 2, "pièce");
    ajouterIngredientARecette(ratatouilleId, "Tomates", 4, "pièce");
    ajouterIngredientARecette(ratatouilleId, "Oignon", 1, "pièce");
    ajouterIngredientARecette(ratatouilleId, "Ail", 3, "gousse");
    ajouterIngredientARecette(ratatouilleId, "Huile d'olive", 50, "ml");
    ajouterInstructionSimple(ratatouilleId, -1, "Couper tous les légumes en dés");
    ajouterInstructionSimple(ratatouilleId, -1, "Faire revenir l'oignon et l'ail");
    ajouterInstructionSimple(ratatouilleId, -1, "Ajouter les légumes et mijoter 45 minutes");

    // ---- Recette 8 : Crêpes ----
    int crepesId = creerRecette("Crêpes", "Crêpes sucrées traditionnelles");
    ajouterIngredientARecette(crepesId, "Farine", 250, "g");
    ajouterIngredientARecette(crepesId, "Œufs", 3, "pièce");
    ajouterIngredientARecette(crepesId, "Lait", 500, "ml");
    ajouterIngredientARecette(crepesId, "Sucre", 50, "g");
    ajouterIngredientARecette(crepesId, "Beurre fondu", 50, "g");
    int prepCrepes = ajouterInstructionComposee(crepesId, -1, "Préparation de la pâte");
    ajouterInstructionSimple(crepesId, prepCrepes, "Mélanger la farine et le sucre");
    ajouterInstructionSimple(crepesId, prepCrepes, "Ajouter les œufs et le lait progressivement");
    ajouterInstructionSimple(crepesId, -1, "Laisser reposer 30 minutes");
    ajouterInstructionSimple(crepesId, -1, "Cuire à la poêle 2 minutes de chaque côté");

    // ---- Recette 9 : Lasagnes ----
    int lasagnesId = creerRecette("Lasagnes", "Lasagnes à la bolognaise maison");
    ajouterIngredientARecette(lasagnesId, "Plaques de lasagnes", 12, "pièce");
    ajouterIngredientARecette(lasagnesId, "Viande hachée", 500, "g");
    ajouterIngredientARecette(lasagnesId, "Sauce tomate", 400, "g");
    ajouterIngredientARecette(lasagnesId, "Béchamel", 500, "ml");
    ajouterIngredientARecette(lasagnesId, "Parmesan", 100, "g");
    ajouterIngredientARecette(lasagnesId, "Mozzarella", 200, "g");
    int prepLasagnes = ajouterInstructionComposee(lasagnesId, -1, "Préparation de la bolognaise");
    ajouterInstructionSimple(lasagnesId, prepLasagnes, "Faire revenir la viande hachée");
    ajouterInstructionSimple(lasagnesId, prepLasagnes, "Ajouter la sauce tomate et mijoter 20 minutes");
    ajouterInstructionSimple(lasagnesId, -1, "Alterner couches de pâtes, bolognaise et béchamel");
    ajouterInstructionSimple(lasagnesId, -1, "Terminer par les fromages");
    ajouterInstructionSimple(lasagnesId, -1, "Cuire au four à 180°C pendant 40 minutes");

    // ---- Recette 10 : Tiramisu ----
    int tiramisuId = creerRecette("Tiramisu", "Dessert italien au café et mascarpone");
    ajouterIngredientARecette(tiramisuId, "Mascarpone", 500, "g");
    ajouterIngredientARecette(tiramisuId, "Œufs", 4, "pièce");
    ajouterIngredientARecette(tiramisuId, "Sucre", 100, "g");
    ajouterIngredientARecette(tiramisuId, "Biscuits cuillère", 300, "g");
    ajouterIngredientARecette(tiramisuId, "Café fort", 300, "ml");
    ajouterIngredientARecette(tiramisuId, "Cacao en poudre", 20, "g");
    int prepTiramisu = ajouterInstructionComposee(tiramisuId, -1, "Préparation de la crème");
    ajouterInstructionSimple(tiramisuId, prepTiramisu, "Séparer les blancs des jaunes d'œufs");
    ajouterInstructionSimple(tiramisuId, prepTiramisu, "Mélanger jaunes, sucre et mascarpone");
    ajouterInstructionSimple(tiramisuId, prepTiramisu, "Monter les blancs en neige et incorporer");
    ajouterInstructionSimple(tiramisuId, -1, "Tremper les biscuits dans le café");
    ajouterInstructionSimple(tiramisuId, -1, "Alterner couches de biscuits et crème");
    ajouterInstructionSimple(tiramisuId, -1, "Saupoudrer de cacao et réfrigérer 4 heures");

    // ---- Recette 11 : Soupe à l'oignon ----
    int soupeId = creerRecette("Soupe à l'Oignon", "Soupe gratinée traditionnelle");
    ajouterIngredientARecette(soupeId, "Oignons", 1000, "g");
    ajouterIngredientARecette(soupeId, "Bouillon de bœuf", 1500, "ml");
    ajouterIngredientARecette(soupeId, "Beurre", 50, "g");
    ajouterIngredientARecette(soupeId, "Pain", 200, "g");
    ajouterIngredientARecette(soupeId, "Gruyère râpé", 200, "g");
    ajouterInstructionSimple(soupeId, -1, "Émincer finement les oignons");
    ajouterInstructionSimple(soupeId, -1, "Faire caraméliser les oignons dans le beurre");
    ajouterInstructionSimple(soupeId, -1, "Ajouter le bouillon et mijoter 30 minutes");
    ajouterInstructionSimple(soupeId, -1, "Verser dans des bols, ajouter pain et fromage");
    ajouterInstructionSimple(soupeId, -1, "Gratiner au four 10 minutes");

    // ---- Recette 12 : Poulet Rôti ----
    int pouletId = creerRecette("Poulet Rôti", "Poulet fermier rôti au four");
    ajouterIngredientARecette(pouletId, "Poulet entier", 1500, "g");
    ajouterIngredientARecette(pouletId, "Beurre", 100, "g");
    ajouterIngredientARecette(pouletId, "Thym", 5, "g");
    ajouterIngredientARecette(pouletId, "Citron", 1, "pièce");
    ajouterIngredientARecette(pouletId, "Ail", 5, "gousse");
    ajouterInstructionSimple(pouletId, -1, "Préchauffer le four à 200°C");
    ajouterInstructionSimple(pouletId, -1, "Farcir le poulet avec citron, ail et thym");
    ajouterInstructionSimple(pouletId, -1, "Badigeonner de beurre");
    ajouterInstructionSimple(pouletId, -1, "Cuire 1h30 en arrosant régulièrement");

    // ---- Recette 13 : Gratin Dauphinois ----
    int gratinId = creerRecette("Gratin Dauphinois", "Gratin de pommes de terre crémeux");
    ajouterIngredientARecette(gratinId, "Pommes de terre", 1000, "g");
    ajouterIngredientARecette(gratinId, "Crème fraîche", 400, "ml");
    ajouterIngredientARecette(gratinId, "Lait", 200, "ml");
    ajouterIngredientARecette(gratinId, "Ail", 2, "gousse");
    ajouterIngredientARecette(gratinId, "Noix de muscade", 2, "g");
    ajouterInstructionSimple(gratinId, -1, "Éplucher et trancher finement les pommes de terre");
    ajouterInstructionSimple(gratinId, -1, "Frotter le plat avec l'ail");
    ajouterInstructionSimple(gratinId, -1, "Disposer les pommes de terre en couches");
    ajouterInstructionSimple(gratinId, -1, "Verser le mélange crème-lait-muscade");
    ajouterInstructionSimple(gratinId, -1, "Cuire au four à 180°C pendant 1h15");

    // ---- Recette 14 : Tarte Tatin ----
    int tatinId = creerRecette("Tarte Tatin", "Tarte aux pommes caramélisées renversée");
    ajouterIngredientARecette(tatinId, "Pommes", 1200, "g");
    ajouterIngredientARecette(tatinId, "Sucre", 150, "g");
    ajouterIngredientARecette(tatinId, "Beurre", 100, "g");
    ajouterIngredientARecette(tatinId, "Pâte feuilletée", 1, "pièce");
    ajouterInstructionSimple(tatinId, -1, "Faire un caramel avec le sucre et le beurre");
    ajouterInstructionSimple(tatinId, -1, "Disposer les pommes coupées en quartiers");
    ajouterInstructionSimple(tatinId, -1, "Recouvrir de pâte feuilletée");
    ajouterInstructionSimple(tatinId, -1, "Cuire au four à 180°C pendant 30 minutes");
    ajouterInstructionSimple(tatinId, -1, "Retourner encore chaude sur un plat");

    // ---- Recette 15 : Mousse au Chocolat ----
    int mousseId = creerRecette("Mousse au Chocolat", "Mousse onctueuse et légère");
    ajouterIngredientARecette(mousseId, "Chocolat noir", 200, "g");
    ajouterIngredientARecette(mousseId, "Œufs", 4, "pièce");
    ajouterIngredientARecette(mousseId, "Sucre", 50, "g");
    int prepMousse = ajouterInstructionComposee(mousseId, -1, "Préparation de la mousse");
    ajouterInstructionSimple(mousseId, prepMousse, "Faire fondre le chocolat au bain-marie");
    ajouterInstructionSimple(mousseId, prepMousse, "Séparer les blancs des jaunes");
    ajouterInstructionSimple(mousseId, prepMousse, "Mélanger les jaunes au chocolat fondu");
    ajouterInstructionSimple(mousseId, prepMousse, "Monter les blancs en neige avec le sucre");
    ajouterInstructionSimple(mousseId, -1, "Incorporer délicatement les blancs au chocolat");
    ajouterInstructionSimple(mousseId, -1, "Réfrigérer au moins 3 heures");

    // Rafraîchir le modèle pour afficher les nouvelles recettes
    chargerRecettes();
    emit recettesModifiees();

    qDebug() << "✓ 15 recettes de test insérées avec succès";
}
