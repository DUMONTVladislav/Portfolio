<script setup>
import { ref, computed, onMounted, onUnmounted, nextTick } from 'vue'
import CandyCrushTerminal from './CandyCrushTerminal.vue'
import { useI18n } from '@/composables/useI18n.js'
import { useFocusTrap } from '@/composables/useFocusTrap.js'

const { t } = useI18n()

const projectCategories = [
  {
    category: "Projets Universitaires",
    origin: "universitaire",
    projects: [
      {
        id: "project-systemes-de-vote",
        title: "Systèmes de vote",
        languages: ["C++"],
        description: "Adaptation de plusieurs systèmes de vote en C++ et tests avec des fichiers Oracle",
        longDescription: "Pour ma première expérience en C++ il m'a été demandé à moi et mon groupe de recréer 3 systèmes de vote : le vote majoritaire à 2 tours (utilisé actuellement en France), la méthode de Borda (liste de choix) et le vote limité (scrutin plurinominal majoritaire). Les programmes fonctionnent à l'aide de fichiers d'entrées et les sorties sont comparées à un fichier Oracle pour vérifier leur veracité.",
        images: ["vote.jpg"],
        githubUrl: "",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-candy-crush",
        title: "Candy Crush",
        languages: ["C++"],
        description: "Recréation du jeu emblématique Candy Crush en C++ avec les modes suivants : classique, histoire, 1v1",
        longDescription: "Ce deuxième projet en C++ demandait de recréer cette fois-ci Candy-Crush, l'un des jeux les plus connus sur téléphone. Cette version fonctionne au tour par tour mais simule tout de même le système de combo et la gravité (inversée malheureusement). Plusieurs mode de jeu sont disponible tels que le mode Classique, le mode 1v1, et même un mode Histoire ! BONUS : le jeu est jouable depuis cette page, testez le ! (Jeu adapté au site web grâce à Antigravity)",
        images: [],
        githubUrl: "",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-rock-o-rama",
        title: "Page web statique : Rock O' Rama",
        languages: ["HTML", "CSS"],
        description: "Création de ma première page web statique sur le thème du rock !",
        longDescription: "Pour ma première impression d'HTML et CSS, il nous est demandé de créer une page web statique comportant plusieurs caractéristiques : plusieurs pages responsives avec navbar et menu hamburger maximisant google lighthouse. Je vous présente donc Rock O' Rama !",
        images: ["ROR1.png", "ROR2.png"],
        githubUrl: "https://github.com/DUMONTVladislav/Rock_O_Rama",
        siteUrl: "https://dumont-vladislav-25009525.github.io/Rock_O_Rama/",
        pinned: false
      },
      {
        id: "project-les-tenracs",
        title: "Modélisation et Exploitation d'une BDD : Les Tenracs",
        languages: ["SQL", "Python"],
        description: "Modélisation du système de la confrérie des TENders RAClette et exploitation de données générées via Faker",
        longDescription: "La confrérie imaginaire des TENRACs avait besoin d'une base de donnée fonctionnelle afin d'organiser leurs prochains repas. Nous nous sommes donc occupé de la création d'un MCD opérationnel avec Looping. Pour faire des statistiques de cette base de données, il a fallu créer des fausses données avec Faker puis les analyser de manière pertinente avec des bibliothèques Python telles que pandas, numpy, etc...",
        images: ["TRL.png", "TRS1.png", "TRS2.png", "TRC1.png", "TRC2.png"],
        githubUrl: "https://github.com/DUMONTVladislav/SAE-Exploitation-BDD",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-pagerank",
        title: "Statistiques PageRank",
        languages: ["Python"],
        description: "Analyse de l'algorithme de Google PageRank avec Python",
        longDescription: "PageRank est un algorithme utilisé pour gérer le système de référencement des sites webs. Nous avons donc tout d'abord recréé un semblant de l'algorithme et l'avons testé avec des matrices simulant un web.",
        images: ["PR.png"],
        githubUrl: "",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-serveurs-apache-dns-mx",
        title: "Mise en place de serveurs Apache, DNS et MX",
        languages: ["Apache", "DNS", "MX"],
        description: "Mise en places des serveurs et premières notions de cybersécurité",
        longDescription: "Pour ma première expérience en réseau, moi et mon coéquipier avons mis en place un serveur Apache ainsi que deux serveurs DNS (primaire / secondaire) et un serveur de messagerie (MX). Nous avons pu nous sensibiliser sur la cybersécurité et les mesures à prendre en lançant une attaque DoS depuis une VM pirate.",
        images: ["Apache.png"],
        githubUrl: "",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-vigiechiro",
        title: "VigieChiro Compagnon",
        languages: ["Java", "JavaFX"],
        description: "Modélisation, visualisation, conception et tests d'une application portant sur l'étude de la faune de nuit",
        longDescription: "Nous avons contribué à l'application VigieChiro Compagnon en réalisant des tests unitaires pour valider chaque étape de notre Model View Controller. Le but de cette application est de mesurer l'impact de l'éclairage artificiel sur la faune de nuit (chauve-souris principalement), pour faire cela biologistes et amateurs peuvent poser des capteurs de sons qui seront répertoriés et dont les sons seront analysés pour établir des statistiques selon la localisation géographique et l'heure de la journée.",
        images: ["VC.jpg"],
        githubUrl: "",
        siteUrl: "",
        pinned: false
      },
      {
        id: "project-datalab",
        title: "DataLab",
        languages: ["HTML", "CSS", "PHP", "SQL", "JavaScript"],
        description: "Création d'un site web de manipulation de BDD a but pédagogique",
        longDescription: "Mon plus gros projet à ce jour. Pour manipuler des bases de données les élèves peuvent utiliser des interprètes en lignes comme OneCompiler qui restent superficiels ou alors PhpMyAdmin qui est plus complet mais dont l'interface est rustique voire hostile pour des débutants. Le but de DataLab serait de faire un site web en ligne qui mélangerait l'aspect 'complet' de PhpMyAdmin tout en le rendant pédagogique comme la plateforme Ametice. Les élèves pourront réaliser des exercices disponibles selon leur année de formation, groupe de TP, etc..., en créant des espaces de travail reprenant la base de données du cours. Il est prévu d'ajouter si possible un système de gamification pour rendre le site plus 'ludique'.",
        images: [],
        githubUrl: "",
        siteUrl: "",
        pinned: true
      },
      {
        id: "project-flexarion",
        title: "Flexarion",
        languages: ["Communication"],
        description: "Stratégie de référencement avancée visant à positionner le site web Flexarion en première position sur Google grâce à différentes techniques de communication",
        longDescription: "L'objectif de ce projet est de voir comment bien faire un plan de communication. Le fonctionnement est simple, plusieurs équipes créent un studio de développement fictif Flexarion et la meilleure équipe sera celle la mieux référencée sur Google. Pour y parvenir nous avons utilisé des techniques comme le typosquatting et des outils tels que l'IA pour gérer le site web, créer du contenu sur différent réseaux sociaux afin d'avoir un maximum de visite. Entre autre en suivant le fonctionnement de l'algorithme PageRank étudié en 1ère année si une de ces pages 'perce' et qu'elle pointe vers notre site, celui-ci sera d'avantage référencé (techniquement vous contribuez au bon référencement de Flexarion en visitant mon Portfolio et l'équipe vous en remercie).",
        images: [],
        githubUrl: "https://github.com/Androtim/Flexarion",
        siteUrl: "https://flexarion.alwaysdata.net/",
        pinned: true
      }
    ]
  },
  {
    category: "Projets Personnels",
    origin: "personnel",
    projects: [
      {
        id: "project-portfolio",
        title: "Portfolio",
        languages: ["Vue.js", "CSS"],
        description: "Création d'un espace technique interactif avec design system sur mesure et esthétique de centre de contrôle",
        longDescription: "Conception et développement de ce portfolio personnel sous Vue.js (Composition API). Ajout de quelques features utiles telles que des barres de recherche, systèmes de filtrage, etc...",
        images: [],
        githubUrl: "https://github.com/DUMONTVladislav/Portfolio",
        siteUrl: "",
        pinned: true
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
const projectModalRef = ref(null)
const zoomModalRef = ref(null)

const isProjectModalOpen = computed(() => Boolean(activeProject.value))
const isZoomModalOpen = computed(() => Boolean(zoomedImageSrc.value))

useFocusTrap(projectModalRef, isProjectModalOpen, { isSuspended: isZoomModalOpen })
useFocusTrap(zoomModalRef, isZoomModalOpen)

const openModal = (project) => {
  activeProject.value = project
  currentImageIndex.value = 0
}

const onCardKeydown = (e, project) => {
  if (e.target !== e.currentTarget) return
  e.preventDefault()
  openModal(project)
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

const getProjectTitle = (project) => {
  const trans = t(`projects.items.${project.id}.title`)
  return (trans && trans !== `projects.items.${project.id}.title`) ? trans : project.title
}

const getProjectDescription = (project) => {
  const trans = t(`projects.items.${project.id}.description`)
  return (trans && trans !== `projects.items.${project.id}.description`) ? trans : project.description
}

const getProjectLongDescription = (project) => {
  const trans = t(`projects.items.${project.id}.longDescription`)
  if (trans && trans !== `projects.items.${project.id}.longDescription`) {
    return trans
  }
  return project.longDescription || project.description
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

  const query = searchQuery.value.toLowerCase()

  let list = cat.projects.filter(project => {
    const matchesLang = project.languages.some(lang => selectedLanguages.value.includes(lang))
    const title = getProjectTitle(project).toLowerCase()
    const desc = getProjectDescription(project).toLowerCase()
    const origTitle = project.title.toLowerCase()
    const origDesc = project.description.toLowerCase()

    const matchesSearch = title.includes(query) ||
                          desc.includes(query) ||
                          origTitle.includes(query) ||
                          origDesc.includes(query) ||
                          project.languages.some(l => l.toLowerCase().includes(query))
    return matchesLang && matchesSearch
  })

  list.sort((a, b) => (b.pinned ? 1 : 0) - (a.pinned ? 1 : 0))

  return list
}

const filteredUniversitaires = computed(() => filterProjects('universitaire'))
const filteredPersonnels = computed(() => filterProjects('personnel'))

const highlightedProjectId = ref(null)

const scrollToProject = (id) => {
  if (!id) return
  const cleanId = id.replace(/^#/, '')
  if (cleanId === 'projects') return

  const cat = projectCategories.find(c => c.projects.some(p => p.id === cleanId))
  if (!cat) return

  let wasClosed = false
  if (cat.origin === 'universitaire') {
    if (!isUniversitaireOpen.value) wasClosed = true
    isUniversitaireOpen.value = true
  } else if (cat.origin === 'personnel') {
    if (!isPersonnelOpen.value) wasClosed = true
    isPersonnelOpen.value = true
  }

  const project = cat.projects.find(p => p.id === cleanId)
  if (project) {
    const isLangSelected = project.languages.some(lang => selectedLanguages.value.includes(lang))
    if (!isLangSelected) {
      selectedLanguages.value = [...allLanguages]
    }
    if (searchQuery.value) {
      searchQuery.value = ''
    }
  }

  setTimeout(() => {
    nextTick(() => {
      const el = document.getElementById(cleanId)
      if (el) {
        el.scrollIntoView({ behavior: 'smooth', block: 'center' })
        highlightedProjectId.value = cleanId
        setTimeout(() => {
          if (highlightedProjectId.value === cleanId) {
            highlightedProjectId.value = null
          }
        }, 2500)
      }
    })
  }, wasClosed ? 200 : 0)
}

const onNavToProject = (e) => {
  if (e.detail?.id) {
    scrollToProject(e.detail.id)
  }
}

const onHashChange = () => {
  if (window.location.hash && window.location.hash.startsWith('#project-')) {
    scrollToProject(window.location.hash.slice(1))
  }
}

const onKeydown = (e) => {
  if (e.key === 'Escape') {
    if (zoomedImageSrc.value) {
      closeZoom()
    } else if (activeProject.value) {
      closeModal()
    }
  }
}

onMounted(() => {
  window.addEventListener('nav-to-project', onNavToProject)
  window.addEventListener('hashchange', onHashChange)
  document.addEventListener('keydown', onKeydown)
  if (window.location.hash && window.location.hash.startsWith('#project-')) {
    setTimeout(() => {
      scrollToProject(window.location.hash.slice(1))
    }, 150)
  }
})

onUnmounted(() => {
  window.removeEventListener('nav-to-project', onNavToProject)
  window.removeEventListener('hashchange', onHashChange)
  document.removeEventListener('keydown', onKeydown)
})
</script>

<template>
  <section id="projects" class="projects-section">
    <h2 v-reveal>{{ t('projects.title') }}</h2>

    <div v-reveal="{ delay: 80 }" class="projects-controls">
      <div class="search-group">
        <label for="project-search" class="control-label">{{ t('projects.searchLabel') }}</label>
        <input
          id="project-search"
          type="text"
          v-model="searchQuery"
          :placeholder="t('projects.searchPlaceholder')"
          class="search-input"
        />
      </div>

      <div class="filter-group">
        <span class="control-label">{{ t('projects.filterLabel') }}</span>
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

    <p class="sr-only" aria-live="polite">
      {{ t('projects.resultsCount', { count: filteredUniversitaires.length + filteredPersonnels.length }) }}
    </p>

    <div v-reveal="{ delay: 100 }" class="project-category-group" v-if="filteredUniversitaires.length">
      <button
        type="button"
        class="category-toggle-btn"
        :class="{ 'is-collapsed': !isUniversitaireOpen }"
        @click="isUniversitaireOpen = !isUniversitaireOpen"
        :aria-expanded="isUniversitaireOpen"
      >
        <span class="category-title-text">{{ t('projects.sectionUniversitaire') }} <span class="count-badge">({{ filteredUniversitaires.length }})</span></span>
        <span class="toggle-icon" aria-hidden="true" :class="{ rotated: !isUniversitaireOpen }">▼</span>
      </button>

      <div class="section-collapse" :class="{ 'is-collapsed': !isUniversitaireOpen }">
        <div class="section-collapse-inner">
          <TransitionGroup name="project-item" tag="div" class="projects-container">
            <article
              v-for="project in filteredUniversitaires"
              :key="project.id"
              :id="project.id"
              class="project-card-large clickable-card"
              :class="{ highlighted: highlightedProjectId === project.id }"
              tabindex="0"
              role="button"
              aria-haspopup="dialog"
              :aria-label="getProjectTitle(project)"
              @click="openModal(project)"
              @keydown.enter="onCardKeydown($event, project)"
              @keydown.space="onCardKeydown($event, project)"
            >
              <div class="pin-badge" v-if="project.pinned" role="img" :aria-label="t('projects.pinnedTitle')" :title="t('projects.pinnedTitle')">
                <span aria-hidden="true">📌</span>
              </div>

              <div v-if="project.title === 'Candy Crush'" class="project-terminal-box" @click.stop>
                <CandyCrushTerminal :allow-expand="true" @expand="openModal(project)" />
              </div>
              <div v-else class="project-screenshot-box">
                <template v-if="project.images && project.images.length">
                  <img
                    :src="project.images[0]"
                    :alt="project.title"
                    class="project-screenshot"
                  />
                  <div class="zoom-overlay" aria-hidden="true">
                    <span>{{ t('projects.zoomBadge') }}</span>
                  </div>
                </template>
                <div v-else class="no-img-box">
                  <span class="no-img-text">
                    {{ project.title === 'Portfolio' ? t('projects.noImgPortfolio') : t('projects.noImgDefault') }}
                  </span>
                </div>
              </div>

              <div class="project-content">
                <div class="project-languages-tags">
                  <span class="project-tag-lang" v-for="lang in project.languages" :key="lang">{{ lang }}</span>
                </div>
                <h3>{{ getProjectTitle(project) }}</h3>
                <p>{{ getProjectDescription(project) }}</p>

                <div class="project-actions" v-if="project.githubUrl || project.siteUrl" @click.stop>
                  <a v-if="project.githubUrl" :href="project.githubUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.viewGithub') }}</a>
                  <a v-if="project.siteUrl" :href="project.siteUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.visitSite') }}</a>
                </div>
              </div>
            </article>
          </TransitionGroup>
        </div>
      </div>
    </div>

    <div v-reveal="{ delay: 100 }" class="project-category-group" v-if="filteredPersonnels.length">
      <button
        type="button"
        class="category-toggle-btn"
        :class="{ 'is-collapsed': !isPersonnelOpen }"
        @click="isPersonnelOpen = !isPersonnelOpen"
        :aria-expanded="isPersonnelOpen"
      >
        <span class="category-title-text">{{ t('projects.sectionPersonnel') }} <span class="count-badge">({{ filteredPersonnels.length }})</span></span>
        <span class="toggle-icon" aria-hidden="true" :class="{ rotated: !isPersonnelOpen }">▼</span>
      </button>

      <div class="section-collapse" :class="{ 'is-collapsed': !isPersonnelOpen }">
        <div class="section-collapse-inner">
          <TransitionGroup name="project-item" tag="div" class="projects-container">
            <article
              v-for="project in filteredPersonnels"
              :key="project.id"
              :id="project.id"
              class="project-card-large clickable-card"
              :class="{ highlighted: highlightedProjectId === project.id }"
              tabindex="0"
              role="button"
              aria-haspopup="dialog"
              :aria-label="getProjectTitle(project)"
              @click="openModal(project)"
              @keydown.enter="onCardKeydown($event, project)"
              @keydown.space="onCardKeydown($event, project)"
            >
              <div class="pin-badge" v-if="project.pinned" role="img" :aria-label="t('projects.pinnedTitle')" :title="t('projects.pinnedTitle')">
                <span aria-hidden="true">📌</span>
              </div>

              <div class="project-screenshot-box">
                <template v-if="project.images && project.images.length">
                  <img
                    :src="project.images[0]"
                    :alt="getProjectTitle(project)"
                    class="project-screenshot"
                  />
                  <div class="zoom-overlay" aria-hidden="true">
                    <span>{{ t('projects.zoomBadge') }}</span>
                  </div>
                </template>
                <div v-else class="no-img-box">
                  <span class="no-img-text">
                    {{ project.title === 'Portfolio' ? t('projects.noImgPortfolio') : t('projects.noImgDefault') }}
                  </span>
                </div>
              </div>

              <div class="project-content">
                <div class="project-languages-tags">
                  <span class="project-tag-lang" v-for="lang in project.languages" :key="lang">{{ lang }}</span>
                </div>
                <h3>{{ getProjectTitle(project) }}</h3>
                <p>{{ getProjectDescription(project) }}</p>

                <div class="project-actions" v-if="project.githubUrl || project.siteUrl" @click.stop>
                  <a v-if="project.githubUrl" :href="project.githubUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.viewGithub') }}</a>
                  <a v-if="project.siteUrl" :href="project.siteUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.visitSite') }}</a>
                </div>
              </div>
            </article>
          </TransitionGroup>
        </div>
      </div>
    </div>

    <div v-if="!filteredUniversitaires.length && !filteredPersonnels.length" class="empty-results" role="status">
      {{ t('projects.emptyResults') }}
    </div>

    <Transition name="modal">
      <div class="modal-backdrop" v-if="activeProject" @click="closeModal">
        <div
          ref="projectModalRef"
          class="modal-content"
          role="dialog"
          aria-modal="true"
          aria-labelledby="project-modal-title"
          tabindex="-1"
          @click.stop
        >
          <button type="button" class="modal-close-btn" @click="closeModal" :aria-label="t('projects.closeModalAria')">✕</button>

          <div class="modal-header">
            <div class="project-languages-tags">
              <span class="project-tag-lang" v-for="lang in activeProject.languages" :key="lang">{{ lang }}</span>
            </div>
            <h3 id="project-modal-title">{{ getProjectTitle(activeProject) }}</h3>
          </div>

          <div class="modal-body">
            <div v-if="activeProject.title === 'Candy Crush'" class="modal-terminal-box">
              <CandyCrushTerminal />
            </div>
            <div v-else-if="activeProject.images && activeProject.images.length" class="modal-screenshot-box">
              <button type="button" class="carousel-btn prev" @click="prevImage" v-if="activeProject.images.length > 1" :aria-label="t('projects.prevImageAria')">❮</button>

              <Transition name="carousel-fade" mode="out-in">
                <img
                  :key="currentImageIndex"
                  :src="activeProject.images[currentImageIndex]"
                  :alt="getProjectTitle(activeProject)"
                  class="modal-screenshot zoomable-img"
                  tabindex="0"
                  role="button"
                  @click="openZoom(activeProject.images[currentImageIndex])"
                  @keydown.enter.prevent="openZoom(activeProject.images[currentImageIndex])"
                  @keydown.space.prevent="openZoom(activeProject.images[currentImageIndex])"
                  :title="t('projects.zoomTitle')"
                />
              </Transition>

              <button type="button" class="carousel-btn next" @click="nextImage" v-if="activeProject.images.length > 1" :aria-label="t('projects.nextImageAria')">❯</button>

              <div class="carousel-counter" v-if="activeProject.images.length > 1" aria-live="polite" :aria-label="t('projects.carouselCounterAria', { current: currentImageIndex + 1, total: activeProject.images.length })">
                {{ currentImageIndex + 1 }} / {{ activeProject.images.length }}
              </div>
            </div>

            <div class="modal-screenshot-box" v-else>
              <span class="no-img-text">
                {{ activeProject.title === 'Portfolio' ? t('projects.noImgPortfolio') : t('projects.noImgDefault') }}
              </span>
            </div>

            <div class="modal-details">
              <h4>{{ t('projects.detailedDescription') }}</h4>
              <p>{{ getProjectLongDescription(activeProject) }}</p>
            </div>
          </div>

          <div class="modal-footer" v-if="activeProject.githubUrl || activeProject.siteUrl">
            <a v-if="activeProject.githubUrl" :href="activeProject.githubUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.viewGithubRepo') }}</a>
            <a v-if="activeProject.siteUrl" :href="activeProject.siteUrl" target="_blank" rel="noopener noreferrer" class="btn-outline">{{ t('projects.visitSite') }}</a>
          </div>
        </div>
      </div>
    </Transition>

    <Transition name="zoom-modal">
      <div class="zoom-lightbox-backdrop" v-if="zoomedImageSrc" @click="closeZoom">
        <div
          ref="zoomModalRef"
          class="zoom-lightbox-content"
          role="dialog"
          aria-modal="true"
          aria-labelledby="zoom-modal-title"
          tabindex="-1"
          @click.stop
        >
          <h3 id="zoom-modal-title" class="sr-only">{{ t('projects.zoomAlt') }}</h3>
          <button type="button" class="modal-close-btn" @click="closeZoom" :aria-label="t('projects.closeZoomAria')">✕</button>
          <img :src="zoomedImageSrc" :alt="t('projects.zoomAlt')" class="zoomed-full-img" />
        </div>
      </div>
    </Transition>
  </section>
</template>

<style scoped>
.projects-section {
  padding: 4rem 2rem;
  max-width: 1200px;
  margin: 0 auto;
  scroll-margin-top: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 1rem);
  box-sizing: border-box;
}

.projects-section > h2 {
  font-family: var(--font-title);
  font-size: 2rem;
  color: var(--accent-text);
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
  min-width: 0;
  background: color-mix(in srgb, var(--text-color) 5%, transparent);
  border: 1px solid color-mix(in srgb, var(--text-color) 20%, transparent);
  color: var(--text-color);
  padding: 0.45rem 0.8rem;
  border-radius: 6px;
  font-size: 0.85rem;
  outline: none;
  transition: all 0.3s ease;
}

.search-input:focus,
.search-input:focus-visible {
  border-color: var(--accent-text);
  box-shadow: 0 0 8px var(--accent-color);
}

.filter-group {
  display: flex;
  flex-wrap: wrap;
  gap: 0.85rem 1rem;
  align-items: center;
}

.control-label {
  font-family: var(--font-title);
  font-size: 0.8rem;
  color: var(--accent-text);
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
  margin-bottom: 0;
  box-shadow: 0 0 8px rgba(0, 0, 0, 0.1);
}

.category-toggle-btn:hover,
.category-toggle-btn:focus-visible {
  background: color-mix(in srgb, var(--accent-color) 10%, var(--nav-bg));
  box-shadow: 0 0 12px var(--accent-color);
}

.category-toggle-btn:active {
  transform: scale(0.995);
}

.section-collapse {
  display: grid;
  grid-template-rows: 1fr;
  transition: grid-template-rows 0.35s cubic-bezier(0.4, 0, 0.2, 1), opacity 0.3s ease, margin-top 0.35s ease;
  opacity: 1;
  margin-top: 1.5rem;
}

.section-collapse.is-collapsed {
  grid-template-rows: 0fr;
  opacity: 0;
  margin-top: 0;
  visibility: hidden;
  transition: grid-template-rows 0.35s cubic-bezier(0.4, 0, 0.2, 1), opacity 0.25s ease, margin-top 0.35s ease, visibility 0.35s step-end;
}

.section-collapse-inner {
  overflow: hidden;
  min-height: 0;
  padding: 6px 4px;
  margin: -6px -4px;
}

.category-title-text {
  font-family: var(--font-title);
  font-size: 1.2rem;
  color: var(--text-color);
  display: flex;
  align-items: center;
  gap: 0.5rem;
  text-align: left;
}

.count-badge {
  font-size: 0.85rem;
  opacity: 0.7;
  font-family: sans-serif;
}

.toggle-icon {
  font-size: 0.9rem;
  color: var(--accent-text);
  transition: transform 0.3s ease;
  flex-shrink: 0;
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
  scroll-margin-top: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 1.5rem);
  position: relative;
}

.project-card-large:hover,
.project-card-large:focus-visible {
  box-shadow: 0 0 20px var(--accent-color);
  transform: translateY(-3px);
}

.pin-badge {
  position: absolute;
  top: 1rem;
  right: 1.2rem;
  font-size: 1rem;
  background: color-mix(in srgb, var(--accent-color) 20%, transparent);
  border: 1px solid var(--accent-color);
  border-radius: 50%;
  width: 30px;
  height: 30px;
  display: flex;
  align-items: center;
  justify-content: center;
  box-shadow: 0 0 8px var(--accent-color);
  z-index: 5;
}

.project-card-large:target,
.project-card-large.highlighted {
  border-color: var(--accent-text);
  box-shadow: 0 0 25px var(--accent-color), inset 0 0 10px color-mix(in srgb, var(--accent-color) 25%, transparent);
  animation: project-pulse 1.8s ease-in-out;
}

@keyframes project-pulse {
  0% {
    transform: scale(1);
    box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);
  }
  30% {
    transform: scale(1.015);
    box-shadow: 0 0 35px var(--accent-color), inset 0 0 15px color-mix(in srgb, var(--accent-color) 40%, transparent);
  }
  70% {
    transform: scale(1.01);
    box-shadow: 0 0 30px var(--accent-color);
  }
  100% {
    transform: scale(1);
    box-shadow: 0 0 20px var(--accent-color);
  }
}

.project-terminal-box {
  flex: 1.5;
  height: 310px;
  min-width: 280px;
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.4);
}

.modal-terminal-box {
  width: 100%;
  height: 420px;
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  box-shadow: 0 0 20px rgba(0, 0, 0, 0.5);
}

.project-screenshot-box {
  flex: 1.5;
  min-width: 0;
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
  color: var(--accent-text);
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
  min-width: 0;
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
  color: var(--accent-text);
  background: color-mix(in srgb, var(--accent-color) 15%, transparent);
  border: 1px solid var(--accent-color);
  padding: 0.1rem 0.5rem;
  border-radius: 4px;
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.project-content h3 {
  font-family: var(--font-title);
  font-size: 1.4rem;
  color: var(--text-color);
  margin: 0 0 0.8rem 0;
  overflow-wrap: anywhere;
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
  gap: 0.8rem;
  flex-wrap: wrap;
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
  box-sizing: border-box;
}

.btn-outline:hover {
  background-color: var(--accent-text);
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
  box-sizing: border-box;
}

.modal-content {
  background: var(--nav-bg);
  border: 2px solid var(--accent-color);
  border-radius: 14px;
  width: 100%;
  max-width: 900px;
  max-height: 90vh;
  overflow-y: auto;
  overscroll-behavior: contain;
  -webkit-overflow-scrolling: touch;
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
  color: var(--accent-text);
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
  transform: rotate(90deg) scale(1.1);
}

.modal-close-btn:active {
  transform: rotate(90deg) scale(0.95);
}

.modal-header h3 {
  font-family: var(--font-title);
  font-size: 1.8rem;
  color: var(--text-color);
  margin-top: 0.5rem;
  text-align: left;
  overflow-wrap: anywhere;
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
  background: rgba(0, 0, 0, 0.72);
  border: 1px solid var(--accent-color);
  color: #f8fafc;
  width: 40px;
  height: 40px;
  border-radius: 50%;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1rem;
  z-index: 10;
  touch-action: manipulation;
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
  background: rgba(0, 0, 0, 0.78);
  border: 1px solid var(--accent-color);
  color: #f8fafc;
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
  color: var(--accent-text);
  opacity: 0.9;
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
  color: var(--accent-text);
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
  overflow-wrap: anywhere;
}

.modal-footer {
  display: flex;
  gap: 1rem;
  justify-content: flex-start;
  margin-top: 0.5rem;
  flex-wrap: wrap;
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
  overscroll-behavior: contain;
  box-sizing: border-box;
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

.modal-enter-active,
.modal-leave-active {
  transition: opacity 0.3s cubic-bezier(0.16, 1, 0.3, 1);
}

.modal-enter-from,
.modal-leave-to {
  opacity: 0;
}

.modal-enter-active .modal-content,
.modal-leave-active .modal-content {
  transition: transform 0.35s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.3s ease;
}

.modal-enter-from .modal-content,
.modal-leave-to .modal-content {
  opacity: 0;
  transform: scale(0.92) translateY(20px);
}

.zoom-modal-enter-active,
.zoom-modal-leave-active {
  transition: opacity 0.3s cubic-bezier(0.16, 1, 0.3, 1);
}

.zoom-modal-enter-from,
.zoom-modal-leave-to {
  opacity: 0;
}

.zoom-modal-enter-active .zoom-lightbox-content,
.zoom-modal-leave-active .zoom-lightbox-content {
  transition: transform 0.3s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.3s ease;
}

.zoom-modal-enter-from .zoom-lightbox-content,
.zoom-modal-leave-to .zoom-lightbox-content {
  opacity: 0;
  transform: scale(0.9);
}

.carousel-fade-enter-active,
.carousel-fade-leave-active {
  transition: opacity 0.22s ease, transform 0.22s ease;
}

.carousel-fade-enter-from {
  opacity: 0;
  transform: scale(0.96);
}

.carousel-fade-leave-to {
  opacity: 0;
  transform: scale(1.04);
}

.project-item-move,
.project-item-enter-active,
.project-item-leave-active {
  transition: transform 0.35s cubic-bezier(0.4, 0, 0.2, 1), opacity 0.3s ease;
}

.project-item-enter-from,
.project-item-leave-to {
  opacity: 0;
  transform: scale(0.95);
}

@media (max-width: 1024px) and (min-width: 869px) {
  .projects-section {
    padding: 3.5rem 1.75rem;
  }

  .project-card-large {
    padding: 1.5rem;
    gap: 1.5rem;
  }

  .project-terminal-box {
    min-width: 240px;
    height: 290px;
  }
}

@media (max-width: 868px) {
  .projects-section {
    padding: 3rem 1.25rem;
  }

  .projects-section > h2 {
    font-size: clamp(1.4rem, 5vw, 1.8rem);
    margin-bottom: 1.5rem;
  }

  .projects-controls {
    padding: 1rem;
    gap: 0.85rem;
    margin-bottom: 2rem;
  }

  .search-group {
    flex-direction: column;
    align-items: stretch;
    gap: 0.35rem;
  }

  .category-toggle-btn {
    padding: 0.85rem 1rem;
  }

  .category-title-text {
    font-size: 1.05rem;
  }

  .project-card-large {
    flex-direction: column;
    align-items: stretch;
    padding: 1.5rem;
    gap: 1.5rem;
  }

  .project-screenshot-box {
    width: 100%;
    height: 230px;
  }

  .project-terminal-box {
    width: 100%;
    height: 300px;
    min-width: 0;
  }

  .modal-backdrop {
    padding: 0.75rem;
  }

  .modal-content {
    padding: 1.75rem 1.25rem;
    max-height: 94vh;
    gap: 1rem;
  }

  .modal-header h3 {
    font-size: 1.35rem;
    padding-right: 2rem;
  }

  .modal-screenshot-box {
    height: 240px;
  }

  .modal-terminal-box {
    height: 350px;
  }
}

@media (max-width: 540px) {
  .projects-section {
    padding: 2.5rem 1rem;
  }

  .project-card-large {
    padding: 1.15rem;
    gap: 1.15rem;
    border-radius: 10px;
  }

  .project-screenshot-box {
    height: 180px;
  }

  .project-terminal-box {
    height: 260px;
  }

  .project-content h3 {
    font-size: 1.15rem;
  }

  .project-content p {
    font-size: 0.85rem;
  }

  .project-actions {
    flex-direction: column;
    width: 100%;
  }

  .project-actions .btn-outline {
    width: 100%;
    text-align: center;
  }

  .modal-backdrop {
    padding: 0.35rem;
  }

  .modal-content {
    padding: 1.25rem 0.85rem;
  }

  .modal-close-btn {
    top: 0.75rem;
    right: 0.75rem;
    width: 30px;
    height: 30px;
    font-size: 0.85rem;
  }

  .modal-header h3 {
    font-size: 1.15rem;
  }

  .modal-screenshot-box {
    height: 180px;
  }

  .modal-terminal-box {
    height: 290px;
  }

  .carousel-btn {
    width: 32px;
    height: 32px;
    font-size: 0.8rem;
  }

  .carousel-btn.prev {
    left: 0.5rem;
  }

  .carousel-btn.next {
    right: 0.5rem;
  }

  .modal-footer {
    flex-direction: column;
    width: 100%;
  }

  .modal-footer .btn-outline {
    width: 100%;
    text-align: center;
  }

  .filter-group {
    gap: 0.6rem;
  }

  .checkbox-label {
    font-size: 0.8rem;
  }
}

@media (prefers-reduced-motion: reduce) {
  .section-collapse,
  .section-collapse.is-collapsed,
  .toggle-icon,
  .project-card-large,
  .category-toggle-btn,
  .modal-close-btn,
  .carousel-btn,
  .project-item-enter-active,
  .project-item-leave-active,
  .project-item-move,
  .modal-enter-active,
  .modal-leave-active,
  .modal-enter-active .modal-content,
  .modal-leave-active .modal-content,
  .zoom-modal-enter-active,
  .zoom-modal-leave-active,
  .zoom-modal-enter-active .zoom-lightbox-content,
  .zoom-modal-leave-active .zoom-lightbox-content,
  .carousel-fade-enter-active,
  .carousel-fade-leave-active {
    transition: none !important;
  }

  .project-card-large:target,
  .project-card-large.highlighted {
    animation: none !important;
  }

  .project-card-large:hover,
  .project-card-large:focus-visible,
  .modal-close-btn:hover {
    transform: none !important;
  }
}
</style>