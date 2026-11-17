/**
 * @file candyCrushEngine.js
 * @brief Moteur logique de Candy Crush - Reproduction fidèle de main.cpp
 *
 * Implémentation JavaScript directe et modulaire du jeu console C++
 * Développé initialement par Vladislav Dumont, Anna Boin, Lucas Franceschi--Pinson
 */

export const MENU_TEXT = `================================================================================
-- Candy Crush --
Sélectionnez un mode en entrant le chiffre associé :

1. Mode Histoire
2. Mode Classique
3. Mode 1v1
4. Leaderboard
5. Instructions
0. Quitter
================================================================================`;

export const RULES_TEXT = `================================================================================
-- Règles --

Déplacements :
* Sélectionnez les coordonnées d'une case
* Z - Haut, Q - Gauche, S - Bas, D - Droite, pour la déplacer

But du jeu :
* Aligner au moins 3 mêmes chiffres pour les faire disparaître
* Atteindre le plus gros score en un nombre de déplacements limités

Appuyez sur 0 pour quitter
================================================================================`;

export const KReset = 0;
export const KNbCandies = 9;

export class CandyCrushEngine {
  constructor(io) {
    this.io = io; // { print, println, clear, setColor, readLine }
    this.isAborted = false;
    this.scores = [];
    this.names = [];
  }

  abort() {
    this.isAborted = true;
  }

  // --- Fonctions utilitaires C++ ---

  clearScreen() {
    this.io.clear();
  }

  couleur(coul) {
    this.io.setColor(coul);
  }

  initGrid(grid, matSize) {
    grid.length = 0;
    for (let i = 0; i < matSize; ++i) {
      const a = [];
      for (let j = 0; j < matSize; ++j) {
        a.push(Math.floor(Math.random() * KNbCandies) + 1);
      }
      grid.push(a);
    }
  }

  displayGrid(grid) {
    this.clearScreen();
    this.couleur(KReset);
    for (let i = 0; i < grid.length; ++i) {
      for (let j = 0; j < grid.length; ++j) {
        const courant = grid[i][j];
        this.io.print('|');
        if (courant === 0) {
          this.couleur(37); // invisible / blanc
        } else {
          this.couleur(courant % 8 === 6 ? 31 : 31 + (courant % 8));
        }
        this.io.print(String(courant));
        this.couleur(KReset);
      }
      this.io.println('|');
    }
  }

  makeAMove(grid, pos, direction) {
    let dep;
    let chiffreChoisi;
    const dir = String(direction).toLowerCase();
    switch (dir) {
      case 's':
        if (pos.ord >= grid.length - 1) {
          this.io.println('Déplacement non-valide');
          dep = false;
        } else {
          chiffreChoisi = grid[pos.ord][pos.abs];
          grid[pos.ord][pos.abs] = grid[pos.ord + 1][pos.abs];
          grid[pos.ord + 1][pos.abs] = chiffreChoisi;
          dep = true;
        }
        break;
      case 'z':
        if (pos.ord === 0) {
          this.io.println('Déplacement non-valide');
          dep = false;
        } else {
          chiffreChoisi = grid[pos.ord][pos.abs];
          grid[pos.ord][pos.abs] = grid[pos.ord - 1][pos.abs];
          grid[pos.ord - 1][pos.abs] = chiffreChoisi;
          dep = true;
        }
        break;
      case 'q':
        if (pos.abs === 0) {
          this.io.println('Déplacement non-valide');
          dep = false;
        } else {
          chiffreChoisi = grid[pos.ord][pos.abs];
          grid[pos.ord][pos.abs] = grid[pos.ord][pos.abs - 1];
          grid[pos.ord][pos.abs - 1] = chiffreChoisi;
          dep = true;
        }
        break;
      case 'd':
        if (pos.abs >= grid.length - 1) {
          this.io.println('Déplacement non-valide');
          dep = false;
        } else {
          chiffreChoisi = grid[pos.ord][pos.abs];
          grid[pos.ord][pos.abs] = grid[pos.ord][pos.abs + 1];
          grid[pos.ord][pos.abs + 1] = chiffreChoisi;
          dep = true;
        }
        break;
      default:
        this.io.println('Déplacement non-valide');
        dep = false;
        break;
    }
    return dep;
  }

  atLeastThreeInAColumn(grid, pos, res) {
    const col = pos.abs;
    pos.ord = 0;
    let courant = grid[0][col];
    res.howMany = 1;
    for (let i = 1; i < grid.length; ++i) {
      if (grid[i][col] === courant && courant !== 0) {
        ++res.howMany;
      } else {
        if (res.howMany >= 3 && courant !== 0) return true;
        courant = grid[i][col];
        res.howMany = courant === 0 ? 0 : 1;
        pos.ord = i;
      }
    }
    return res.howMany >= 3 && courant !== 0;
  }

