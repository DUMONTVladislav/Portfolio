<script setup>
import { ref } from 'vue'
import AlertBanner from './components/AlertBanner.vue'
import Home from './components/Home.vue'
import Skills from './components/Skills.vue'
import News from './components/News.vue'
import Navbar from './components/Navbar.vue'
import Projects from './components/Projects.vue'
import Footer from './components/Footer.vue'
import BackgroundEffect from './components/BackgroundEffect.vue'
import { useI18n } from './composables/useI18n.js'

const { t } = useI18n()
const bannerRef = ref(null)
</script>

<template>
  <a href="#main-content" class="skip-link">{{ t('nav.skipToContent') }}</a>
  <BackgroundEffect />
  <AlertBanner ref="bannerRef" />
  <Navbar />
  <main id="main-content" tabindex="-1">
    <Home />
    <Skills />
    <News />
    <Projects />
  </main>
  <Footer />
</template>

<style scoped>
.skip-link {
  position: fixed;
  top: -100px;
  left: 1rem;
  z-index: 2000;
  background: var(--accent-color);
  color: #ffffff;
  font-family: var(--font-title);
  font-size: 0.85rem;
  font-weight: 600;
  padding: 0.65rem 1.1rem;
  border-radius: 8px;
  text-decoration: none;
  box-shadow: 0 4px 16px rgba(0, 0, 0, 0.45);
  transition: top 0.2s ease;
}

.skip-link:focus-visible {
  top: 0.85rem;
  outline: 2px solid #ffffff;
  outline-offset: 2px;
}

main:focus {
  outline: none;
}

@media (prefers-reduced-motion: reduce) {
  .skip-link {
    transition: none !important;
  }
}
</style>
