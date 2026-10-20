<script setup>
// Note : Le sélecteur d'onglets sera réintégré plus tard pour la version mobile
</script>
<template>
  <section id="accueil" class="hero-section">
    <div class="hero-header">
      <h1>Futur expert en cyber-sécurité</h1>
      <h2>Ma présentation</h2>
    </div>

    <div class="hero-middle-row">
      <div class="hero-content">
        <p>
          Actuellement en 2ème année de BUT Informatique à l'IUT d'Aix-en-Provence,
          je suis le parcours Déploiement d'applications communicantes et sécurisées.
          Passionné par les infrastructures réseaux, la gestion des bases de données et 
          l'évolution constante de l'écosystème IT. Je m'intéresse aux rouages profonds du 
          numérique et à la sécurisation des systèmes.<br>
          Bienvenue dans mon espace technique.
        </p>
      </div>
      
      <div class="hero-nav-links">
        <a href="#skills" class="btn-outline">Mes compétences</a>
        <a href="#projects" class="btn-outline">Mes projets</a>
      </div>
    </div>

    <div class="hero-card-container">
      <div class="card-display-box">
        <div class="tab-content timeline-container">
          <h3>Mon Parcours</h3>
          <div class="timeline">
            <div class="timeline-item">
              <div class="timeline-dot"></div>
              <div class="timeline-content">
                <span class="timeline-date">2026 - Présent</span>
                <h4>BUT Informatique - 2ème année (DEPLOI)</h4>
                <p>IUT d'Aix-en-Provence</p>
                <ul>
                    <li>Compétences techniques : PostgreSQL, PHP</li>
                    <li>Projet : DataLab</li>
                </ul>
              </div>
            </div>
            
            <div class="timeline-item">
              <div class="timeline-dot"></div>
              <div class="timeline-content">
                <span class="timeline-date">2025 - 2026</span>
                <h4>BUT Informatique - 1ère année</h4>
                <p>IUT d'Aix-en-Provence</p>
                <ul>
                    <li>Compétences techniques : Terminaux linux, Git, C++, Python, Java, SQL, Bases réseau, HTML, CSS, MIPS</li>
                    <li>Projets : Candy Crush, Systèmes de votes, Page web statique, Serveurs DNS / MX / Apache, Exploitation BD, Statistiques Page Rank, VigieChiro Compagnon</li>
                </ul>
              </div>
            </div>

            <div class="timeline-item">
              <div class="timeline-dot"></div>
              <div class="timeline-content">
                <span class="timeline-date">2024 - 2025</span>
                <h4>Obtention du Baccalauréat</h4>
                <p>Lycée Adam de Craponne</p>
                <ul>
                    <li>Spécialités : Mathématiques et Numériques Sciences Informatiques</li>
                    <li>Options : Mathématiques expertes et Anglais euro mathématiques</li>
                </ul>
              </div>
            </div>
          </div>
        </div>

        <div class="tab-content cv-container">
          <h3>Mon CV</h3>
          <iframe src="/cv.pdf" class="cv-viewer" title="CV - Vladislav DUMONT"></iframe>
          <div class="cv-actions">
            <a href="/cv.pdf" target="_blank" class="btn-outline">Ouvrir dans un nouvel onglet</a>
          </div>
        </div>
      </div>
    </div>
  </section>
</template>
<style scoped>
.hero-section {
  display: flex;
  flex-direction: column;
  padding: 8rem 2rem 4rem 2rem;
  min-height: 100vh;
  gap: 2.5rem;
  box-sizing: border-box;
  max-width: 1200px;
  margin: 0 auto;
}

.hero-header {
  width: 100%;
}

.hero-header h1 {
  font-family: var(--font-title);
  font-size: 2.2rem;
  color: var(--accent-color);
  margin-bottom: 0.5rem;
}

.hero-header h2 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  opacity: 0.8;
  margin-bottom: 0;
}

.hero-middle-row {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 3rem;
  width: 100%;
}

.hero-content {
  flex: 2;
}