  atLeastThreeInARow(grid, pos, res) {
    const row = pos.ord;
    pos.abs = 0;
    let courant = grid[row][0];
    res.howMany = 1;
    for (let i = 1; i < grid.length; ++i) {
      if (grid[row][i] === courant && courant !== 0) {
        ++res.howMany;
      } else {
        if (res.howMany >= 3 && courant !== 0) return true;
        courant = grid[row][i];
        res.howMany = courant === 0 ? 0 : 1;
        pos.abs = i;
      }
    }
    return res.howMany >= 3 && courant !== 0;
  }

  removalInColumn(grid, pos, howMany, matSize) {
    for (let i = pos.ord; i < pos.ord + howMany; ++i) {
      grid[i][pos.abs] = 0;
    }
    for (let i = pos.ord + howMany; i < matSize; ++i) {
      grid[i - howMany][pos.abs] = grid[i][pos.abs];
      grid[i][pos.abs] = 0;
    }
  }

  removalInRow(grid, pos, howMany, matSize) {
    for (let i = pos.abs; i < pos.abs + howMany; ++i) {
      grid[pos.ord][i] = 0;
    }
    for (let j = pos.abs; j < pos.abs + howMany; ++j) {
      for (let i = pos.ord + 1; i < matSize; ++i) {
        grid[i - 1][j] = grid[i][j];
        grid[i][j] = 0;
      }
    }
  }

  removeAll(grid, matSize, scoreRef) {
    const posR = { abs: 0, ord: 0 };
    const res = { howMany: 0 };
    let comboP = false;
    scoreRef.points = 0;
    while (true) {
      let modif = false;
      for (let i = 0; i < matSize; ++i) {
        posR.abs = i;
        posR.ord = 0;
        while (this.atLeastThreeInAColumn(grid, posR, res)) {
          ++scoreRef.combo;
          scoreRef.points += res.howMany - 2;
          this.removalInColumn(grid, posR, res.howMany, matSize);
          modif = true;
          comboP = true;
        }
      }
      for (let i = 0; i < matSize; ++i) {
        posR.abs = 0;
        posR.ord = i;
        while (this.atLeastThreeInARow(grid, posR, res)) {
          ++scoreRef.combo;
          scoreRef.points += res.howMany - 2;
          this.removalInRow(grid, posR, res.howMany, matSize);
          modif = true;
          comboP = true;
        }
      }
      if (!modif) break;
    }
    if (!comboP) scoreRef.combo = 0;
  }

  verifVide(grid, matSize) {
    for (let j = 0; j < matSize; ++j) {
      let libre = 0;
      for (let i = 0; i < matSize; ++i) {
        if (grid[i][j] !== 0) {
          grid[libre][j] = grid[i][j];
          if (libre !== i) grid[i][j] = 0;
          ++libre;
        }
      }
    }
  }

  inVect(numbers, num) {
    return numbers.includes(num);
  }

  frenzy(grid, matSize) {
    let vide = true;
    const numbers = [];
    for (let i = 0; i < matSize; ++i) {
      for (let j = 0; j < matSize; ++j) {
        if (!this.inVect(numbers, grid[i][j]) && grid[i][j] !== 0) {
          numbers.push(grid[i][j]);
        }
      }
    }
    for (const nb of numbers) {
      let compteur = 0;
      for (let i = 0; i < matSize; ++i) {
        for (let j = 0; j < matSize; ++j) {
          if (grid[i][j] === nb) ++compteur;
          if (compteur >= 3) vide = false;
        }
      }
    }
    if (vide) {
      for (let i = 0; i < matSize; ++i) {
        for (let j = 0; j < matSize; ++j) {
          if (grid[i][j] === 0) {
            grid[i][j] = Math.floor(Math.random() * KNbCandies) + 1;
          }
        }
      }
    }
    return vide;
  }

