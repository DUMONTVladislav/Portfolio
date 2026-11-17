#include <iostream>
#include <vector>
#include <istream>
#include <fstream>

/**
 * @file main.cpp
 * @brief Logique principale du candy-crush
 *
 * Ce fichier contient toutes les fonctions permettant
 * le fonctionnement du jeu
 *
 * @author Vladislav Dumont, Anna Boin, Lucas Franceschi--Pinson
 * @date 2026
 */


using namespace std;

/**
 * @brief Efface l’écran.
 *
 * Utilise des séquences d’échappement ANSI pour effacer l'écran
 */
void clearScreen () {
    cout << "\033[H\033[2J";
}

const unsigned KReset   (0);
const unsigned KNbCandies = 9;

/**
 * @brief Change la couleur d’affichage du terminal.
 *
 * @param coul Code de couleur ANSI à appliquer.
 */
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}

typedef vector <unsigned> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

struct maPosition {
    unsigned abs;
    unsigned ord;
}; // une position dans la grille

/**
 * @brief Initialise la grille de jeu avec des valeurs aléatoires.
 *
 * Remplit la matrice avec des chiffres.
 *
 * @param grid Grille à initialiser.
 * @param matSize Taille de la grille carrée.
 */
void initGrid (mat & grid, const size_t & matSize){
    for (size_t i = 0; i < matSize; ++i) {
        line a(matSize);
        for (unsigned &number : a){
            number = rand() % KNbCandies + 1; // chaque nombre est généré aléatoirement entre 1 et KNbCandies
        }
        grid.push_back(a);
    }
}

/**
 * @brief Affiche la grille de jeu dans le terminal.
 *
 * Affiche chaque élément de la grille avec une couleur dépendant de sa valeur.
 *
 * @param grid Grille à afficher.
 */
void displayGrid (const mat & grid){
    clearScreen();
    couleur(KReset);
    for (size_t i = 0 ; i < grid.size() ; ++i) {
        for (size_t j = 0; j < grid.size(); ++j) {
            unsigned courant = grid[i][j];
            cout << '|';
            if (courant == 0) couleur(37); // 0 est affiché en blanc (pour le rendre invisible)
            else {
                couleur(courant % 8 == 6 ? 31 : 31 + courant % 8); // les autres chiffres prennent une couleur (sauf noir ou blanc)
            }
            cout << courant;
            couleur(KReset);
        }
        cout << '|' << endl;
    }
}

/**
 * @brief Déplace un chiffre dans la grille selon une direction donnée.
 *
 * Échange le chiffre sélectionné avec son voisin si le déplacement dans la direction donnée
 * est valide.
 *
 * @param grid Grille de jeu.
 * @param pos Position actuelle.
 * @param direction Direction du déplacement (z, q, s, d).
 * @return true si le déplacement a été effectué, false sinon.
 */
bool makeAMove(mat &grid, const maPosition &pos, const char &direction){
    bool dep;
    unsigned chiffreChoisi;
    switch (direction)
    {
    case 's':
        if (pos.ord >= grid.size() - 1) // Vérifie si le déplacement est valide
        {
            cout << "Déplacement non-valide" << endl;
            dep = false;
        }
        else // Effectue le déplacement
        {
            chiffreChoisi = grid[pos.ord][pos.abs];
            grid[pos.ord][pos.abs] = grid[pos.ord + 1][pos.abs];
            grid[pos.ord + 1][pos.abs] = chiffreChoisi;
            dep = true;
        }
        break;
    case 'z':
        if (pos.ord == 0)
        {
            cout << "Déplacement non-valide" << endl;
            dep = false;
        }
        else
        {
            chiffreChoisi = grid[pos.ord][pos.abs];
            grid[pos.ord][pos.abs] = grid[pos.ord - 1][pos.abs];
            grid[pos.ord - 1][pos.abs] = chiffreChoisi;
            dep = true;
        }
        break;
    case 'q':
        if (pos.abs == 0)
        {
            cout << "Déplacement non-valide" << endl;
            dep = false;
        }
        else
        {
            chiffreChoisi = grid[pos.ord][pos.abs];
            grid[pos.ord][pos.abs] = grid[pos.ord][pos.abs - 1];
            grid[pos.ord][pos.abs - 1] = chiffreChoisi;
            dep = true;
        }
        break;
    case 'd':
        if (pos.abs >= grid.size() - 1)
        {
            cout << "Déplacement non-valide" << endl;
            dep = false;
        }
        else
        {
            chiffreChoisi = grid[pos.ord][pos.abs];
            grid[pos.ord][pos.abs] = grid[pos.ord][pos.abs + 1];
            grid[pos.ord][pos.abs + 1] = chiffreChoisi;
            dep = true;
        }
        break;
    default:
        cout << "Déplacement non-valide" << endl;
        dep = false;
        break;
    }
    return dep;
}


