<script setup>
import { ref } from 'vue'

const isLightMode = ref(false)

const toggleTheme = () => {
  isLightMode.value = !isLightMode.value
  document.body.classList.toggle('light-mode', isLightMode.value)
}
</script>
<template>
    <nav>
        <ul>
            <li><a href="#home">Accueil</a></li>
            <li><a href="#skills">Compétences</a></li>
            <li><a href="#projects">Projets</a></li>
        </ul>
        <button @click="toggleTheme" class="theme-toggle-btn">
  Mode Clair / Sombre
</button>
    </nav>
</template>
<style scoped></style>