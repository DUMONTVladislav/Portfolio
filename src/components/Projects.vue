<script setup>
import { ref, computed } from 'vue'

const projectCategories = [
  {
    category: "Projets Universitaires",
    origin: "universitaire",
    projects: [
      {
        title: "Systèmes de vote",
        languages: ["C++"],
        description: "Adaptation de plusieurs systèmes de vote en C++ et tests avec des fichiers Oracle",
        longDescription: "Pour ma première expérience en C++ il m'a été demandé à moi et mon groupe de recréer 3 systèmes de vote : le vote majoritaire à 2 tours (utilisé actuellement en France), la méthode de Borda (liste de choix) et le vote limité (scrutin plurinominal majoritaire). Les programmes fonctionnent à l'aide de fichiers d'entrées et les sorties sont comparées à un fichier Oracle pour vérifier leur veracité.",
        images: ["vote.jpg"],
        githubUrl: ""
      },
      {
        title: "Candy Crush",
        languages: ["C++"],
        description: "Recréation du jeu emblématique Candy Crush en C++ avec les modes suivants : classique, histoire, 1v1",
        longDescription: "Ce deuxième projet en C++ demandait de recréer cette fois-ci Candy-Crush, l'un des jeux les plus connus sur téléphone. Cette version fonctionne au tour par tour mais simule tout de même le système de combo et la gravité. Plusieurs mode de jeu sont disponible tels que le mode Classique, le mode 1v1, et même un mode Histoire ! BONUS : le jeu est jouable depuis cette page, testez le !",
        images: [],
        githubUrl: ""
      },
      {
        title: "Page web statique : Rock O' Rama",
        languages: ["HTML", "CSS"],
        description: "Création de ma première page web statique sur le thème du rock !",
        longDescription: "Pour ma première impression d'HTML et CSS, il nous est demandé de créer une page web statique comportant plusieurs caractéristiques : plusieurs pages responsives avec navbar et menu hamburger maximisant google lighthouse. Je vous présente donc Rock O' Rama !",
        images: ["ROR1.png", "ROR2.png"],
        githubUrl: "https://github.com/DUMONTVladislav/Rock_O_Rama"
      },
      {
        title: "Modélisation et Exploitation d'une BDD : Les Tenracs",
        languages: ["SQL", "Python"],
        description: "Modélisation du système de la confrérie des TENders RAClette et exploitation de données générées via Faker",
        longDescription: "La confrérie imaginaire des TENRACs avait besoin d'une base de donnée fonctionnelle afin d'organiser leurs prochains repas. Nous nous sommes donc occupé de la création d'un MCD opérationnel avec Looping. Pour faire des statistiques de cette base de données, il a fallu créer des fausses données avec Faker puis les analyser de manière pertinente avec des bibliothèques Python telles que pandas, numpy, etc...",
        images: ["TRL.png", "TRS1.png", "TRS2.png", "TRC1.png", "TRC2.png"],
        githubUrl: "https://github.com/DUMONTVladislav/SAE-Exploitation-BDD"
      },
      {
        title: "Statistiques PageRank",
        languages: ["Python"],
        description: "Analyse de l'algorithme de Google PageRank avec Python",
        longDescription: "PageRank est un algorithme utilisé pour gérer le système de référencement des sites webs. Nous avons donc tout d'abord recréé un semblant de l'algorithme et l'avons testé avec des matrices simulant un web.",
        images: ["PR.png"],
        githubUrl: ""
      },
      {
        title: "Mise en place de serveurs Apache, DNS et MX",
        languages: ["Apache", "DNS", "MX"],
        description: "Mise en places des serveurs et premières notions de cybersécurité",
        longDescription: "Pour ma première expérience en réseau, moi et mon coéquipier avons mis en place un serveur Apache ainsi que deux serveurs DNS (primaire / secondaire) et un serveur de messagerie (MX). Nous avons pu nous sensibiliser sur la cybersécurité et les mesures à prendre en lançant une attaque DoS depuis une VM pirate.",
        images: ["Apache.png"],
        githubUrl: ""
      },
      {
        title: "VigieChiro Compagnon",
        languages: ["Java", "JavaFX"],
        description: "Modélisation, visualisation, conception et tests d'une application portant sur l'étude de la faune de nuit",
        longDescription: "Nous avons contribué à l'application VigieChiro Compagnon en réalisant des tests unitaires pour valider chaque étape de notre Model View Controller. Le but de cette application est de mesurer l'impact de l'éclairage artificiel sur la faune de nuit (chauve-souris principalement), pour faire cela biologistes et amateurs peuvent poser des capteurs de sons qui seront répertoriés et dont les sons seront analysés pour établir des statistiques selon la localisation géographique et l'heure de la journée.",
        images: ["VC.jpg"],
        githubUrl: ""
      },
      {
        title: "DataLab",
        languages: ["HTML", "CSS", "PHP", "SQL", "JavaScript"],
        description: "Création d'un site web de manipulation de BDD a but pédagogique",
        longDescription: "Mon plus gros projet à ce jour. Pour manipuler des bases de données les élèves peuvent utiliser des interprètes en lignes comme OneCompiler qui restent superficiels ou alors PhpMyAdmin qui est plus complet mais dont l'interface est rustique voire hostile pour des débutants. Le but de DataLab serait de faire un site web en ligne qui mélangerait l'aspect 'complet' de PhpMyAdmin tout en le rendant pédagogique comme la plateforme Ametice. Les élèves pourront réaliser des exercices disponibles selon leur année de formation, groupe de TP, etc..., en créant des espaces de travail reprenant la base de données du cours. Il est prévu d'ajouter si possible un système de gamification pour rendre le site plus 'ludique'.",
        images: [],
        githubUrl: ""
      }
    ]
  },
  {
    category: "Projets Personnels",
    origin: "personnel",
    projects: [
      {
        title: "Portfolio",
        languages: ["Vue.js", "CSS"],
        description: "Création d'un espace technique interactif avec design system sur mesure et esthétique de centre de contrôle",
        longDescription: "Conception et développement de ce portfolio personnel sous Vue.js (Composition API). Ajout de quelques features utiles telles que des barres de recherche, systèmes de filtrage, etc...",
        images: [],
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

const activeProject = ref(null)
const currentImageIndex = ref(0)
const zoomedImageSrc = ref(null)

const openModal = (project) => {
  activeProject.value = project
  currentImageIndex.value = 0
}

const closeModal = () => {
  activeProject.value = null
  currentImageIndex.value = 0
}

const nextImage = () => {
  if (activeProject.value && activeProject.value.images) {
    currentImageIndex.value = (currentImageIndex.value + 1) % activeProject.value.images.length
  }
}

const prevImage = () => {
  if (activeProject.value && activeProject.value.images) {
    currentImageIndex.value = (currentImageIndex.value - 1 + activeProject.value.images.length) % activeProject.value.images.length
  }
}

const openZoom = (imgSrc) => {
  if (imgSrc) {
    zoomedImageSrc.value = imgSrc
  }
}

const closeZoom = () => {
  zoomedImageSrc.value = null
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

    <div class="project-category-group" v-if="filteredUniversitaires.length">
      <button class="category-toggle-btn" @click="isUniversitaireOpen = !isUniversitaireOpen">
        <span class="category-title-text">Projets Universitaires <span class="count-badge">({{ filteredUniversitaires.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isUniversitaireOpen }">▼</span>
      </button>
      
      <div class="projects-container" v-show="isUniversitaireOpen">
        <article 
          v-for="project in filteredUniversitaires" 
          :key="project.title" 
          class="project-card-large clickable-card"
          @click="openModal(project)"
        >
          <div class="project-screenshot-box">
            <template v-if="project.images && project.images.length">
              <img 
                :src="project.images[0]" 
                :alt="project.title" 
                class="project-screenshot" 
              />
              <div class="zoom-overlay">
                <span>🔍 Agrandir</span>
              </div>
            </template>
            <div v-else class="no-img-box">
              <span class="no-img-text">
                {{ project.title === 'Portfolio' ? "A-ton vraiment besoin d'images ?" : "[ Capture d'écran en cours d'ajout ]" }}
              </span>
            </div>
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

    <div class="project-category-group" v-if="filteredPersonnels.length">
      <button class="category-toggle-btn" @click="isPersonnelOpen = !isPersonnelOpen">
        <span class="category-title-text">Projets Personnels <span class="count-badge">({{ filteredPersonnels.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isPersonnelOpen }">▼</span>
      </button>
      
      <div class="projects-container" v-show="isPersonnelOpen">
        <article 
          v-for="project in filteredPersonnels" 
          :key="project.title" 
          class="project-card-large clickable-card"
          @click="openModal(project)"
        >
          <div class="project-screenshot-box">
            <template v-if="project.images && project.images.length">
              <img 
                :src="project.images[0]" 
                :alt="project.title" 
                class="project-screenshot" 
              />
              <div class="zoom-overlay">
                <span>🔍 Agrandir</span>
              </div>
            </template>
            <div v-else class="no-img-box">
              <span class="no-img-text">
                {{ project.title === 'Portfolio' ? "A-ton vraiment besoin d'images ?" : "[ Capture d'écran en cours d'ajout ]" }}
              </span>
            </div>
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
          <div class="modal-screenshot-box" v-if="activeProject.images && activeProject.images.length">
            <button class="carousel-btn prev" @click="prevImage" v-if="activeProject.images.length > 1">❮</button>
            
            <img 
              :src="activeProject.images[currentImageIndex]" 
              :alt="activeProject.title" 
              class="modal-screenshot zoomable-img" 
              @click="openZoom(activeProject.images[currentImageIndex])"
              title="Cliquer pour zoomer en plein écran"
            />
            
            <button class="carousel-btn next" @click="nextImage" v-if="activeProject.images.length > 1">❯</button>
            
            <div class="carousel-counter" v-if="activeProject.images.length > 1">
              {{ currentImageIndex + 1 }} / {{ activeProject.images.length }}
            </div>
          </div>
          
          <div class="modal-screenshot-box" v-else>
            <span class="no-img-text">
              {{ activeProject.title === 'Portfolio' ? "A-ton vraiment besoin d'images ?" : "[ Capture d'écran en cours d'ajout ]" }}
            </span>
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

    <div class="zoom-lightbox-backdrop" v-if="zoomedImageSrc" @click="closeZoom">
      <div class="zoom-lightbox-content" @click.stop>
        <button class="modal-close-btn" @click="closeZoom">✕</button>
        <img :src="zoomedImageSrc" alt="Agrandissement de l'image" class="zoomed-full-img" />
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
  background: color-mix(in srgb, var(--accent-color) 5%, rgba(0, 0, 0, 0.8));
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
  position: relative;
  box-shadow: inset 0 0 15px rgba(0, 0, 0, 0.7);
}

.project-screenshot {
  width: 100%;
  height: 100%;
  object-fit: contain;
  z-index: 1;
}

.zoom-overlay {
  position: absolute;
  inset: 0;
  background: rgba(5, 8, 15, 0.75);
  backdrop-filter: blur(4px);
  display: flex;
  align-items: center;
  justify-content: center;
  opacity: 0;
  transition: opacity 0.3s ease;
  z-index: 2;
  pointer-events: none;
}

.zoom-overlay span {
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  padding: 0.6rem 1.2rem;
  border-radius: 6px;
  font-family: var(--font-title);
  font-size: 0.85rem;
  letter-spacing: 1px;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.8);
  transform: translateY(6px);
  transition: transform 0.3s ease, box-shadow 0.3s ease;
}

.project-card-large:hover .zoom-overlay {
  opacity: 1;
}

.project-card-large:hover .zoom-overlay span {
  transform: translateY(0);
  box-shadow: 0 0 12px var(--accent-color);
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
  z-index: 10;
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
  height: 320px;
  background: color-mix(in srgb, var(--accent-color) 5%, rgba(0, 0, 0, 0.8));
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
  position: relative;
  box-shadow: inset 0 0 15px rgba(0, 0, 0, 0.7);
}

.modal-screenshot {
  width: 100%;
  height: 100%;
  object-fit: contain;
}

.zoomable-img {
  cursor: zoom-in;
}

.carousel-btn {
  position: absolute;
  top: 50%;
  transform: translateY(-50%);
  background: rgba(0, 0, 0, 0.6);
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  width: 40px;
  height: 40px;
  border-radius: 50%;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1rem;
  z-index: 10;
  transition: all 0.3s ease;
}

.carousel-btn:hover {
  background: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 10px var(--accent-color);
}

.carousel-btn.prev {
  left: 1rem;
}

.carousel-btn.next {
  right: 1rem;
}

.carousel-counter {
  position: absolute;
  bottom: 0.8rem;
  right: 1rem;
  background: rgba(0, 0, 0, 0.7);
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  padding: 0.2rem 0.6rem;
  border-radius: 4px;
  font-family: var(--font-title);
  font-size: 0.75rem;
  letter-spacing: 1px;
}

.no-img-box {
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 1rem;
  text-align: center;
}

.no-img-text {
  font-family: var(--font-title);
  font-size: 0.9rem;
  color: var(--accent-color);
  opacity: 0.8;
  letter-spacing: 0.5px;
}

.modal-details {
  background: color-mix(in srgb, var(--text-color) 3%, transparent);
  border: 1px solid color-mix(in srgb, var(--accent-color) 30%, transparent);
  border-left: 3px solid var(--accent-color);
  border-radius: 8px;
  padding: 1.2rem;
}

.modal-details h4 {
  font-family: var(--font-title);
  font-size: 0.9rem;
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

.zoom-lightbox-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.9);
  backdrop-filter: blur(8px);
  z-index: 2000;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 2rem;
}

.zoom-lightbox-content {
  position: relative;
  max-width: 95vw;
  max-height: 95vh;
  display: flex;
  align-items: center;
  justify-content: center;
}

.zoomed-full-img {
  max-width: 90vw;
  max-height: 90vh;
  object-fit: contain;
  border: 2px solid var(--accent-color);
  border-radius: 8px;
  box-shadow: 0 0 40px var(--accent-color);
}
</style>