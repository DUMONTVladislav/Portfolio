# Portfolio — Vladislav DUMONT

Portfolio technique personnel développé avec **Vue 3 (Composition API)**, conçu avec une esthétique inspirée d'un **centre de contrôle / terminal** et un design system sur mesure basé sur des variables CSS (`--accent-color`, `--nav-bg`, `--text-color`), le *glassmorphism* et un mode clair/sombre.

Étudiant en **2ème année de BUT Informatique (parcours DEPLOI)** à l'IUT d'Aix-en-Provence, orienté infrastructures réseaux, bases de données et cybersécurité.

---

## Aperçu & Fonctionnalités

- **Navigation fixe & adaptative (`Navbar.vue`)** :
  - Indicateur actif animé sur ordinateur et détection automatique de la section visible au défilement (*scroll spy*).
  - Menu hamburger responsive sur tablette et mobile, s'ajustant dynamiquement à la hauteur de la barre et de la bannière d'alerte.
  - Bascule de thème clair / sombre.
- **Bannière d'alerte persistante (`AlertBanner.vue`)** :
  - Positionnée sous la barre de navigation avec calcul dynamique des hauteurs (`--navbar-height`, `--alert-height`) pour éviter tout chevauchement.
  - État de fermeture sauvegardé dans le `localStorage` et méthode `resetBanner()` exposée via `defineExpose` (utilisable en développement).
- **Présentation, Parcours & CV (`Home.vue`)** :
  - Présentation du profil et liens rapides vers les compétences et projets.
  - Chronologie du parcours académique et intégration du CV (`public/cv.pdf`) avec onglets dédiés sur tablette et mobile.
- **Compétences filtrables & triables (`Skills.vue`)** :
  - Séparation entre *Cursus Scolaire* et *Apprentissage Autodidacte & Personnel*.
  - Recherche textuelle, filtrage par catégories, tri par aisance ou ordre alphabétique, sections repliables et liens directs vers les projets associés.
- **Journal de bord / News (`News.vue`)** :
  - Flux d'articles triés automatiquement par date (du plus récent au plus ancien) et lecture détaillée dans une modale (avec support `Échap` et affichage d'illustration).
- **Projets & Terminal interactif (`Projects.vue` & `CandyCrushTerminal.vue`)** :
  - Filtrage par langages/outils, recherche, mise en avant des projets épinglés (`pinned`), carrousel d'images avec zoom *lightbox* et navigation croisée depuis les compétences.
  - Terminal interactif intégré pour le projet **Candy Crush** (C++), incluant des raccourcis contextuels et un retour à la ligne automatique pour les textes longs du mode Histoire.
- **Pied de page (`Footer.vue`)** :
  - Coordonnées, liens GitHub / LinkedIn et mentions légales.

---

## Stack technique

- **Framework** : [Vue 3](https://vuejs.org/) (`<script setup>`, Composition API)
- **Bundler** : [Vite](https://vitejs.dev/)
- **Styles** : CSS natif (`scoped` styles, variables CSS personnalisées, `color-mix()`, requêtes médias tablette & mobile)

---

## Installation & Lancement en local

1. **Cloner le dépôt** :
   ```bash
   git clone [https://github.com/DUMONTVladislav/Portfolio.git](https://github.com/DUMONTVladislav/Portfolio.git)
   cd Portfolio
   ```
2. **Installer les dépendances** :
   ```bash
   npm install
   ```
3. **Lancer le serveur de développement** :
   ```bash
   npm run dev
   ```
4. **Compiler pour la production** :
   ```bash
   npm run build
   ```
5. **Prévisualiser le build de production** :
   ```bash
   npm run preview
   ```
## Features à ajouter :

- Traduction en anglais

- Améliorations graphiques

- Optimisation du code

- Documentation

- Easter-eggs ?

## Contact

- Email : vladislav.dumont@gmail.com

- GitHub : github.com/DUMONTVladislav

- LinkedIn : linkedin.com/in/vladislav-dumont-2301753b3

© 2026 Vladislav DUMONT — Tous droits réservés.