.hero-nav-links {
  flex: 1;
  display: flex;
  flex-direction: column;
  gap: 1rem;
  align-items: flex-end;
}

.hero-card-container {
  width: 100%;
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-radius: 12px;
  padding: 1.5rem;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);
  height: 600px;
  display: flex;
  flex-direction: column;
  box-sizing: border-box;
}

.card-display-box {
  flex: 1;
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 2rem;
  overflow: hidden;
  height: 100%;
  min-height: 0;
}

.card-display-box h3 {
  font-family: var(--font-title);
  font-size: 1.15rem;
  color: var(--accent-color);
  margin-top: 0;
  margin-bottom: 1rem;
}

.tab-content {
  height: 100%;
  display: flex;
  flex-direction: column;
  min-width: 0;
}

.btn-outline {
  display: inline-block;
  padding: 0.75rem 1.5rem;
  font-family: var(--font-title);
  font-size: 0.9rem;
  text-decoration: none;
  color: var(--text-color);
  background: transparent;
  border: 1px solid var(--accent-color);
  border-radius: 6px;
  cursor: pointer;
  transition: all 0.3s ease;
  text-align: center;
  width: 200px;
}

.btn-outline:hover {
  background-color: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 12px var(--accent-color);
  transform: translateY(-2px);
}

.timeline-container {
  overflow-y: auto;
  padding-right: 0.75rem;
  flex: 1;
  min-height: 0;
}

.timeline-container h3 {
  position: sticky;
  top: 0;
  background-color: var(--nav-bg);
  z-index: 2;
  padding-bottom: 0.5rem;
}

.timeline {
  position: relative;
  margin-left: 1rem;
  padding-left: 1.5rem;
  border-left: 2px solid var(--text-color);
}

.timeline-item {
  position: relative;
  margin-bottom: 1.5rem;
}

.timeline-dot {
  position: absolute;
  left: -1.85rem;
  top: 0.25rem;
  width: 10px;
  height: 10px;
  background-color: var(--accent-color);
  border-radius: 50%;
  box-shadow: 0 0 8px var(--accent-color);
}

.timeline-date {
  font-family: var(--font-title);
  font-size: 0.75rem;
  color: var(--accent-color);
  opacity: 0.9;
}

.timeline-content h4 {
  font-family: var(--font-title);
  font-size: 0.9rem;
  margin: 0.2rem 0;
  color: var(--text-color);
}

.timeline-content p {
  font-size: 0.85rem;
  opacity: 0.8;
  margin: 0;
}

.timeline-content ul {
  list-style: none;
  font-size: 0.8rem;
  opacity: 0.8;
  margin: 0.5rem 0;
  padding-left: 0.5rem;
}

.timeline-content li {
  font-size: 0.8rem;
  opacity: 0.85;
  margin-bottom: 0.3rem;
  position: relative;
  padding-left: 1rem;
}

.timeline-content li::before {
  content: ">";
  position: absolute;
  left: 0;
  color: var(--accent-color);
  font-weight: bold;
}

.timeline-container::-webkit-scrollbar {
  width: 6px;
}

.timeline-container::-webkit-scrollbar-track {
  background: rgba(0, 0, 0, 0.1);
  border-radius: 4px;
}

.timeline-container::-webkit-scrollbar-thumb {
  background-color: var(--accent-color);
  border-radius: 4px;
  box-shadow: 0 0 5px var(--accent-color);
}

.timeline-container::-webkit-scrollbar-thumb:hover {
  background-color: var(--text-color);
}

.cv-container {
  display: flex;
  flex-direction: column;
  height: 100%;
  min-height: 0;
}

.cv-viewer {
  width: 100%;
  flex: 1;
  min-height: 0;
  border: 1px solid rgba(255, 255, 255, 0.1);
  border-radius: 8px;
  background-color: #ffffff;
}

.cv-actions {
  margin-top: 1rem;
  display: flex;
  justify-content: center;
}

.cv-actions .btn-outline {
  width: auto;
  min-width: 220px;
  padding: 0.6rem 1.2rem;
  font-size: 0.85rem;
}
</style>