  async tour(grid, tourRef, matSize, scoreRef) {
    const frenzyB = this.frenzy(grid, matSize);
    let dep = false;
    const pos = { abs: 0, ord: 0 };
    let direction = '';
    const pointsObj = { points: 0, combo: scoreRef.combo };

    this.displayGrid(grid);
    if (frenzyB) {
      this.io.println('-- FRENZY MODE --');
      scoreRef.score += 10;
      tourRef.nbTour = tourRef.nbTour * 2;
    }
    this.io.println('Tours restants : ' + tourRef.nbTour);
    this.io.println('Combo : ' + scoreRef.combo);
    this.io.println('Score : ' + scoreRef.score);

    while (!this.isAborted) {
      const input = await this.io.readLine(
        'Entrez le numéro de la colonne entre 1 et ' + matSize + ' : ',
        { type: 'col', max: matSize }
      );
      if (this.isAborted || input === null || input === undefined) return;
      const parsed = parseInt(input, 10);
      if (isNaN(parsed) || parsed < 1 || parsed > matSize) {
        this.io.println('Entrée non-valide');
        continue;
      }
      pos.abs = parsed;
      break;
    }

    while (!this.isAborted) {
      const input = await this.io.readLine(
        'Entrez le numéro de la ligne entre 1 et ' + matSize + ' : ',
        { type: 'row', max: matSize }
      );
      if (this.isAborted || input === null || input === undefined) return;
      const parsed = parseInt(input, 10);
      if (isNaN(parsed) || parsed < 1 || parsed > matSize) {
        this.io.println('Entrée non-valide');
        continue;
      }
      pos.ord = parsed;
      break;
    }

    pos.abs -= 1;
    pos.ord -= 1;

    while (!this.isAborted) {
      const input = await this.io.readLine(
        'Entrez une direction de déplacement : ',
        { type: 'direction' }
      );
      if (this.isAborted || input === null || input === undefined) return;
      direction = input.trim().charAt(0);
      dep = this.makeAMove(grid, pos, direction);
      if (dep) break;
    }

    this.verifVide(grid, matSize);
    this.removeAll(grid, matSize, pointsObj);
    scoreRef.combo = pointsObj.combo;
    scoreRef.score += pointsObj.points + pointsObj.combo;
  }

  async classicMode() {
    let finPartie = true;
    const scoreRef = { score: 0, combo: 0 };
    let matSize = 0;
    const grid = [];

    this.io.println('-- Mode classique --\n');
    while (matSize < 5 && !this.isAborted) {
      const input = await this.io.readLine(
        'Entrez la taille de la grille (au moins 5) : ',
        { type: 'size', min: 5 }
      );
      if (this.isAborted || input === null || input === undefined) return;
      const parsed = parseInt(input, 10);
      if (!isNaN(parsed) && parsed >= 5) {
        matSize = parsed;
      }
    }

    const tourRef = { nbTour: 6 + 4 * (matSize - 4) };
    this.initGrid(grid, matSize);

    while (tourRef.nbTour > 0 && !this.isAborted) {
      await this.tour(grid, tourRef, matSize, scoreRef);
      if (this.isAborted) return;
      --tourRef.nbTour;
    }

    while (finPartie && !this.isAborted) {
      this.clearScreen();
      this.io.println(
        '-- Fin de Partie --\nScore : ' +
          scoreRef.score +
          '\nAppuyez sur 0 pour retourner au menu principal'
      );
      const input = await this.io.readLine('', { type: 'confirm_0' });
      if (this.isAborted || input === null || input === undefined) return;
      if (input.trim() === '0') {
        finPartie = false;
      }
    }
  }

  async pvpMode() {
    let finPartie = true;
    const score1 = { score: 0, combo: 0 };
    const score2 = { score: 0, combo: 0 };
    let matSize = 0;
    const grid1 = [];

    this.io.println('-- Mode 1v1 --\n');
    while (matSize < 5 && !this.isAborted) {
      const input = await this.io.readLine(
        'Entrez la taille de la grille (au moins 5) : ',
        { type: 'size', min: 5 }
      );
      if (this.isAborted || input === null || input === undefined) return;
      const parsed = parseInt(input, 10);
      if (!isNaN(parsed) && parsed >= 5) {
        matSize = parsed;
      }
    }

    this.clearScreen();
    let deb = 0;
    const tourRef1 = { nbTour: 6 + 4 * (matSize - 4) };
    const tourRef2 = { nbTour: tourRef1.nbTour };
    this.initGrid(grid1, matSize);
    const grid2 = grid1.map((r) => [...r]);

    while ((tourRef1.nbTour > 0 || tourRef2.nbTour > 0) && !this.isAborted) {
      if (tourRef1.nbTour > 0) {
        this.io.println('Au tour du Joueur 1');
        deb = 0;
        while (deb !== 1 && !this.isAborted) {
          const input = await this.io.readLine('Appuyez sur 1 pour jouer\n', {
            type: 'confirm_1'
          });
          if (this.isAborted || input === null || input === undefined) return;
          deb = parseInt(input, 10);
        }
        await this.tour(grid1, tourRef1, matSize, score1);
        if (this.isAborted) return;
        --tourRef1.nbTour;
      }

      this.clearScreen();
      if (tourRef2.nbTour > 0) {
        this.io.println('Au tour du Joueur 2');
        deb = 0;
        while (deb !== 2 && !this.isAborted) {
          const input = await this.io.readLine('Appuyez sur 2 pour jouer\n', {
            type: 'confirm_2'
          });
          if (this.isAborted || input === null || input === undefined) return;
          deb = parseInt(input, 10);
        }
        await this.tour(grid2, tourRef2, matSize, score2);
        if (this.isAborted) return;
        --tourRef2.nbTour;
      }
    }

    while (finPartie && !this.isAborted) {
      this.clearScreen();
      this.io.println('-- Fin de partie --');
      if (score1.score < score2.score) {
        this.io.println('Joueur 2 a gagné');
      } else if (score1.score > score2.score) {
        this.io.println('Joueur 1 a gagné');
      } else {
        this.io.println('Egalité !');
      }
      this.io.println('Appuyez sur 0 pour retourner au menu principal');
      const input = await this.io.readLine('', { type: 'confirm_0' });
      if (this.isAborted || input === null || input === undefined) return;
      if (input.trim() === '0') {
        finPartie = false;
      }
    }
  }