/**
 * @brief Vérifie s'il existe une chaine d'au moins 3 chiffres dans une colonne
 *
 * Analyse la colonne correspondant à la position donnée et détermine
 * s'il existe une chaine d'au moins 3 chiffres identiques
 *
 * @param grid Grille de jeu.
 * @param pos Position analysée (la colonne est utilisée, la ligne est mise à jour).
 * @param howMany Nombre de chiffres consécutifs détectés.
 * @return true si une chaine d’au moins trois chiffres est trouvée, false sinon.
 */
bool atLeastThreeInAColumn(const mat &grid, maPosition &pos, unsigned &howMany)
{
    unsigned col = pos.abs;
    pos.ord = 0;
    unsigned courant = grid[0][col];
    howMany = 1;
    for (size_t i = 1; i < grid.size(); ++i)
    {
        if (grid[i][col] == courant && courant != 0) ++howMany; // si le chiffre actuel correspond à celui en mémoire on incrémente le compteur de 1
        else
        {
            if (howMany >= 3 && courant != 0) return true;
            courant = grid[i][col]; // le chiffre actuel rentre en mémoire
            howMany = (courant == 0 ? 0 : 1); // si il vaut 0, le compteur revient à 0 sinon il revient à 1
            pos.ord = i;
        }
    }
    return (howMany >= 3 && courant != 0);
}

/**
 * @brief Vérifie s'il existe une chaine d'au moins 3 chiffres dans une ligne
 *
 * Analyse la ligne correspondant à la position donnée et détermine
 * s'il existe une chaine d'au moins 3 chiffres identiques
 *
 * @param grid Grille de jeu.
 * @param pos Position analysée (la colonne est utilisée, la colonne est mise à jour).
 * @param howMany Nombre de chiffres consécutifs détectés.
 * @return true si une chaine d’au moins trois chiffres est trouvée, false sinon.
 */
bool atLeastThreeInARow(const mat &grid, maPosition &pos, unsigned &howMany)
{
    unsigned row = pos.ord;
    pos.abs = 0;
    unsigned courant = grid[row][0];
    howMany = 1;
    for (size_t i = 1; i < grid.size(); ++i)
    {
        if (grid[row][i] == courant && courant != 0) ++howMany; // si le chiffre actuel correspond à celui en mémoire on incrémente le compteur de 1
        else
        {
            if (howMany >= 3 && courant != 0) return true;
            courant = grid[row][i]; // le chiffre actuel rentre en mémoire
            howMany = (courant == 0 ? 0 : 1); // si il vaut 0, le compteur revient à 0 sinon il revient à 1
            pos.abs = i;
        }
    }

    return (howMany >= 3 && courant != 0);
}

/**
 * @brief Supprime une chaine d’éléments dans une colonne
 *
 * Remplace la chaine par des 0 et applique de la gravité
 *
 * @param grid Grille de jeu.
 * @param pos Position de départ de la suppression.
 * @param howMany Nombre de chiffres à supprimer.
 * @param matSize Taille de la grille.
 */
