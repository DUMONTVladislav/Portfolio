<script setup>
import { ref } from 'vue'

const isLightMode = ref(false)

const toggleTheme = () => {
  isLightMode.value = !isLightMode.value
  document.body.classList.toggle('light-mode', isLightMode.value)
}
</script>
<template>
<nav class="navbar">
    <div class="nav-brand">
      <span class="logo-text">Portfolio</span>
    </div>
    
    <ul class="nav-links">
      <li><a href="#accueil">Accueil</a></li>
      <li><a href="#competences">Compétences</a></li>
      <li><a href="#projets">Projets</a></li>
      <li><a href="#footer">Contact</a></li>
    </ul>

    <!-- Le bouton de bascule de thème -->
    <button @click="toggleTheme" class="theme-btn">
        Thème
    </button>
  </nav>
</template>
<style scoped>
.navbar {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 1rem 2rem;
  background-color: var(--nav-bg);
  border-bottom: 1px solid rgba(255, 255, 255, 0.08);
  backdrop-filter: blur(10px);
  z-index: 1000;
  box-sizing: border-box;
}

.logo-text {
  font-family: var(--font-title);
  font-weight: 700;
  font-size: 1.2rem;
  color: var(--accent-color);
}

.nav-links {
  list-style: none;
  display: flex;
  gap: 2rem;
  margin: 0;
  padding: 0;
}

.nav-links a {
  text-decoration: none;
  color: var(--text-color);
  font-weight: 500;
  transition: color 0.3s ease;
}

.nav-links a:hover {
  color: var(--accent-color);
}

.theme-btn {
  background: transparent;
  border: 2px solid var(--accent-color);
  color: var(--text-color);
  padding: 0.5rem 1rem;
  border-radius: 8px;
  cursor: pointer;
  font-family: var(--font-body);
  transition: all 0.3s ease;
}

.theme-btn:hover {
  background-color: var(--accent-color);
  color: #fff;
}
</style>