  async niveau(nbNiveau, scoreTRef) {
    let reussi = false;
    const scoreRef = { score: 0, combo: 0 };
    const matSize = 5 + 2 * nbNiveau;
    const grid = [];
    const tourRef = { nbTour: 6 + 4 * (matSize - 4) };
    this.initGrid(grid, matSize);

    while (tourRef.nbTour > 0 && !this.isAborted) {
      await this.tour(grid, tourRef, matSize, scoreRef);
      if (this.isAborted) return false;
      --tourRef.nbTour;
    }

    this.clearScreen();
    const seuil = 10 + 5 * Math.floor(matSize / 2) * nbNiveau;
    if (scoreRef.score >= seuil) {
      this.io.println('Niveau réussi');
      reussi = true;
      scoreTRef.scoreT += scoreRef.score;
    } else {
      this.io.println('Niveau échoué');
    }

    let nvSuivant = 0;
    while (nvSuivant !== 1 && !this.isAborted) {
      const input = await this.io.readLine('Appuyez sur 1 pour continuer\n', {
        type: 'confirm_1'
      });
      if (this.isAborted || input === null || input === undefined) return false;
      nvSuivant = parseInt(input, 10);
    }
    return reussi;
  }

  async boucleNiveau(nbNiveau, readyRef, scoreTRef, lore) {
    while (!this.isAborted) {
      readyRef.ready = false;
      while (!readyRef.ready && !this.isAborted) {
        this.io.println('-- Niveau ' + nbNiveau + ' --\n');
        this.io.println(lore + '\n');
        const scoreABattre =
          10 + 5 * Math.floor((5 + 2 * nbNiveau) / 2) * nbNiveau;
        this.io.println('Score à battre : ' + scoreABattre + '\n');
        const input = await this.io.readLine('Appuyez sur 1 pour continuer\n', {
          type: 'confirm_1'
        });
        if (this.isAborted || input === null || input === undefined) return;
        if (parseInt(input, 10) === 1) readyRef.ready = true;
      }
      const success = await this.niveau(nbNiveau, scoreTRef);
      if (this.isAborted) return;
      if (success) break;
    }
  }

  triLeaderboard(scores, names) {
    const taille = scores.length;
    let indice = 0;
    const nouvScore = scores[taille - 1];
    const nouvNom = names[taille - 1];
    while (scores[indice] >= nouvScore && indice < taille - 1) ++indice;
    for (let i = taille - 1; i > indice; --i) {
      scores[i] = scores[i - 1];
      names[i] = names[i - 1];
    }
    scores[indice] = nouvScore;
    names[indice] = nouvNom;
  }