void removalInColumn(mat &grid, maPosition &pos, unsigned &howMany, const size_t matSize) {
    for (size_t i = pos.ord; i < pos.ord + howMany; ++i) { // En partant du début de la chaine jusqu'à la fin de celle-ci
        grid[i][pos.abs] = 0; // On remplace les valeurs par 0
    }
    for (size_t i = pos.ord + howMany; i < matSize; ++i) { // En partant du début de la chaine jusqu'à la fin de celle-ci, on fait descendre les 0
        grid[i - howMany][pos.abs] = grid[i][pos.abs];
        grid[i][pos.abs] = 0;
    }
}

/**
 * @brief Supprime une chaine d’éléments dans une ligne
 *
 * Remplace la chaine par des 0 et applique de la gravité
 *
 * @param grid Grille de jeu.
 * @param pos Position de départ de la suppression.
 * @param howMany Nombre de chiffres à supprimer.
 * @param matSize Taille de la grille.
 */
void removalInRow(mat &grid, maPosition &pos, unsigned &howMany, const size_t matSize) {
    for (size_t i = pos.abs; i < pos.abs + howMany; ++i) { // En partant du début de la chaine jusqu'à la fin de celle-ci
        grid[pos.ord][i] = 0; // On remplace les valeurs par 0
    }
    for (size_t j = pos.abs; j < pos.abs + howMany; ++j) { // Pour chaque colonne ou la chaine est présente
        for (size_t i = pos.ord + 1; i < matSize; ++i) { // On fait descendre le 0
            grid[i - 1][j] = grid[i][j];
            grid[i][j] = 0;
        }
    }
}

/**
 * @brief Affiche le contenu d’un fichier.
 *
 * Par défaut, lit depuis l’entrée standard (cin).
 * Fonction reprise d'un précédent TD.
 *
 * @param stream Flux d’entrée à lire (par défaut : cin).
 */
void flux_cin(istream &stream = cin){
    for (string chaine; getline(stream, chaine);)
        cout << chaine << endl;
}

/**
 * @brief Affiche les règles du jeu.
 *
 * Lit le fichier "../../Rules.txt" et l’affiche à l’écran.
 * Attend que l’utilisateur saisisse une valeur pour quitter l’affichage.
 */
void displayRules() {
    bool regles = true;
    while (regles) {
        clearScreen();
        ifstream rules("../../Rules.txt");
        flux_cin(rules);
        cin >> regles;
    }
}

/**
 * @brief Supprime toutes les chaines valides dans la grille et calcule les points et combos.
 *
 * Parcourt la grille pour détecter toutes les chaines d’au moins trois chiffres
 * consécutifs, les supprime, et met à jour le score et le compteur de combos.
 *
 * @param grid Grille de jeu à mettre à jour.
 * @param matSize Taille de la grille carrée.
 * @param points Points accumulés.
 * @param combo Nombre total de combos réalisés.
 */
void removeAll(mat &grid, const size_t matSize, unsigned &points, unsigned &combo) {
    maPosition posR;
    unsigned howMany;
    bool comboP = false;
    points = 0;
    while (true) { // Tant qu'il y a des modifications
        bool modif = false;
        for (size_t i = 0; i < matSize; ++i) { // On analyse toutes les colonnes
            posR.abs = i;
            posR.ord = 0;
            while (atLeastThreeInAColumn(grid, posR, howMany)) { // Tant que la colonne a des chaines
                ++combo; // On incrémente le compteur combo
                points += howMany - 2; // On incrémente les points
                removalInColumn(grid, posR, howMany, matSize); // On supprime la chaine
                modif = true; // On indique qu'il y a une modification
                comboP = true; // On indique que le combo est actif
            }
        }
        for (size_t i = 0; i < matSize; ++i) { // On analyse toutes les lignes
            posR.abs = 0;
            posR.ord = i;
            while (atLeastThreeInARow(grid, posR, howMany)) { // Tant que la ligne a des chaines
                ++combo; // On incrémente le compteur combo
                points += howMany - 2; // On incrémente les points
                removalInRow(grid, posR, howMany, matSize); // On supprime la chaine
                modif = true; // On indique qu'il y a une modification
                comboP = true; // On indique que le combo est actif
            }
        }
        if (modif == false) break;
    }
    if (comboP == false) combo = 0; // Si le combo n'est plus actif on le met à 0
}

