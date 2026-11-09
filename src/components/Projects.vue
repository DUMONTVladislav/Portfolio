<script setup>
const projectCategories = [
  {
    category: "Projets Universitaires",
    projects: [
        {
            id: 2,
            title: "Systèmes de vote",
            language: "C++",
            description: "Adaptation de plusieurs systèmes de vote en C++ et tests avec des fichiers Oracle",
            imageSrc: "",
            githubUrl: ""
        },
        {
            id: 3,
            title: "Candy Crush",
            language: "C++",
            description: "Recréation du jeu emblématique Candy Crush en C++ avec les modes suivants : classique, histoire, 1v1",
            imageSrc: "",
            githubUrl: ""
        },
        {
          id: 4,
          title: "Page web statique : Rock O' Rama",
          language: "HTML / CSS",
          description: "Création de ma première page web statique sur le thème du rock !",
          imageSrc: "",
          githubUrl: ""
        },
        {
          id: 5,
          title: "Modélisation et Exploitation d'une BDD : Les Tenracs",
          language: "SQL / Python",
          description: "Modélisation du système de la confrérie des TENders RAClette et exploitation de données générées via Faker",
          imageSrc: "",
          githubUrl: ""
        },
        {
          id: 6,
          title: "Statistiques PageRank",
          language: "Python",
          description: "Analyse de l'algorithme de Google PageRank avec Python",
          imageSrc: "",
          githubUrl: ""
        },
        {
          id: 7,
          title: "Mise en place de serveurs Apache, DNS et MX",
          language : "Apache / DNS / MX",
          description: "Mise en places des serveurs et premières notions de cybersécurité",
          imageSrc: "",
          githubUrl: ""
        },
        {
          id: 8,
          title: "VigieChiro Compagnon",
          language: "Java / JavaFX",
          description: "Modélisation, visualisation, conception et tests d'une application portant sur l'étude de la faune de nuit",
          imageSrc: "",
          githubUrl: ""
        },
        {
          id: 9,
          title: "DataLab",
          language: "HTML / CSS / PHP / SQL / JavaScript",
          description: "Création d'un site web de manipulation de BDD a but pédagogique"
        }
    ]
  },
  {
    category: "Projets Personnels",
    projects: [
      {
        id: 1,
        title: "Portfolio",
        language: "Vue.js / CSS",
        description: "Création d'un espace technique interactif avec design system sur mesure et esthétique de centre de contrôle",
        imageSrc: "",
        githubUrl: "https://github.com/DUMONTVladislav/Portfolio"
      }
    ]
  }
]
</script>

<template>
  <section id="projects" class="projects-section">
    <h2>Mes projets</h2>

    <div v-for="cat in projectCategories" :key="cat.category" class="project-category-group">
      <h3 class="category-title">{{ cat.category }}</h3>
      
      <div class="projects-container">
        <article 
          v-for="project in cat.projects" 
          :key="project.id" 
          class="project-card-large"
        >
          <div class="project-screenshot-box">
            <img :src="project.imageSrc" :alt="project.title" class="project-screenshot" />
          </div>

          <div class="project-content">
            <span class="project-language">{{ project.language }}</span>
            <h4>{{ project.title }}</h4>
            <p>{{ project.description }}</p>
            
            <div class="project-actions" v-if="project.githubUrl">
              <a :href="project.githubUrl" target="_blank" class="btn-outline">Voir sur GitHub</a>
            </div>
          </div>
        </article>
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
  margin-bottom: 2.5rem;
  text-align: left;
}

.project-category-group {
  margin-bottom: 3.5rem;
}

.category-title {
  font-family: var(--font-title);
  font-size: 1.3rem;
  color: var(--text-color);
  margin-bottom: 1.5rem;
  border-left: 3px solid var(--accent-color);
  padding-left: 0.75rem;
  opacity: 0.9;
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
  box-shadow: inset 0 0 10px rgba(0, 0, 0, 0.5);
}

.project-screenshot {
  width: 100%;
  height: 100%;
  object-fit: cover;
}

.project-content {
  flex: 1;
  display: flex;
  flex-direction: column;
  text-align: left;
}

.project-language {
  font-family: var(--font-title);
  font-size: 0.75rem;
  color: var(--accent-color);
  opacity: 0.9;
  text-transform: uppercase;
  letter-spacing: 1px;
  margin-bottom: 0.4rem;
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
</style>