  async storyMode() {
    const lore = [
      'Voici ton premier adversaire. C est seulement apres l avoir combattu que je pourrais juger ton envie de vivre. Si tu perds, tu resteras bloquer ici, parmi nous, les nombres. Que le combat commence !',
      'Bravo, on dirait que tu tiens a rejoindre tes proches, dans ton propre monde. Voyons voir si tu feras l affaire face à ce nouveau bug ! Attention a toi, tu pourrais tout perdre a jamais.',
      'On dirait que tu es plus coriace que je ne le pensais. Je vais devoir endurcir mes bugs. Essaye de survivre au plus precieux d entre eux ! Je pense que tu n y arriveras pas ! Personne n a jamais pu le battre, il est bien trop complexe pour l intelligence humaine ! Adieu faible Humain !',
      'Attend..Comment !? Tu es encore en vie ? Je dois admettre que tu es le premier humain a attiser ma curiosite. Puisque tu as battu mes bugs les plus coriaces, je vais devoir t eliminer moi meme..Pret a mourir ?',
      'Tu as reussi, tu m as battu..Bravo a toi, humain..Mais pour pouvoir rejoindre ton miserable monde, il va falloir ouvrir la porte qui separe les humains et nous, les nombres. Arriveras tu a sortir d ici ? '
    ];

    let nbNiveau = 1;
    const scoreTRef = { scoreT: 0 };
    const readyRef = { ready: false };

    this.io.println('-- Mode Histoire --\n');
    this.io.println(
      'Bienvenue dans le monde numerique, jeune apprenti ! Ici, tout est reduis a de simples nombres. ' +
        'Notre devoir en tant que combattants est de detruire tous les bugs de programmation qui nous sont indiques. ' +
        'Pour cela, il faut supprimer le plus d erreurs en faisant des groupes de 3 meme chiffres, minimum. ' +
        'Pour commencer, tu m accompagneras pour detruire les plus petites erreurs, puis, apres m avoir prouve ta valeur et ta determination, ' +
        'tu pourras combattre a toi seul les plus grands bugs encore jamais resolus. ' +
        'Pret a servir la societe de ce monde futuriste ?\n'
    );

    while (!readyRef.ready && !this.isAborted) {
      const input = await this.io.readLine('Appuyez sur 1 pour continuer\n', {
        type: 'confirm_1'
      });
      if (this.isAborted || input === null || input === undefined) return;
      if (parseInt(input, 10) === 1) readyRef.ready = true;
    }

    while (nbNiveau <= 5 && !this.isAborted) {
      this.clearScreen();
      await this.boucleNiveau(
        nbNiveau,
        readyRef,
        scoreTRef,
        lore[nbNiveau - 1]
      );
      if (this.isAborted) return;
      ++nbNiveau;
    }

    this.clearScreen();
    this.io.println(
      'Tu vis devant toi, une immense porte blanche.\n' +
        'En t’y approchant, elle s’ouvrit doucement et te laissa voir le second monde, celui des humains.\n' +
        'Ton monde. Tu avais réussi à survivre et à revenir à ta vie, près de tes proches.\n' +
        'Mais, serait-t-elle la seule bataille contre les nombres ? Ou ne serait-ce que le début d’une longue guerre ?\n' +
        'Seul le futur nous le dira.'
    );
    this.io.println('Votre score final : ' + scoreTRef.scoreT);
    const name = await this.io.readLine('Entrez votre nom : \n', {
      type: 'name'
    });
    if (this.isAborted || name === null || name === undefined) return;
    this.scores.push(scoreTRef.scoreT);
    this.names.push(name.trim() || 'Joueur');
    this.triLeaderboard(this.scores, this.names);
  }

  async displayLead() {
    let lead = true;
    this.clearScreen();
    while (lead && !this.isAborted) {
      for (let i = 0; i < this.scores.length; ++i) {
        this.io.println(
          i + 1 + '.\t' + this.names[i] + '\t' + this.scores[i]
        );
      }
      this.io.println('Appuyez sur 0 pour retourner au menu principal');
      const input = await this.io.readLine('', { type: 'confirm_0' });
      if (this.isAborted || input === null || input === undefined) return;
      if (input.trim() === '0') lead = false;
    }
  }

  async displayRules() {
    let regles = true;
    while (regles && !this.isAborted) {
      this.clearScreen();
      this.io.println(RULES_TEXT);
      const input = await this.io.readLine('', { type: 'confirm_0' });
      if (this.isAborted || input === null || input === undefined) return;
      if (input.trim() === '0') regles = false;
    }
  }

  async start() {
    this.isAborted = false;
    let jeu = true;
    while (jeu && !this.isAborted) {
      this.clearScreen();
      this.io.println(MENU_TEXT);
      const input = await this.io.readLine('', { type: 'menu' });
      if (this.isAborted || input === null || input === undefined) return;
      const choix = parseInt(input.trim(), 10);
      switch (choix) {
        case 0:
          this.io.println('Vous avez quitté le jeu');
          jeu = false;
          break;
        case 1:
          await this.storyMode();
          break;
        case 2:
          await this.classicMode();
          break;
        case 3:
          await this.pvpMode();
          break;
        case 4:
          await this.displayLead();
          break;
        case 5:
          await this.displayRules();
          break;
        default:
          break;
      }
    }
  }
}