/**
 * @brief Applique la gravité à tous les éléments.
 *
 * Fait descendre tous les 0 de la grille.
 *
 * @param grid Grille de jeu à mettre à jour.
 * @param matSize Taille de la grille carrée.
 */
void verifVide(mat &grid, const size_t matSize) {
    for (size_t j = 0; j < matSize; ++j) { // Pour chaque colonne
        unsigned libre = 0; // Indice d'une case "vide"
        for (size_t i = 0; i < matSize; ++i) { // Pour chaque élement de la colonne
            if (grid[i][j] != 0){ // Si il est différent de 0
                grid[libre][j] = grid[i][j]; // Il prend la place de la case libre
                if (libre != i) grid[i][j] = 0; // Et si l'indice de la case actuelle ne correspond pas à celui de la case libre, la case actuelle prend pour valeur 0
                ++libre; // On incrémente l'indice de la case libre
            }
        }
    }
}

/**
 * @brief Vérifie si un nombre est présent dans un vecteur.
 *
 * @param numbers Vecteur d’entiers à parcourir.
 * @param num Nombre à rechercher.
 * @return true si le nombre est présent, false sinon.
 */
bool inVect(vector<unsigned> &numbers , const unsigned num){
    for (unsigned nb : numbers ) {
        if (nb == num) return true;
    }
    return false;
}

/**
 * @brief Remplit la grille aléatoirement si aucune chaine n’existe.
 *
 * Analyse la grille pour détecter si au moins une chaine existe.
 * Si aucune chaine n’est présente, les cases vides sont remplies avec des valeurs aléatoires.
 *
 * @param grid Grille de jeu à mettre à jour.
 * @param matSize Taille de la grille carrée.
 * @return true si aucune chaine n’est trouvée (mode frenzy activé), false sinon.
 */
bool frenzy(mat &grid, const size_t matSize){
    bool vide = true;
    unsigned compteur = 0;
    vector<unsigned> numbers;
    for (size_t i = 0; i < matSize; ++i) { // On parcourt la grille
        for (size_t j = 0; j < matSize; ++j) {
            if (!inVect(numbers, grid[i][j]) && grid[i][j] != 0)
                numbers.push_back(grid[i][j]); // On remplit le vecteur avec toutes les chiffres présents sauf 0
        }
    }
    for (unsigned nb : numbers) { // Pour chaque chiffre dans le vecteur
        compteur = 0;
        for (size_t i = 0; i < matSize; ++i) { // On parcourt la grille
            for (size_t j = 0; j < matSize; ++j) {
                if(grid[i][j] == nb) ++compteur; // Et on incrémente le compteur si le chiffre est présent
                if(compteur >= 3) vide = false; // Si le compteur dépasse 3 on peut faire une chaine (pas de mode frenzy)
            }
        }
    }
    if (vide){ // Si mode frenzy
        for (size_t i = 0; i < matSize; ++i) { // On parcourt la grille
            for (size_t j = 0; j < matSize; ++j) {
                if (grid[i][j] == 0)
                    grid[i][j] = rand() % KNbCandies + 1; // On remplace les 0 par des chiffres aléatoires entre 1 et KNbCandies
            }
        }
    }
    return vide;
}

/**
 * @brief Gère le tour d’un joueur dans le jeu.
 *
 * Affiche la grille, demande la position et la direction du déplacement,
 * effectue le mouvement, gère le "frenzy mode", met à jour la grille,
 * supprime les chaines et met à jour le score et le combo.
 *
 * @param grid Grille de jeu à mettre à jour.
 * @param nbTour Nombre de tours restants (peut être modifié en frenzy mode).
 * @param matSize Taille de la grille carrée.
 * @param score Score, mis à jour avec ce tour.
 * @param combo Nombre de combos accumulés, mis à jour avec ce tour.
 */
