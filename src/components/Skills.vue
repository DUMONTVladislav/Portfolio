<script setup>
import { ref, computed } from 'vue'

const skills = [
  // --- CURSUS SCOLAIRE ---
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

  // --- AUTODIDACTE ---
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
</script>

<template>
  <section id="skills" class="skills-section">
    <h2>Mes compétences</h2>

    <div class="skills-controls">
      <!-- Barre de recherche -->
      <div class="search-group">
        <label for="search-input" class="control-label">Rechercher :</label>
        <input 
          id="search-input"
          type="text" 
          v-model="searchQuery" 
          placeholder="Ex: Python, Docker, Linux..." 
          class="search-input"
        />
      </div>

      <div class="filter-group">
        <span class="control-label">Catégories :</span>
        <label v-for="cat in allCategories" :key="cat" class="checkbox-label">
          <input 
            type="checkbox" 
            :checked="selectedCategories.includes(cat)" 
            @change="toggleCategory(cat)"
          />
          {{ cat }}
        </label>
      </div>

      <div class="sort-group">
        <label for="sort-select" class="control-label">Trier par :</label>
        <select id="sort-select" v-model="sortBy" class="sort-select">
          <option value="default">Par défaut</option>
          <option value="ratingDesc">Aisance (décroissante)</option>
          <option value="ratingAsc">Aisance (croissante)</option>
          <option value="nameAsc">Nom (A-Z)</option>
        </select>
      </div>
    </div>

    <!-- Section Cursus Scolaire -->
    <div class="skill-section-group" v-if="cursusSkills.length">
      <button class="category-toggle-btn" @click="isCursusOpen = !isCursusOpen">
        <span class="category-title-text">Cursus Scolaire <span class="count-badge">({{ cursusSkills.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isCursusOpen }">▼</span>
      </button>

      <div class="skills-grid" v-show="isCursusOpen">
        <div 
          v-for="(skill, index) in cursusSkills" 
          :key="skill.name" 
          class="skill-card"
          :class="{ 'reverse': index % 2 !== 1 }"
        >
          <div class="skill-icon-box">
            <span class="skill-emoji">{{ skill.icon }}</span>
          </div>

          <div class="skill-text-box">
            <span class="skill-category">{{ skill.category }}</span>
            <h3>{{ skill.name }}</h3>
            <p>{{ skill.description }}</p>
            
            <div class="skill-projects" v-if="skill.projects && skill.projects.length">
              <span class="projects-label">Projets :</span>
              <a href="#projects" class="project-tag" v-for="proj in skill.projects" :key="proj">{{ proj }}</a>
            </div>

            <div class="skill-rating-container">
              <span class="rating-label">Aisance :</span>
              <div class="skill-rating">
                <span 
                  v-for="star in 5" 
                  :key="star" 
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
      </div>
    </div>

    <!-- Section Apprentissage Autodidacte -->
    <div class="skill-section-group" v-if="autodidacteSkills.length">
      <button class="category-toggle-btn" @click="isAutodidacteOpen = !isAutodidacteOpen">
        <span class="category-title-text">Apprentissage Autodidacte & Personnel <span class="count-badge">({{ autodidacteSkills.length }})</span></span>
        <span class="toggle-icon" :class="{ 'rotated': !isAutodidacteOpen }">▼</span>
      </button>

      <div class="skills-grid" v-show="isAutodidacteOpen">
        <div 
          v-for="(skill, index) in autodidacteSkills" 
          :key="skill.name" 
          class="skill-card"
          :class="{ 'reverse': index % 2 !== 1 }"
        >
          <div class="skill-icon-box">
            <span class="skill-emoji">{{ skill.icon }}</span>
          </div>

          <div class="skill-text-box">
            <span class="skill-category">{{ skill.category }}</span>
            <h3>{{ skill.name }}</h3>
            <p>{{ skill.description }}</p>
            
            <div class="skill-projects" v-if="skill.projects && skill.projects.length">
              <span class="projects-label">Projets :</span>
              <a href="#projects" class="project-tag" v-for="proj in skill.projects" :key="proj">{{ proj }}</a>
            </div>

            <div class="skill-rating-container">
              <span class="rating-label">Aisance :</span>
              <div class="skill-rating">
                <span 
                  v-for="star in 5" 
                  :key="star" 
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
      </div>
    </div>
  </section>
</template>

<style scoped>
.skills-section {
  padding: 4rem 2rem;
  max-width: 1200px;
  margin: 0 auto;
}

.skills-section h2 {
  font-family: var(--font-title);
  font-size: 2rem;
  color: var(--accent-color);
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

.sort-group {
  display: flex;
  align-items: center;
  gap: 0.8rem;
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

.sort-select {
  background: color-mix(in srgb, var(--text-color) 5%, transparent);
  border: 1px solid color-mix(in srgb, var(--text-color) 20%, transparent);
  color: var(--text-color);
  padding: 0.3rem 0.6rem;
  border-radius: 6px;
  font-size: 0.85rem;
  outline: none;
  cursor: pointer;
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

.skills-grid {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
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
  box-sizing: border-box;
}

.skill-card:hover {
  box-shadow: 0 0 15px var(--accent-color);
  transform: translateY(-3px);
}

.skill-card.reverse {
  flex-direction: row-reverse;
}

.skill-card.reverse .skill-text-box {
  text-align: left;
}

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
  color: var(--accent-color);
  opacity: 0.8;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.skill-text-box h3 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  color: var(--text-color);
  margin: 0.2rem 0 0.3rem 0;
}

.skill-text-box p {
  font-size: 0.8rem;
  opacity: 0.8;
  margin: 0 0 0.5rem 0;
  line-height: 1.3;
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
  color: var(--accent-color);
  text-shadow: 0 0 5px var(--accent-color);
}

.star.half {
  background: linear-gradient(90deg, var(--accent-color) 50%, color-mix(in srgb, var(--text-color) 25%, transparent) 50%);
  -webkit-background-clip: text;
  -webkit-text-fill-color: transparent;
  filter: drop-shadow(0 0 3px var(--accent-color));
}
</style>