<script setup>
import { ref, computed } from 'vue'

const projectCategories = [
  {
    category: "Projets Universitaires",
    origin: "universitaire",
    projects: [
      {
        id: 2,
        title: "Systèmes de vote",
        languages: ["C++"],
        description: "Adaptation de plusieurs systèmes de vote en C++ et tests avec des fichiers Oracle",
        longDescription: "Ce projet universitaire a consisté à concevoir et implémenter différents systèmes de vote (scrutin majoritaire, proportionnel, etc.) en C++. Une attention particulière a été portée à la robustesse du code, à la gestion rigoureuse de la mémoire et à la validation des résultats via des jeux de tests et des fichiers Oracle.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 3,
        title: "Candy Crush",
        languages: ["C++"],
        description: "Recréation du jeu emblématique Candy Crush en C++ avec les modes suivants : classique, histoire, 1v1",
        longDescription: "Développement complet du jeu Candy Crush en C++ en architecture modulaire. Implémentation des algorithmes de détection d'alignements de bonbons, gestion des scores, de la gravité, et création de plusieurs modes de jeu stimulants : mode classique, mode histoire avec progression, et un mode 1v1 en réseau/local.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 4,
        title: "Page web statique : Rock O' Rama",
        languages: ["HTML", "CSS"],
        description: "Création de ma première page web statique sur le thème du rock !",
        longDescription: "Premier projet de webdesign et d'intégration HTML/CSS. Structuration sémantique du contenu, mise en page créative aux couleurs du rock, utilisation des balises modernes et application de styles personnalisés pour une immersion totale.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 5,
        title: "Modélisation et Exploitation d'une BDD : Les Tenracs",
        languages: ["SQL", "Python"],
        description: "Modélisation du système de la confrérie des TENders RAClette et exploitation de données générées via Faker",
        longDescription: "Conception complète d'une base de données relationnelle pour la confrérie fictive des TENders RAClette. Génération d'un volume important de données réalistes à l'aide de scripts Python et de la bibliothèque Faker, puis écriture de requêtes SQL complexes pour l'analyse et l'exploitation des données.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 6,
        title: "Statistiques PageRank",
        languages: ["Python"],
        description: "Analyse de l'algorithme de Google PageRank avec Python",
        longDescription: "Implémentation et analyse mathématique/statistique de l'algorithme PageRank popularisé par Google. Utilisation de Python pour modéliser le graphe du web, calcul des matrices de transition et étude de la convergence des scores d'autorité des pages.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 7,
        title: "Mise en place de serveurs Apache, DNS et MX",
        languages: ["Apache", "DNS", "MX"],
        description: "Mise en places des serveurs et premières notions de cybersécurité",
        longDescription: "Projet d'infrastructure réseau et système : déploiement et configuration complète de serveurs de noms (DNS), de serveurs web Apache (virtual hosts, sécurisation de base) et de serveurs de messagerie (MX). Application des premières bonnes pratiques de durcissement et de cybersécurité.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 8,
        title: "VigieChiro Compagnon",
        languages: ["Java", "JavaFX"],
        description: "Modélisation, visualisation, conception et tests d'une application portant sur l'étude de la faune de nuit",
        longDescription: "Application lourde en Java et JavaFX dédiée aux chercheurs étudiant les chiroptères (chauves-souris). Modélisation orientée objet rigoureuse, création d'une interface graphique interactive pour la visualisation de données de bio-acoustique nocturne, et mise en place de tests unitaires.",
        imageSrc: "",
        githubUrl: ""
      },
      {
        id: 9,
        title: "DataLab",
        languages: ["HTML", "CSS", "PHP", "SQL", "JavaScript"],
        description: "Création d'un site web de manipulation de BDD a but pédagogique",
        longDescription: "Plateforme web interactive et pédagogique permettant de s'initier aux bases de données. Combinaison de HTML/CSS et JavaScript pour le frontend, d'un backend en PHP et d'une connexion à une base de données pour permettre aux étudiants d'exécuter et de tester des requêtes en direct.",
        imageSrc: "",
        githubUrl: ""
      }
    ]
  },
  {
    category: "Projets Personnels",
    origin: "personnel",
    projects: [
      {
        id: 1,
        title: "Portfolio",
        languages: ["Vue.js", "CSS"],
        description: "Création d'un espace technique interactif avec design system sur mesure et esthétique de centre de contrôle",
        longDescription: "Conception et développement de ce portfolio personnel sous Vue.js (Composition API). Utilisation d'un design system futuriste inspiré des centres de contrôle, architecture hautement modulaire, composants réactifs avec filtrage dynamique et gestion des thèmes.",
        imageSrc: "",
        githubUrl: "https://github.com/DUMONTVladislav/Portfolio"
      }
    ]
  }
]