void tour(mat &grid, unsigned &nbTour, const size_t matSize, unsigned &score, unsigned &combo) {
    bool frenzyB = frenzy(grid, matSize); // On regarde si le mode frenzy est actif
    bool dep;
    maPosition pos;
    char direction;
    unsigned points;
    displayGrid(grid);
    if (frenzyB){ // Si mode frenzy
        cout << "-- FRENZY MODE --" << endl;
        score += 10;
        nbTour = nbTour * 2;
    }
    cout << "Tours restants : " << nbTour << endl;
    cout << "Combo : " << combo << endl;
    cout << "Score : " << score << endl;
    while (true) { // Demande l'entrée de la position de la colonne tant qu'elle n'est pas valide
        cout << "Entrez le numéro de la colonne entre 1 et " << matSize <<  " : ";
        cin >> pos.abs;
        if (pos.abs < 1 || pos.abs > matSize) {
            cout << "Entrée non-valide" << endl;
            continue;
        }
        break;
    }
    while (true) { // Demande l'entrée de la position de la ligne tant qu'elle n'est pas valide
        cout << "Entrez le numéro de la ligne entre 1 et " << matSize <<  " : ";
        cin >> pos.ord;
        if (pos.ord < 1 || pos.ord > matSize) {
            cout << "Entrée non-valide" << endl;
            continue;
        }
        break;
    }
    pos.abs -= 1;
    pos.ord -= 1;
    while (true) { // Demande l'entrée de la direction de déplacement tant qu'elle n'est pas valide
        cout << "Entrez une direction de déplacement : ";
        cin >> direction;
        dep = makeAMove(grid, pos, direction);
        if (dep) break;
    }
    verifVide(grid, matSize); // Applique la gravité
    removeAll(grid, matSize, points, combo); // Enlève toutes les chaines
    score += points + combo; // On incrémente le score
}


/**
 * @brief Lance le mode classique du jeu.
 *
 * Demande la taille de la grille, initialise la grille,
 * gère les tours du joueur, et affiche le score final.
 */
void classicMode() {
    bool finPartie = true;
    unsigned score = 0;
    unsigned combo = 0;
    size_t matSize = 0;
    mat grid;
    cout << "-- Mode classique --" << '\n' << endl;
    while (matSize < 5){ // Demande un taille de grille tant qu'elle est inférieure à 5
        cout << "Entrez la taille de la grille (au moins 5) : ";
        cin >> matSize;
    }
    unsigned nbTour = 6 + 4 * (matSize - 4);
    initGrid(grid, matSize);
    while (nbTour > 0) { // Tant qu'il reste des tours on relance tour()
        tour(grid, nbTour, matSize, score, combo);
        --nbTour;
    }
    while (finPartie) { // Tant que l'utilisateur n'entre pas 0, on affiche l'écran de fin
        clearScreen();
        cout << "-- Fin de Partie --" << '\n' << "Score : " << score << '\n' << "Appuyez sur 0 pour retourner au menu principal" << endl;
        cin >> finPartie;
    }
}

/**
 * @brief Lance le mode pvp.
 *
 * Demande la taille de la grille, initialise deux grilles identiques,
 * gère les tours des deux joueurs, et affiche le gagnant à la fin.
 */
