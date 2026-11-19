<script setup>
import { ref } from 'vue'
import AlertBanner from './components/AlertBanner.vue'
import Home from './components/Home.vue'
import Skills from './components/Skills.vue'
import News from './components/News.vue'
import Navbar from './components/Navbar.vue'
import Projects from './components/Projects.vue'
import Footer from './components/Footer.vue'

const isDev = import.meta.env.DEV
const bannerRef = ref(null)

const triggerBannerReset = () => {
  bannerRef.value?.resetBanner()
}
</script>

<template>
  <AlertBanner ref="bannerRef" />
  <Navbar />
  <Home />
  <Skills />
  <News />
  <Projects />
  <Footer />

  <!--
  <button
    v-if="isDev"
    @click="triggerBannerReset"
    class="dev-reset-banner-btn"
    title="Réinitialiser la bannière d'alerte (DEV uniquement)"
  >
    [DEV] Reset Banner
  </button>
-->
</template>

<style scoped>
.dev-reset-banner-btn {
  position: fixed;
  bottom: 1rem;
  right: 1rem;
  z-index: 2000;
  background: var(--nav-bg);
  color: var(--accent-color);
  border: 1px dashed var(--accent-color);
  border-radius: 6px;
  padding: 0.45rem 0.75rem;
  font-family: monospace;
  font-size: 0.75rem;
  cursor: pointer;
  opacity: 0.85;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.35);
  transition: opacity 0.2s ease, transform 0.2s ease, background-color 0.2s ease;
}

.dev-reset-banner-btn:hover {
  opacity: 1;
  transform: translateY(-2px);
  background: color-mix(in srgb, var(--accent-color) 15%, var(--nav-bg));
}
</style>