const allLanguages = [...new Set(projectCategories.flatMap(cat => cat.projects.flatMap(p => p.languages)))]
const selectedLanguages = ref([...allLanguages])
const searchQuery = ref('')

const isUniversitaireOpen = ref(true)
const isPersonnelOpen = ref(true)

// État pour la modale plein écran
const activeProject = ref(null)

const openModal = (project) => {
  activeProject.value = project
}

const closeModal = () => {
  activeProject.value = null
}

const toggleLanguage = (lang) => {
  if (selectedLanguages.value.includes(lang)) {
    selectedLanguages.value = selectedLanguages.value.filter(l => l !== lang)
  } else {
    selectedLanguages.value.push(lang)
  }
}

const filterProjects = (origin) => {
  const cat = projectCategories.find(c => c.origin === origin)
  if (!cat) return []

  return cat.projects.filter(project => {
    const matchesLang = project.languages.some(lang => selectedLanguages.value.includes(lang))
    const matchesSearch = project.title.toLowerCase().includes(searchQuery.value.toLowerCase()) || 
                          project.description.toLowerCase().includes(searchQuery.value.toLowerCase()) ||
                          project.languages.some(l => l.toLowerCase().includes(searchQuery.value.toLowerCase()))
    return matchesLang && matchesSearch
  })
}

const filteredUniversitaires = computed(() => filterProjects('universitaire'))
const filteredPersonnels = computed(() => filterProjects('personnel'))
</script>