void pvpMode()
{
    bool finPartie = true;
    unsigned score1 = 0;
    unsigned combo1 = 0;
    unsigned score2 = 0;
    unsigned combo2 = 0;
    size_t matSize = 0;
    mat grid1;
    mat grid2;

    cout << "-- Mode 1v1 --" << '\n'
         << endl;
    while (matSize < 5) { // Demande un taille de grille tant qu'elle est inférieure à 5
        cout << "Entrez la taille de la grille (au moins 5) : ";
        cin >> matSize;
    }
    clearScreen();
    unsigned deb = 0;
    unsigned nbTour1 = 6 + 4 * (matSize - 4);
    unsigned nbTour2 = nbTour1;
    initGrid(grid1, matSize);
    grid2 = grid1;
    while (nbTour1 > 0 || nbTour2 > 0) // Tant qu'il reste des tours aux 2 joueurs
    {
        if (nbTour1 > 0) { // On passe au joueur 1 si il lui reste des tours
            cout << "Au tour du Joueur 1" << endl;
            while (deb != 1)
            {
                cout << "Appuyez sur 1 pour jouer" << endl;
                cin >> deb;
            }
            tour(grid1, nbTour1, matSize, score1, combo1);
            --nbTour1;
        }
        clearScreen();
        if (nbTour2 > 0) { // On passe au joueur 2 si il lui reste des tours
            cout << "Au tour du Joueur 2" << endl;
            while (deb != 2)
            {
                cout << "Appuyez sur 2 pour joueur" << endl;
                cin >> deb;
            }
            tour(grid2, nbTour2, matSize, score2, combo2);
            --nbTour2;
        }
    }

    while (finPartie) { // Tant que l'utilisateur n'entre pas 0, on affiche le gagnant
        clearScreen();
        cout << "-- Fin de partie --" << endl;
        if (score1 < score2)
        {
            cout << "Joueur 2 a gagné" << endl;
        }
        else if (score1 > score2)
        {
            cout << "Joueur 1 a gagné" << endl;
        }
        else
        {
            cout << "Egalité !" << endl;
        }
        cout << "Appuyez sur 0 pour retourner au menu principal" << endl;
        cin >> finPartie;
    }
}

/**
 * @brief Lance un certain niveau pour le mode histoire.
 *
 * Initialise la grille, gère les tours, calcule le score et détermine
 * si le niveau est réussi selon le score requis.
 *
 * @param nbNiveau Numéro du niveau.
 * @param scoreT Score total accumulé, mis à jour si le niveau est réussi.
 * @return true si le niveau est réussi, false sinon.
 */
bool niveau(unsigned const nbNiveau, unsigned &scoreT)
{
    bool reussi = false;
    unsigned combo = 0;
    unsigned score = 0;
    size_t matSize = 5 + 2 * nbNiveau;
    mat grid;
    unsigned nbTour = 6 + 4 * (matSize - 4);
    initGrid(grid, matSize);
    while (nbTour > 0) // Tant qu'il reste des tours on relance tour()
    {
        tour(grid, nbTour, matSize, score, combo);
        --nbTour;
    }
    clearScreen();
    if (score >= 10 + 5 * (matSize / 2) * nbNiveau) { // Si le score requis est atteint le niveau est réussi
        cout << "Niveau réussi" << endl;
        reussi = true;
        scoreT += score; // On ajoute au score total le score du niveau
    }
    else cout << "Niveau échoué" << endl; // Sinon le niveau est échoué
    unsigned nvSuivant = 0;
    while (nvSuivant != 1)
    {
        cout << "Appuyez sur 1 pour continuer" << endl;
        cin >> nvSuivant;
    }
    return reussi; // On renvoie si le niveau est réussi ou non
}


/**
 * @brief Boucle un niveau du mode histoire jusqu’à ce qu’il soit réussi.
 *
 * Affiche le lore du niveau en attendant que le joueur soit prêt
 * puis lance le niveau via niveau().
 *
 * @param nbNiveau Numéro du niveau à jouer.
 * @param ready Booléen indiquant si le joueur est prêt à commencer.
 * @param scoreT Score total accumulé, mis à jour après le niveau.
 * @param lore Texte de l’histoire associé à ce niveau.
 */
