<script setup>
</script>

<template>
  <footer id="footer" class="footer-section">
    <div class="footer-container">
      <div class="footer-info">
        <h3>Contact & Informations</h3>
        <p>Vladislav DUMONT — Futur expert en cyber-sécurité</p>
        <p>IUT d'Aix-en-Provence • BUT Informatique (DEPLOI)</p>
        <p>Email : <a href="mailto:vladislav.dumont@gmail.com" class="footer-link">vladislav.dumont@gmail.com</a></p>
      </div>

      <div class="footer-legal">
        <h3>Mentions Légales</h3>
        <p>Ce portfolio est un site web personnel à vocation technique et professionnelle.</p>
        <p>Hébergé sur ... • Tous droits réservés © 2026</p>
      </div>
    </div>
  </footer>
</template>

<style scoped>
.footer-section {
  background: var(--nav-bg);
  border-top: 1px solid var(--accent-color);
  padding: 3rem 2rem;
  margin-top: 4rem;
  box-sizing: border-box;
}

.footer-container {
  max-width: 1200px;
  margin: 0 auto;
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 3rem;
  text-align: left;
}

.footer-info, .footer-legal {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

.footer-section h3 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  color: var(--accent-color);
  margin-bottom: 0.5rem;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.footer-section p {
  font-size: 0.85rem;
  opacity: 0.8;
  margin: 0;
  line-height: 1.4;
  color: var(--text-color);
}

.footer-link {
  color: var(--accent-color);
  text-decoration: none;
  transition: opacity 0.3s ease;
}

.footer-link:hover {
  text-decoration: underline;
  opacity: 1;
}
</style>