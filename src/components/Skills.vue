<script setup>
import { ref, computed } from 'vue'
import { useI18n } from '@/composables/useI18n.js'

const { t } = useI18n()

const skills = [
  { 
    name: "Linux terminals", 
    category: "Infrastructure & Réseaux", 
    origin: "cursus",
    description: "Maîtrise des commandes, administration et gestion des scripts shell.", 
    icon: "🐧", 
    projects: ["Tous les projets"],
    rating: 4 
  },
  { 
    name: "Git", 
    category: "Outils & Versioning", 
    origin: "cursus",
    description: "Gestion de versions, branches, fusion et travail collaboratif.", 
    icon: "🌿", 
    projects: ["Tous les projets"],
    rating: 4 
  },
  { 
    name: "Python", 
    category: "Développement & Programmation", 
    origin: "cursus",
    description: "Développement de scripts, automatisation, traitement de données (Faker) et PageRank.", 
    icon: "🐍", 
    projects: ["PageRank", "Les Tenracs"],
    rating: 3.5 
  },
  { 
    name: "Java & JavaFX", 
    category: "Développement & Programmation", 
    origin: "cursus",
    description: "Programmation orientée objet, conception d'interfaces graphiques et robustesse.", 
    icon: "☕", 
    projects: ["VigieChiro"],
    rating: 3
  },
  { 
    name: "C++", 
    category: "Développement & Programmation", 
    origin: "cursus",
    description: "Gestion de la mémoire, performance, algorithmique avancée et tests Oracle.", 
    icon: "⚙️", 
    projects: ["Systèmes de vote", "Candy Crush"],
    rating: 3.5
  },
  { 
    name: "MIPS", 
    category: "Développement & Programmation", 
    origin: "cursus",
    description: "Architecture des ordinateurs, programmation assembleur et bas niveau.", 
    icon: "💻", 
    projects: [],
    rating: 2.5
  },
  { 
    name: "PHP", 
    category: "Développement & Programmation", 
    origin: "cursus",
    description: "Développement backend, scripts serveur et interaction dynamique avec les bases de données.", 
    icon: "🐘", 
    projects: ["DataLab"],
    rating: 2.5
  },
  { 
    name: "PostgreSQL & SQL", 
    category: "Bases de Données", 
    origin: "cursus",
    description: "Conception de schémas relationnels, modélisation, requêtes complexes et optimisation.", 
    icon: "🐘", 
    projects: ["Les Tenracs", "DataLab"],
    rating: 4 
  },
  { 
    name: "DNS servers", 
    category: "Infrastructure & Réseaux", 
    origin: "cursus",
    description: "Configuration, résolution de noms et architecture des serveurs DNS.", 
    icon: "🌐", 
    projects: ["Serveurs Apache/DNS/MX"],
    rating: 3.5
  },
  { 
    name: "Apache servers", 
    category: "Infrastructure & Réseaux", 
    origin: "cursus",
    description: "Déploiement, configuration de virtual hosts et sécurisation web.", 
    icon: "🪶", 
    projects: ["Serveurs Apache/DNS/MX"],
    rating: 2.5
  },
  { 
    name: "MX servers", 
    category: "Infrastructure & Réseaux", 
    origin: "cursus",
    description: "Gestion de serveurs de messagerie et protocoles de routage d'e-mails.", 
    icon: "✉️", 
    projects: ["Serveurs Apache/DNS/MX"],
    rating: 2.5
  },
  { 
    name: "HTML", 
    category: "Web & Frontend", 
    origin: "cursus",
    description: "Sémantique, structure de documents et accessibilité de base.", 
    icon: "📄", 
    projects: ["Rock O' Rama", "DataLab"],
    rating: 3.5
  },
  { 
    name: "CSS", 
    category: "Web & Frontend", 
    origin: "cursus",
    description: "Mise en page, variables, animations et design responsive.", 
    icon: "🎨", 
    projects: ["Rock O' Rama", "DataLab"],
    rating: 3 
  },
  { 
    name: "JavaScript", 
    category: "Développement & Programmation", 
    origin: "autodidacte",
    description: "Dynamisme, manipulation du DOM et programmation asynchrone.", 
    icon: "⚡", 
    projects: ["Portfolio", "DataLab"],
    rating: 2.5
  },
  { 
    name: "Vue.js", 
    category: "Web & Frontend", 
    origin: "autodidacte",
    description: "Composants réactifs, composition API et architecture SPA.", 
    icon: "🟢", 
    projects: ["Portfolio"],
    rating: 3.5
  },
  { 
    name: "Node.js", 
    category: "Développement & Programmation", 
    origin: "autodidacte",
    description: "Environnement d'exécution JavaScript coté serveur et API.", 
    icon: "🟢", 
    projects: ["Portfolio"],
    rating: 3 
  }
]