void boucleNiveau(unsigned nbNiveau, bool &ready, unsigned &scoreT, string lore){
    while (true) {
        ready = false;
        while (!ready) { // Tant que le joueur n'est pas prêt, on affiche toutes les infos du niveau
            cout << "-- Niveau "<< nbNiveau << " --" << '\n' << endl;
            cout << lore << '\n' << endl;
            cout << "Score à battre : " << 10 + 5 * ((5 + 2 * nbNiveau)/2) * nbNiveau << '\n' << endl;
            cout << "Appuyez sur 1 pour continuer" << endl;
            cin >> ready;
        }
        if (niveau(nbNiveau, scoreT)) break;
    }
}

/**
 * @brief Trie le leaderboard en insérant le nouveau score à la bonne position.
 *
 * Réorganise scores et names dans un ordre décroissant.
 *
 * @param scores Vecteur des scores à trier.
 * @param names Vecteur des noms correspondants aux scores.
 */
void triLeaderboard(vector<unsigned> &scores, vector<string> &names){
    size_t taille = scores.size();
    size_t indice = 0;
    unsigned nouvScore = scores[taille - 1]; // On garde en mémoire le nouveau score
    string nouvNom = names[taille - 1]; // On garde en mémoire le nom associé
    while (scores[indice] >= nouvScore && indice < taille - 1) ++indice; // On cherche le plus petit indice inférieur au nouveau score
    for (size_t i = taille - 1; i > indice; --i) { // On décale tous les éléments de names et scores de 1 vers la droite à partir de cet indice
        scores[i] = scores[i - 1];
        names[i] = names[i - 1];
    }
    scores[indice] = nouvScore; // On insère le nouveau score à l'indice donné
    names[indice] = nouvNom; // On insère le nom associé au même indice
}

/**
 * @brief Lance le mode histoire.
 *
 * Initialise les niveaux, affiche le lore, gère la progression à travers les niveaux,
 * et met à jour le leaderboard.
 *
 * @param scores Vecteur des scores pour le leaderboard, mis à jour à la fin.
 * @param names Vecteur des noms pour le leaderboard, mis à jour à la fin.
 */
void storyMode(vector<unsigned> &scores, vector<string> &names)
{
    vector<string> lore; // On met dans le vecteur lore tous les lores associés à chaque niveau
    lore.push_back("Voici ton premier adversaire. "
                   "C est seulement apres l avoir combattu que je pourrais juger ton envie de vivre. "
                   "Si tu perds, tu resteras bloquer ici, parmi nous, les nombres. "
                   "Que le combat commence !");
    lore.push_back("Bravo, on dirait que tu tiens a rejoindre tes proches, dans ton propre monde. "
                   "Voyons voir si tu feras l affaire face à ce nouveau bug ! "
                   "Attention a toi, tu pourrais tout perdre a jamais.");
    lore.push_back("On dirait que tu es plus coriace que je ne le pensais. "
                   "Je vais devoir endurcir mes bugs. "
                   "Essaye de survivre au plus precieux d entre eux ! Je pense que tu n y arriveras pas ! "
                   "Personne n a jamais pu le battre, il est bien trop complexe pour l intelligence humaine ! "
                   "Adieu faible Humain !");
    lore.push_back("Attend..Comment !? Tu es encore en vie ? Je dois admettre que tu es le premier humain a attiser ma curiosite. "
                   "Puisque tu as battu mes bugs les plus coriaces, je vais devoir t eliminer moi meme..Pret a mourir ?");
    lore.push_back("Tu as reussi, tu m as battu..Bravo a toi, humain.."
                   "Mais pour pouvoir rejoindre ton miserable monde, il va falloir ouvrir la porte qui separe les humains et nous, les nombres. "
                   "Arriveras tu a sortir d ici ? ");
    unsigned nbNiveau = 1;
    unsigned scoreT = 0;
    string name;
    bool ready = false;
    cout << "-- Mode Histoire --" << '\n' << endl;
    cout << "Bienvenue dans le monde numerique, jeune apprenti ! Ici, tout est reduis a de simples nombres. "
            "Notre devoir en tant que combattants est de detruire tous les bugs de programmation qui nous sont indiques. "
            "Pour cela, il faut supprimer le plus d erreurs en faisant des groupes de 3 meme chiffres, minimum. "
            "Pour commencer, tu m accompagneras pour detruire les plus petites erreurs, puis, apres m avoir prouve ta valeur et ta determination, "
            "tu pourras combattre a toi seul les plus grands bugs encore jamais resolus. "
            "Pret a servir la societe de ce monde futuriste ? " << '\n'
         << endl;
    while (!ready) { // On affiche le lore principal tant que l'utilisateur n'est pas prêt
        cout << "Appuyez sur 1 pour continuer" << endl;
        cin >> ready;
    }
    while (nbNiveau <= 5) { // Tant que l'utilisateur n'a pas réussi les 5 niveaux, on avance dans ceux-ci
        clearScreen();
        boucleNiveau(nbNiveau, ready, scoreT, lore[nbNiveau - 1]);
        ++nbNiveau;
    }
    clearScreen();
    cout << "Tu vis devant toi, une immense porte blanche. " << '\n'
         << "En t’y approchant, elle s’ouvrit doucement et te laissa voir le second monde, celui des humains. " << '\n'
         << "Ton monde. Tu avais réussi à survivre et à revenir à ta vie, près de tes proches. " << '\n'
         << "Mais, serait-t-elle la seule bataille contre les nombres ? Ou ne serait-ce que le début d’une longue guerre ? " << '\n'
         << "Seul le futur nous le dira." << endl; // Affichage du lore de fin
    cout << "Votre score final : " << scoreT << endl;
    cout << "Entrez votre nom : " << endl;
    cin >> name;
    scores.push_back(scoreT);
    names.push_back(name);
    triLeaderboard(scores, names); // On trie le leaderboard après avoir enregistré le nouveau score et son nom
}

