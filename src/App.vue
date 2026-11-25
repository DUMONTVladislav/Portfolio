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

const bannerRef = ref(null)
</script>

<template>
  <BackgroundEffect />
  <AlertBanner ref="bannerRef" />
  <Navbar />
  <Home />
  <Skills />
  <News />
  <Projects />
  <Footer />
</template>

<style scoped>
</style>
