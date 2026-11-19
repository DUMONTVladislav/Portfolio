<script setup>
import { ref } from 'vue'

const activeMobileTab = ref('timeline')
</script>

<template>
  <section id="home" class="hero-section">
    <div v-reveal class="hero-header">
      <h1>Futur expert en cyber-sécurité</h1>
      <h2>Ma présentation</h2>
    </div>

    <div v-reveal="{ delay: 100 }" class="hero-middle-row">
      <div class="hero-content">
        <p>
          Actuellement en 2ème année de BUT Informatique à l'IUT d'Aix-en-Provence,
          je suis le parcours Déploiement d'applications communicantes et sécurisées.
          Je suis passionné par les infrastructures réseaux, la gestion des bases de données et
          l'évolution du monde de l'Informatique.<br />
          Bienvenue dans mon espace technique !
        </p>
      </div>

      <div class="hero-nav-links">
        <a href="#skills" class="btn-outline">Mes compétences</a>
        <a href="#projects" class="btn-outline">Mes projets</a>
      </div>
    </div>

    <div class="hero-card-container">
      <div class="mobile-tabs-bar" role="tablist" aria-label="Parcours et CV">
        <button
          type="button"
          role="tab"
          :aria-selected="activeMobileTab === 'timeline'"
          class="mobile-tab-btn"
          :class="{ active: activeMobileTab === 'timeline' }"
          @click="activeMobileTab = 'timeline'"
        >
          📅 Mon Parcours
        </button>
        <button
          type="button"
          role="tab"
          :aria-selected="activeMobileTab === 'cv'"
          class="mobile-tab-btn"
          :class="{ active: activeMobileTab === 'cv' }"
          @click="activeMobileTab = 'cv'"
        >
          📄 Mon CV
        </button>
      </div>

      <div class="card-display-box">
        <div
          v-reveal="{ delay: 150 }"
          class="tab-content timeline-container"
          :class="{ 'mobile-hidden': activeMobileTab !== 'timeline' }"
        >
          <h3 class="desktop-only-title">Mon Parcours</h3>
          <div class="timeline">
            <div v-reveal="{ delay: 80 }" class="timeline-item">
              <div class="timeline-dot"></div>
              <div class="timeline-content">
                <span class="timeline-date">2026 - Présent</span>
                <h4>BUT Informatique - 2ème année (DEPLOI)</h4>
                <p>IUT d'Aix-en-Provence</p>
                <ul>
                  <li>Compétences techniques : PostgreSQL, PHP</li>
                  <li>Projets : DataLab, Flexarion</li>
                </ul>
              </div>
            </div>

            <div v-reveal="{ delay: 160 }" class="timeline-item">
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

            <div v-reveal="{ delay: 240 }" class="timeline-item">
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

        <div
          v-reveal="{ delay: 200 }"
          class="tab-content cv-container"
          :class="{ 'mobile-hidden': activeMobileTab !== 'cv' }"
        >
          <h3 class="desktop-only-title">Mon CV</h3>
          <iframe src="/cv.pdf" class="cv-viewer" title="CV - Vladislav DUMONT"></iframe>
          <div class="cv-actions">
            <a href="/cv.pdf" target="_blank" rel="noopener noreferrer" class="btn-outline">
              Ouvrir dans un nouvel onglet
            </a>
            <a href="/cv.pdf" download class="btn-outline btn-secondary">
              Télécharger le CV
            </a>
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
  padding: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 3.5rem) 2rem 4rem 2rem;
  min-height: 100vh;
  gap: 2.5rem;
  box-sizing: border-box;
  max-width: 1200px;
  margin: 0 auto;
  overflow-x: clip;
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
  min-width: 0;
}

.hero-content p {
  line-height: 1.6;
  margin: 0;
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
  grid-template-columns: minmax(0, 1fr) minmax(0, 1fr);
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
  display: inline-flex;
  align-items: center;
  justify-content: center;
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
  box-sizing: border-box;
}