/**
 * @brief Affiche le leaderboard avec les noms et scores.
 *
 * Parcourt les vecteurs scores et names et les affiche dans l’ordre.
 * Attend que l’utilisateur saisisse 0 pour retourner au menu principal.
 *
 * @param scores Vecteur des scores des joueurs.
 * @param names Vecteur des noms des joueurs correspondants aux scores.
 */
void displayLead(vector<unsigned> &scores, vector<string> &names) {
    bool lead = true;
    clearScreen();
    while (lead) { // Tant que l'utilisateur ne rentre pas 0
        for (size_t i = 0; i < scores.size(); ++i) { // Affiche le leaderboard
            cout << i + 1 << '.' << '\t' << names[i] << '\t' << scores[i] << endl;
        }
        cout << "Appuyez sur 0 pour retourner au menu principal" << endl;
        cin >> lead;
    }
}

/**
 * @brief Fonction principale du jeu.
 *
 * Initialise l’aléatoire, les vecteurs pour le leaderboard et la boucle principale du jeu.
 * Affiche le menu avec flux_cin() et gère le choix des modes :
 * - 0 : quitter
 * - 1 : mode histoire
 * - 2 : mode classique
 * - 3 : mode 1v1
 * - 4 : leaderboard
 * - 5 : règles
 *
 * @return 0 à la fin de l’exécution.
 */
int main()
{
    srand(time(0));
    bool jeu = true;
    vector<unsigned> scores;
    vector<string> names;
    while (jeu) { // Tant que l'utilisateur ne quitte pas le jeu
        clearScreen();
        ifstream menu("../../Menu.txt");
        flux_cin(menu);
        unsigned choix;
        cin >> choix;
        switch (choix) { // Sélectionne le mode selon le choix utilisateur
        case 0:
            cout << "Vous avez quitté le jeu" << endl;
            jeu = false;
            break;
        case 1:
            storyMode(scores, names);
            break;
        case 2:
            classicMode();
            break;
        case 3:
            pvpMode();
            break;
        case 4:
            displayLead(scores, names);
            break;
        case 5:
            displayRules();
            break;
        default:
            break;
        }
    }
    return 0;
}