<template>
  <section id="projects" class="projects-section">
    <h2>Mes projets</h2>

    <!-- Barre de contrôles -->
    <div class="projects-controls">
      <div class="search-group">
        <label for="project-search" class="control-label">Rechercher :</label>
        <input 
          id="project-search"
          type="text" 
          v-model="searchQuery" 
          placeholder="Ex: C++, Python, Portfolio..." 
          class="search-input"
        />
      </div>

      <div class="filter-group">
        <span class="control-label">Langages / Outils :</span>
        <label v-for="lang in allLanguages" :key="lang" class="checkbox-label">
          <input 
            type="checkbox" 
            :checked="selectedLanguages.includes(lang)" 
            @change="toggleLanguage(lang)"
          />
          {{ lang }}
        </label>
      </div>
    </div>

    <!-- Section Projets Universitaires -->
    <div class="project-category-group" v-if="filteredUniversitaires.length">
      <button class="category-toggle-btn" @click="isUniversitaireOpen = !isUniversitaireOpen">
        <span class="category-title-text">Projets Universitaires <span class="count-badge">({{ filteredUniversitaires.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isUniversitaireOpen }">▼</span>
      </button>
      
      <div class="projects-container" v-show="isUniversitaireOpen">
        <article 
          v-for="project in filteredUniversitaires" 
          :key="project.id" 
          class="project-card-large clickable-card"
          @click="openModal(project)"
        >
          <div class="project-screenshot-box">
            <img :src="project.imageSrc" :alt="project.title" class="project-screenshot" />
            <div class="zoom-overlay"><span>🔍 Agrandir</span></div>
          </div>

          <div class="project-content">
            <div class="project-languages-tags">
              <span class="project-tag-lang" v-for="lang in project.languages" :key="lang">{{ lang }}</span>
            </div>
            <h4>{{ project.title }}</h4>
            <p>{{ project.description }}</p>
            
            <div class="project-actions" v-if="project.githubUrl" @click.stop>
              <a :href="project.githubUrl" target="_blank" class="btn-outline">Voir sur GitHub</a>
            </div>
          </div>
        </article>
      </div>
    </div>

    <!-- Section Projets Personnels -->
    <div class="project-category-group" v-if="filteredPersonnels.length">
      <button class="category-toggle-btn" @click="isPersonnelOpen = !isPersonnelOpen">
        <span class="category-title-text">Projets Personnels <span class="count-badge">({{ filteredPersonnels.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isPersonnelOpen }">▼</span>
      </button>
      
      <div class="projects-container" v-show="isPersonnelOpen">
        <article 
          v-for="project in filteredPersonnels" 
          :key="project.id" 
          class="project-card-large clickable-card"
          @click="openModal(project)"
        >
          <div class="project-screenshot-box">
            <img :src="project.imageSrc" :alt="project.title" class="project-screenshot" />
            <div class="zoom-overlay"><span>🔍 Agrandir</span></div>
          </div>

          <div class="project-content">
            <div class="project-languages-tags">
              <span class="project-tag-lang" v-for="lang in project.languages" :key="lang">{{ lang }}</span>
            </div>
            <h4>{{ project.title }}</h4>
            <p>{{ project.description }}</p>
            
            <div class="project-actions" v-if="project.githubUrl" @click.stop>
              <a :href="project.githubUrl" target="_blank" class="btn-outline">Voir sur GitHub</a>
            </div>
          </div>
        </article>
      </div>
    </div>

    <!-- MODALE PLEIN ÉCRAN -->
    <div class="modal-backdrop" v-if="activeProject" @click="closeModal">
      <div class="modal-content" @click.stop>
        <button class="modal-close-btn" @click="closeModal">✕</button>
        
        <div class="modal-header">
          <div class="project-languages-tags">
            <span class="project-tag-lang" v-for="lang in activeProject.languages" :key="lang">{{ lang }}</span>
          </div>
          <h3>{{ activeProject.title }}</h3>
        </div>

        <div class="modal-body">
          <div class="modal-screenshot-box">
            <img :src="activeProject.imageSrc || ''" :alt="activeProject.title" class="modal-screenshot" />
            <span class="no-img-text" v-if="!activeProject.imageSrc">[ Capture d'écran en cours d'ajout ]</span>
          </div>

          <div class="modal-details">
            <h4>Description détaillée</h4>
            <p>{{ activeProject.longDescription || activeProject.description }}</p>
          </div>
        </div>

        <div class="modal-footer" v-if="activeProject.githubUrl">
          <a :href="activeProject.githubUrl" target="_blank" class="btn-outline">Voir le dépôt GitHub</a>
        </div>
      </div>
    </div>
  </section>
</template>

<style scoped>
.projects-section {
  padding: 4rem 2rem;
  max-width: 1200px;
  margin: 0 auto;
}

.projects-section > h2 {
  font-family: var(--font-title);
  font-size: 2rem;
  color: var(--accent-color);
  margin-bottom: 2rem;
  text-align: left;
}

.projects-controls {
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-radius: 10px;
  padding: 1.2rem;
  margin-bottom: 2.5rem;
  display: flex;
  flex-direction: column;
  gap: 1rem;
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
}

.search-group {
  display: flex;
  align-items: center;
  gap: 1rem;
}

.search-input {
  flex: 1;
  background: color-mix(in srgb, var(--text-color) 5%, transparent);
  border: 1px solid color-mix(in srgb, var(--text-color) 20%, transparent);
  color: var(--text-color);
  padding: 0.4rem 0.8rem;
  border-radius: 6px;
  font-size: 0.85rem;
  outline: none;
  transition: all 0.3s ease;
}

.search-input:focus {
  border-color: var(--accent-color);
  box-shadow: 0 0 8px var(--accent-color);
}

.filter-group {
  display: flex;
  flex-wrap: wrap;
  gap: 1rem;
  align-items: center;
}

.control-label {
  font-family: var(--font-title);
  font-size: 0.8rem;
  color: var(--accent-color);
  text-transform: uppercase;
  letter-spacing: 1px;
}

.checkbox-label {
  font-size: 0.85rem;
  color: var(--text-color);
  display: flex;
  align-items: center;
  gap: 0.4rem;
  cursor: pointer;
}

.project-category-group {
  margin-bottom: 2.5rem;
}

.category-toggle-btn {
  width: 100%;
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-left: 4px solid var(--accent-color);
  border-radius: 8px;
  padding: 1rem 1.25rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
  cursor: pointer;
  transition: all 0.3s ease;
  margin-bottom: 1.5rem;
  box-shadow: 0 0 8px rgba(0, 0, 0, 0.1);
}

.category-toggle-btn:hover {
  background: color-mix(in srgb, var(--accent-color) 10%, var(--nav-bg));
  box-shadow: 0 0 12px var(--accent-color);
}

.category-title-text {
  font-family: var(--font-title);
  font-size: 1.2rem;
  color: var(--text-color);
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.count-badge {
  font-size: 0.85rem;
  opacity: 0.7;
  font-family: sans-serif;
}

.toggle-icon {
  font-size: 0.9rem;
  color: var(--accent-color);
  transition: transform 0.3s ease;
}

.toggle-icon.rotated {
  transform: rotate(-90deg);
}

.projects-container {
  display: flex;
  flex-direction: column;
  gap: 2rem;
}

.project-card-large {
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-radius: 12px;
  padding: 2rem;
  display: flex;
  gap: 2.5rem;
  align-items: center;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);
  transition: all 0.3s ease;
  box-sizing: border-box;
  cursor: pointer;
}

.project-card-large:hover {
  box-shadow: 0 0 20px var(--accent-color);
  transform: translateY(-3px);
}

.project-screenshot-box {
  flex: 1.5;
  height: 250px;
  background: rgba(0, 0, 0, 0.4);
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
  position: relative;
  box-shadow: inset 0 0 10px rgba(0, 0, 0, 0.5);
}

.project-screenshot {
  width: 100%;
  height: 100%;
  object-fit: cover;
}

.zoom-overlay {
  position: absolute;
  inset: 0;
  background: rgba(0, 0, 0, 0.6);
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: 0;
  transition: opacity 0.3s ease;
  font-family: var(--font-title);
  color: var(--accent-color);
  font-size: 0.9rem;
  letter-spacing: 1px;
}

.project-card-large:hover .zoom-overlay {
  opacity: 1;
}

.project-content {
  flex: 1;
  display: flex;
  flex-direction: column;
  text-align: left;
}

.project-languages-tags {
  display: flex;
  flex-wrap: wrap;
  gap: 0.4rem;
  margin-bottom: 0.6rem;
}

.project-tag-lang {
  font-family: var(--font-title);
  font-size: 0.7rem;
  color: var(--accent-color);
  background: color-mix(in srgb, var(--accent-color) 15%, transparent);
  border: 1px solid var(--accent-color);
  padding: 0.1rem 0.5rem;
  border-radius: 4px;
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.project-content h4 {
  font-family: var(--font-title);
  font-size: 1.4rem;
  color: var(--text-color);
  margin: 0 0 0.8rem 0;
}

.project-content p {
  font-size: 0.9rem;
  opacity: 0.85;
  margin: 0 0 1.2rem 0;
  line-height: 1.5;
  color: var(--text-color);
}

.project-actions {
  display: flex;
}

.btn-outline {
  display: inline-block;
  padding: 0.6rem 1.2rem;
  font-family: var(--font-title);
  font-size: 0.85rem;
  text-decoration: none;
  color: var(--text-color);
  background: transparent;
  border: 1px solid var(--accent-color);
  border-radius: 6px;
  cursor: pointer;
  transition: all 0.3s ease;
  text-align: center;
}

.btn-outline:hover {
  background-color: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 12px var(--accent-color);
  transform: translateY(-2px);
}

/* STLES DE LA MODALE PLEIN ÉCRAN */
.modal-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.8);
  backdrop-filter: blur(5px);
  z-index: 1000;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 2rem;
}

.modal-content {
  background: var(--nav-bg);
  border: 2px solid var(--accent-color);
  border-radius: 14px;
  width: 100%;
  max-width: 900px;
  max-height: 90vh;
  overflow-y: auto;
  padding: 2.5rem;
  position: relative;
  box-shadow: 0 0 30px var(--accent-color);
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  box-sizing: border-box;
}

.modal-close-btn {
  position: absolute;
  top: 1.5rem;
  right: 1.5rem;
  background: transparent;
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  width: 35px;
  height: 35px;
  border-radius: 50%;
  font-size: 1rem;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: all 0.3s ease;
}

.modal-close-btn:hover {
  background: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 10px var(--accent-color);
}

.modal-header h3 {
  font-family: var(--font-title);
  font-size: 1.8rem;
  color: var(--text-color);
  margin-top: 0.5rem;
  text-align: left;
}

.modal-body {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  text-align: left;
}

.modal-screenshot-box {
  width: 100%;
  height: 350px;
  background: rgba(0, 0, 0, 0.5);
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
}

.modal-screenshot {
  width: 100%;
  height: 100%;
  object-fit: cover;
}

.no-img-text {
  font-family: var(--font-title);
  font-size: 0.9rem;
  color: var(--accent-color);
  opacity: 0.7;
}

.modal-details h4 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  color: var(--accent-color);
  margin-bottom: 0.5rem;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.modal-details p {
  font-size: 0.95rem;
  line-height: 1.6;
  opacity: 0.9;
  color: var(--text-color);
  margin: 0;
}

.modal-footer {
  display: flex;
  justify-content: flex-start;
  margin-top: 0.5rem;
}
</style>