const allCategories = [...new Set(skills.map(s => s.category))]
const selectedCategories = ref([...allCategories])
const sortBy = ref('default')
const searchQuery = ref('')

const isCursusOpen = ref(true)
const isAutodidacteOpen = ref(true)

const toggleCategory = (cat) => {
  if (selectedCategories.value.includes(cat)) {
    selectedCategories.value = selectedCategories.value.filter(c => c !== cat)
  } else {
    selectedCategories.value.push(cat)
  }
}

const filterAndSort = (origin) => {
  let list = skills.filter(s => {
    const matchesOrigin = s.origin === origin
    const matchesCategory = selectedCategories.value.includes(s.category)
    const matchesSearch = s.name.toLowerCase().includes(searchQuery.value.toLowerCase()) || 
                          s.description.toLowerCase().includes(searchQuery.value.toLowerCase())
    return matchesOrigin && matchesCategory && matchesSearch
  })

  if (sortBy.value === 'ratingDesc') {
    list.sort((a, b) => b.rating - a.rating)
  } else if (sortBy.value === 'ratingAsc') {
    list.sort((a, b) => a.rating - b.rating)
  } else if (sortBy.value === 'nameAsc') {
    list.sort((a, b) => a.name.localeCompare(b.name))
  }
  return list
}

const cursusSkills = computed(() => filterAndSort('cursus'))
const autodidacteSkills = computed(() => filterAndSort('autodidacte'))

const projectLinks = {
  "Systèmes de vote": "#project-systemes-de-vote",
  "Candy Crush": "#project-candy-crush",
  "Rock O' Rama": "#project-rock-o-rama",
  "Les Tenracs": "#project-les-tenracs",
  "PageRank": "#project-pagerank",
  "Serveurs Apache/DNS/MX": "#project-serveurs-apache-dns-mx",
  "VigieChiro": "#project-vigiechiro",
  "DataLab": "#project-datalab",
  "Flexarion": "#project-flexarion",
  "Portfolio": "#project-portfolio",
  "Tous les projets": "#projects"
}

const getProjectLink = (projectName) => {
  return projectLinks[projectName] || '#projects'
}

const getSkillCategory = (cat) => {
  return t(`skills.categories.${cat}`) || cat
}

const getSkillDescription = (skill) => {
  return t(`skills.descriptions.${skill.name}`) || skill.description
}

const getProjectTagTitle = (proj) => {
  if (proj === 'Tous les projets') {
    return t('skills.allProjectsTitle')
  }
  return t('skills.projectTagTitle', { name: proj })
}

const getProjectDisplayName = (proj) => {
  if (proj === 'Tous les projets') {
    return t('skills.allProjects')
  }
  const translated = t(`skills.projectNames.${proj}`)
  return (translated && translated !== `skills.projectNames.${proj}`) ? translated : proj
}

const onProjectClick = (projectName) => {
  const link = getProjectLink(projectName)
  if (link.startsWith('#project-')) {
    const id = link.slice(1)
    window.dispatchEvent(new CustomEvent('nav-to-project', { detail: { id } }))
  }
}
</script>

