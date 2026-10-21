<script setup>
const skills = [
  { 
    id: 1, 
    name: "Linux terminals", 
    category: "Système & Infrastructure", 
    description: "Maîtrise des commandes, administration et gestion des scripts shell.", 
    icon: "🐧", 
    projects: ["Intégralité des projets"],
    rating: 4 
  },
  { 
    id: 2, 
    name: "Git", 
    category: "Outils & Versioning", 
    description: "Gestion de versions, branches, fusion et travail collaborative.", 
    icon: "🌿", 
    projects: ["Intégralité des projets"],
    rating: 4 
  },
  { 
    id: 3, 
    name: "Python", 
    category: "Programmation", 
    description: "Développement de scripts, automatisation et traitement de données.", 
    icon: "🐍", 
    projects: ["Statistiques Page Rank", "Exploitation BD"],
    rating: 3.5 
  },
  { 
    id: 4, 
    name: "Java", 
    category: "Programmation", 
    description: "Programmation orientée objet, structures de données et robustesse.", 
    icon: "☕", 
    projects: ["VigieChiro Compagnon"],
    rating: 3
  },
  { 
    id: 5, 
    name: "C++", 
    category: "Programmation", 
    description: "Gestion de la mémoire, performance et algorithmique avancée.", 
    icon: "⚙️", 
    projects: ["Systèmes de votes", "Candy Crush"],
    rating: 3.5
  },
  { 
    id: 6, 
    name: "PostgreSQL", 
    category: "Bases de données", 
    description: "Conception de schémas relationnels, requêtes complexes et optimisation.", 
    icon: "🐘", 
    projects: ["DataLab"],
    rating: 4 
  },
  { 
    id: 7, 
    name: "DNS servers", 
    category: "Réseaux", 
    description: "Configuration, résolution de noms et architecture des serveurs DNS.", 
    icon: "🌐", 
    projects: ["Serveurs DNS / MX / Apache"],
    rating: 3.5
  },
  { 
    id: 8, 
    name: "Apache servers", 
    category: "Infrastructures Web", 
    description: "Déploiement, configuration de virtual hosts et sécurisation web.", 
    icon: "🪶", 
    projects: ["Serveurs DNS / MX / Apache"],
    rating: 2.5
  },
  { 
    id: 9, 
    name: "MX servers", 
    category: "Réseaux & Messagerie", 
    description: "Gestion des serveurs de messagerie et protocoles de routage d'e-mails.", 
    icon: "✉️", 
    projects: ["Serveurs DNS / MX / Apache"],
    rating: 2.5
  },
  { 
    id: 10, 
    name: "HTML", 
    category: "Web Standard", 
    description: "Sémantique, structure de documents et accessibilité de base.", 
    icon: "📄", 
    projects: ["Portfolio", "Page web statique"],
    rating: 3.5
  },
  { 
    id: 11, 
    name: "CSS", 
    category: "Styling & Design", 
    description: "Mise en page, variables, animations et design system cyber.", 
    icon: "🎨", 
    projects: ["Portfolio", "Page web statique"],
    rating: 3 
  },
  { 
    id: 12, 
    name: "JavaScript", 
    category: "Programmation Web", 
    description: "Dynamisme, manipulation du DOM et programmation asynchrone.", 
    icon: "⚡", 
    projects: ["Portfolio"],
    rating: 2.5
  },
  { 
    id: 13, 
    name: "Vue.js", 
    category: "Framework Frontend", 
    description: "Composants réactifs, composition API et architecture SPA.", 
    icon: "🟢", 
    projects: ["Portfolio"],
    rating: 3.5
  },
  { 
    id: 14, 
    name: "Node.js", 
    category: "Backend", 
    description: "Environnement d'exécution JavaScript coté serveur et API.", 
    icon: "🟢", 
    projects: ["Portfolio"],
    rating: 3 
  }
]
</script>

<template>
  <section id="skills" class="skills-section">
    <h2>Mes compétences</h2>
    <div class="skills-grid">
      <div 
        v-for="(skill, index) in skills" 
        :key="skill.id" 
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
            <span class="project-tag" v-for="proj in skill.projects" :key="proj">{{ proj }}</span>
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
  margin-bottom: 2.5rem;
  text-align: left;
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