.btn-outline:hover {
  background-color: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 12px var(--accent-color);
  transform: translateY(-2px);
}

.btn-outline.btn-secondary {
  background: color-mix(in srgb, var(--accent-color) 12%, transparent);
}

.timeline-container {
  overflow-y: auto;
  padding-right: 0.75rem;
  flex: 1;
  min-height: 0;
  -webkit-overflow-scrolling: touch;
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
  overflow-wrap: anywhere;
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
  gap: 0.75rem;
  flex-wrap: wrap;
}

.cv-actions .btn-outline {
  width: auto;
  min-width: 180px;
  padding: 0.55rem 1rem;
  font-size: 0.8rem;
}

.mobile-tabs-bar {
  display: none;
  gap: 0.75rem;
  margin-bottom: 1.25rem;
  width: 100%;
}

.mobile-tab-btn {
  flex: 1;
  background: color-mix(in srgb, var(--accent-color) 10%, var(--nav-bg));
  border: 1px solid color-mix(in srgb, var(--accent-color) 40%, transparent);
  color: var(--text-color);
  padding: 0.65rem 0.5rem;
  border-radius: 8px;
  font-family: var(--font-title);
  font-size: 0.85rem;
  cursor: pointer;
  touch-action: manipulation;
  transition: all 0.25s ease;
  text-align: center;
}

.mobile-tab-btn.active {
  background: var(--accent-color);
  color: #ffffff;
  border-color: var(--accent-color);
  box-shadow: 0 0 10px var(--accent-color);
}

@media (max-width: 1024px) and (min-width: 869px) {
  .hero-middle-row {
    gap: 2rem;
  }

  .hero-card-container {
    height: 540px;
  }

  .card-display-box {
    gap: 1.5rem;
  }
}

@media (max-width: 868px) {
  .hero-section {
    padding: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 2rem) 1.5rem 3rem 1.5rem;
    min-height: auto;
    gap: 2rem;
  }

  .hero-header h1 {
    font-size: clamp(1.4rem, 4.5vw, 1.9rem);
  }

  .hero-middle-row {
    flex-direction: column;
    align-items: stretch;
    gap: 1.5rem;
  }

  .hero-nav-links {
    flex-direction: row;
    flex-wrap: wrap;
    justify-content: flex-start;
    gap: 1rem;
    width: 100%;
  }

  .hero-nav-links .btn-outline {
    flex: 1;
    min-width: 140px;
    width: auto;
  }

  .hero-card-container {
    height: 580px;
    padding: 1.25rem;
  }

  .mobile-tabs-bar {
    display: flex;
  }

  .desktop-only-title {
    display: none;
  }

  .card-display-box {
    display: flex;
    flex-direction: column;
    height: 100%;
    min-height: 0;
  }

  .tab-content.mobile-hidden {
    display: none !important;
  }
}

@media (max-width: 480px) {
  .hero-section {
    padding: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 1.25rem) 1rem 2.5rem 1rem;
    gap: 1.5rem;
  }

  .hero-header h1 {
    font-size: 1.35rem;
  }

  .hero-content p {
    font-size: 0.9rem;
    line-height: 1.5;
  }

  .hero-nav-links {
    flex-direction: column;
  }

  .hero-nav-links .btn-outline {
    width: 100%;
  }

  .hero-card-container {
    height: 520px;
    padding: 1rem;
    border-radius: 10px;
  }

  .mobile-tab-btn {
    font-size: 0.78rem;
    padding: 0.55rem 0.3rem;
  }

  .timeline {
    margin-left: 0.25rem;
    padding-left: 1.2rem;
  }

  .timeline-dot {
    left: -1.55rem;
  }

  .cv-actions {
    flex-direction: column;
    gap: 0.5rem;
  }

  .cv-actions .btn-outline {
    width: 100%;
    min-width: 0;
  }
}
</style>