<template>
  <section id="skills" class="skills-section">
    <h2 v-reveal>{{ t('skills.title') }}</h2>

    <div v-reveal="{ delay: 80 }" class="skills-controls">
      <div class="search-group">
        <label for="search-input" class="control-label">{{ t('skills.searchLabel') }}</label>
        <input 
          id="search-input"
          type="text" 
          v-model="searchQuery" 
          :placeholder="t('skills.searchPlaceholder')" 
          class="search-input"
        />
      </div>

      <div class="filter-group">
        <span class="control-label">{{ t('skills.categoriesLabel') }}</span>
        <label v-for="cat in allCategories" :key="cat" class="checkbox-label">
          <input 
            type="checkbox" 
            :checked="selectedCategories.includes(cat)" 
            @change="toggleCategory(cat)"
          />
          {{ getSkillCategory(cat) }}
        </label>
      </div>

      <div class="sort-group">
        <label for="sort-select" class="control-label">{{ t('skills.sortLabel') }}</label>
        <select id="sort-select" v-model="sortBy" class="sort-select">
          <option value="default">{{ t('skills.sortDefault') }}</option>
          <option value="ratingDesc">{{ t('skills.sortRatingDesc') }}</option>
          <option value="ratingAsc">{{ t('skills.sortRatingAsc') }}</option>
          <option value="nameAsc">{{ t('skills.sortNameAsc') }}</option>
        </select>
      </div>
    </div>

    <p class="sr-only" aria-live="polite">
      {{ t('skills.resultsCount', { count: cursusSkills.length + autodidacteSkills.length }) }}
    </p>

    <div v-reveal="{ delay: 100 }" class="skill-section-group" v-if="cursusSkills.length">
      <button 
        type="button"
        class="category-toggle-btn" 
        :class="{ 'is-collapsed': !isCursusOpen }" 
        @click="isCursusOpen = !isCursusOpen"
        :aria-expanded="isCursusOpen"
      >
        <span class="category-title-text">{{ t('skills.sectionCursus') }} <span class="count-badge">({{ cursusSkills.length }})</span></span>
        <span class="toggle-icon" aria-hidden="true" :class="{ 'rotated': !isCursusOpen }">▼</span>
      </button>

      <div class="section-collapse" :class="{ 'is-collapsed': !isCursusOpen }">
        <div class="section-collapse-inner">
          <TransitionGroup name="grid-item" tag="div" class="skills-grid">
            <div 
              v-for="(skill, index) in cursusSkills" 
              :key="skill.name" 
              class="skill-card"
              :class="{ 'reverse': index % 2 !== 1 }"
            >
              <div class="skill-icon-box" aria-hidden="true">
                <span class="skill-emoji">{{ skill.icon }}</span>
              </div>

              <div class="skill-text-box">
                <span class="skill-category">{{ getSkillCategory(skill.category) }}</span>
                <h3>{{ skill.name }}</h3>
                <p>{{ getSkillDescription(skill) }}</p>
                
                <div class="skill-projects" v-if="skill.projects && skill.projects.length">
                  <span class="projects-label">{{ t('skills.projectsLabel') }}</span>
                  <a 
                    v-for="proj in skill.projects" 
                    :key="proj"
                    :href="getProjectLink(proj)" 
                    @click="onProjectClick(proj)"
                    class="project-tag"
                    :title="getProjectTagTitle(proj)"
                  >{{ getProjectDisplayName(proj) }}</a>
                </div>

                <div class="skill-rating-container">
                  <span class="rating-label">{{ t('skills.ratingLabel') }}</span>
                  <div
                    class="skill-rating"
                    role="img"
                    :aria-label="t('skills.ratingAria', { rating: skill.rating })"
                  >
                    <span 
                      v-for="star in 5" 
                      :key="star" 
                      aria-hidden="true"
                      class="star" 
                      :class="{ 
                        'filled': star <= skill.rating, 
                        'half': star === Math.ceil(skill.rating) && skill.rating % 1 !== 0 
                      }"
                    >★</span>
                  </div>
                </div>
              </div>
            </div>
          </TransitionGroup>
        </div>
      </div>
    </div>

    <div v-reveal="{ delay: 100 }" class="skill-section-group" v-if="autodidacteSkills.length">
      <button 
        type="button"
        class="category-toggle-btn" 
        :class="{ 'is-collapsed': !isAutodidacteOpen }" 
        @click="isAutodidacteOpen = !isAutodidacteOpen"
        :aria-expanded="isAutodidacteOpen"
      >
        <span class="category-title-text">{{ t('skills.sectionAutodidacte') }} <span class="count-badge">({{ autodidacteSkills.length }})</span></span>
        <span class="toggle-icon" aria-hidden="true" :class="{ 'rotated': !isAutodidacteOpen }">▼</span>
      </button>

      <div class="section-collapse" :class="{ 'is-collapsed': !isAutodidacteOpen }">
        <div class="section-collapse-inner">
          <TransitionGroup name="grid-item" tag="div" class="skills-grid">
            <div 
              v-for="(skill, index) in autodidacteSkills" 
              :key="skill.name" 
              class="skill-card"
              :class="{ 'reverse': index % 2 !== 1 }"
            >
              <div class="skill-icon-box" aria-hidden="true">
                <span class="skill-emoji">{{ skill.icon }}</span>
              </div>

              <div class="skill-text-box">
                <span class="skill-category">{{ getSkillCategory(skill.category) }}</span>
                <h3>{{ skill.name }}</h3>
                <p>{{ getSkillDescription(skill) }}</p>
                
                <div class="skill-projects" v-if="skill.projects && skill.projects.length">
                  <span class="projects-label">{{ t('skills.projectsLabel') }}</span>
                  <a 
                    v-for="proj in skill.projects" 
                    :key="proj"
                    :href="getProjectLink(proj)" 
                    @click="onProjectClick(proj)"
                    class="project-tag"
                    :title="getProjectTagTitle(proj)"
                  >{{ getProjectDisplayName(proj) }}</a>
                </div>

                <div class="skill-rating-container">
                  <span class="rating-label">{{ t('skills.ratingLabel') }}</span>
                  <div
                    class="skill-rating"
                    role="img"
                    :aria-label="t('skills.ratingAria', { rating: skill.rating })"
                  >
                    <span 
                      v-for="star in 5" 
                      :key="star" 
                      aria-hidden="true"
                      class="star" 
                      :class="{ 
                        'filled': star <= skill.rating, 
                        'half': star === Math.ceil(skill.rating) && skill.rating % 1 !== 0 
                      }"
                    >★</span>
                  </div>
                </div>
              </div>
            </div>
          </TransitionGroup>
        </div>
      </div>
    </div>

    <div v-if="!cursusSkills.length && !autodidacteSkills.length" class="empty-results" role="status">
      {{ t('skills.emptyResults') }}
    </div>
  </section>
</template>

<style scoped>
.skills-section {
  padding: 4rem 2rem;
  max-width: 1200px;
  margin: 0 auto;
  scroll-margin-top: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 1rem);
  box-sizing: border-box;
}

.skills-section h2 {
  font-family: var(--font-title);
  font-size: 2rem;
  color: var(--accent-text);
  margin-bottom: 2rem;
  text-align: left;
}

.skills-controls {
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
  border-color: var(--accent-color);
  box-shadow: 0 0 8px var(--accent-color);
}

.filter-group {
  display: flex;
  flex-wrap: wrap;
  gap: 0.85rem 1rem;
  align-items: center;
}

.sort-group {
  display: flex;
  align-items: center;
  gap: 0.8rem;
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

.sort-select {
  background: color-mix(in srgb, var(--text-color) 5%, transparent);
  border: 1px solid color-mix(in srgb, var(--text-color) 20%, transparent);
  color: var(--text-color);
  padding: 0.35rem 0.65rem;
  border-radius: 6px;
  font-size: 0.85rem;
  outline: none;
  cursor: pointer;
}

.sort-select:focus-visible {
  border-color: var(--accent-color);
  outline: 2px solid var(--accent-color);
  outline-offset: 2px;
  box-shadow: 0 0 8px var(--accent-color);
}

.skill-section-group {
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

.skills-grid {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 2rem;
  align-items: stretch;
}

.skill-card {
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-radius: 10px;
  padding: 1.5rem;
  display: flex;
  align-items: center;
  gap: 1.5rem;
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.2);
  transition: all 0.3s ease;
  height: 100%;
  min-width: 0;
  box-sizing: border-box;
}

.skill-card:hover {
  box-shadow: 0 0 15px var(--accent-color);
  transform: translateY(-3px);
}

.skill-card.reverse {
  flex-direction: row-reverse;
}

.skill-card.reverse .skill-text-box,
.skill-card:not(.reverse) .skill-text-box {
  text-align: left;
}

.skill-icon-box {
  min-width: 70px;
  height: 70px;
  background: rgba(0, 0, 0, 0.3);
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 2rem;
  flex-shrink: 0;
  box-shadow: inset 0 0 8px var(--accent-color);
}

.skill-emoji {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 100%;
  height: 100%;
}

.skill-text-box {
  display: flex;
  flex-direction: column;
  min-width: 0;
  flex: 1;
}

.skill-category {
  font-family: var(--font-title);
  font-size: 0.7rem;
  color: var(--accent-text);
  opacity: 0.9;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.skill-text-box h3 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  color: var(--text-color);
  margin: 0.2rem 0 0.3rem 0;
  overflow-wrap: anywhere;
}

.skill-text-box p {
  font-size: 0.8rem;
  opacity: 0.8;
  margin: 0 0 0.5rem 0;
  line-height: 1.35;
}

.skill-projects {
  display: flex;
  flex-wrap: wrap;
  gap: 0.3rem;
  align-items: center;
  margin-bottom: 0.5rem;
}

.projects-label {
  font-size: 0.75rem;
  font-family: var(--font-title);
  opacity: 0.8;
  color: var(--text-color);
}

.project-tag {
  font-size: 0.7rem;
  background: color-mix(in srgb, var(--text-color) 10%, transparent);
  border: 1px solid color-mix(in srgb, var(--text-color) 20%, transparent);
  color: var(--text-color);
  padding: 0.1rem 0.4rem;
  border-radius: 4px;
  opacity: 0.9;
  text-decoration: none;
  transition: all 0.2s ease;
}

.project-tag:hover {
  background: var(--accent-color);
  color: #ffffff;
  border-color: var(--accent-color);
  box-shadow: 0 0 8px var(--accent-color);
}

.skill-rating-container {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  margin-top: auto;
}

.rating-label {
  font-size: 0.75rem;
  font-family: var(--font-title);
  opacity: 0.8;
  color: var(--text-color);
}

.skill-rating {
  display: flex;
  gap: 0.2rem;
  font-size: 0.85rem;
}

.star {
  color: color-mix(in srgb, var(--text-color) 25%, transparent);
}

.star.filled {
  color: var(--accent-text);
  text-shadow: 0 0 5px var(--accent-color);
}

.star.half {
  background: linear-gradient(90deg, var(--accent-text) 50%, color-mix(in srgb, var(--text-color) 25%, transparent) 50%);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  filter: drop-shadow(0 0 3px var(--accent-color));
}

.grid-item-move,
.grid-item-enter-active,
.grid-item-leave-active {
  transition: transform 0.35s cubic-bezier(0.4, 0, 0.2, 1), opacity 0.3s ease;
}

.grid-item-enter-from,
.grid-item-leave-to {
  opacity: 0;
  transform: scale(0.92);
}

@media (max-width: 1024px) and (min-width: 901px) {
  .skills-section {
    padding: 3.5rem 1.75rem;
  }

  .skills-grid {
    gap: 1.5rem;
  }
}

@media (max-width: 900px) {
  .skills-grid {
    grid-template-columns: 1fr;
    gap: 1.25rem;
  }
}

@media (max-width: 768px) {
  .skills-section {
    padding: 3rem 1.25rem;
  }

  .skills-section h2 {
    font-size: clamp(1.4rem, 5vw, 1.8rem);
    margin-bottom: 1.5rem;
  }

  .skills-controls {
    padding: 1rem;
    gap: 0.85rem;
    margin-bottom: 2rem;
  }

  .search-group {
    flex-direction: column;
    align-items: stretch;
    gap: 0.35rem;
  }

  .sort-group {
    flex-wrap: wrap;
    gap: 0.5rem;
  }

  .category-toggle-btn {
    padding: 0.85rem 1rem;
  }

  .category-title-text {
    font-size: 1.05rem;
  }
}

@media (max-width: 540px) {
  .skills-section {
    padding: 2.5rem 1rem;
  }

  .skill-card,
  .skill-card.reverse {
    flex-direction: row;
    padding: 1rem;
    gap: 0.85rem;
  }

  .skill-icon-box {
    min-width: 54px;
    height: 54px;
    font-size: 1.6rem;
  }

  .skill-text-box h3 {
    font-size: 1.05rem;
  }

  .skill-text-box p {
    font-size: 0.82rem;
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
  .skill-card,
  .category-toggle-btn,
  .grid-item-enter-active,
  .grid-item-leave-active,
  .grid-item-move {
    transition: none !important;
  }

  .skill-card:hover {
    transform: none !important;
  }
}
</style>