<script setup>
import { ref, onMounted, onUnmounted } from 'vue'

const mouseGridStyle = ref({
  '--mouse-x': '50vw',
  '--mouse-y': '50vh',
  '--mouse-opacity': '0'
})

const onMouseMove = (e) => {
  mouseGridStyle.value = {
    '--mouse-x': `${e.clientX}px`,
    '--mouse-y': `${e.clientY}px`,
    '--mouse-opacity': '1'
  }
}

const onMouseLeave = () => {
  mouseGridStyle.value['--mouse-opacity'] = '0'
}

onMounted(() => {
  window.addEventListener('mousemove', onMouseMove, { passive: true })
  document.addEventListener('mouseleave', onMouseLeave)
})

onUnmounted(() => {
  window.removeEventListener('mousemove', onMouseMove)
  document.removeEventListener('mouseleave', onMouseLeave)
})
</script>

<template>
  <div class="background-effect-container">
    <div class="bg-layer cyber-grid" :style="mouseGridStyle">
      <!-- Grille de base : repère subtil bien visible -->
      <div class="grid-mesh-base"></div>
      <!-- Grille révélée : nette, contrastée et mise en valeur sous la souris -->
      <div class="grid-mesh-reveal"></div>
    </div>
  </div>
</template>

<style scoped>
.background-effect-container {
  position: fixed;
  top: 0;
  left: 0;
  width: 100vw;
  height: 100vh;
  pointer-events: none;
  z-index: 0;
  overflow: hidden;
}

.bg-layer {
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
}

.cyber-grid {
  opacity: 1;
}

/* Grille de fond passive */
.grid-mesh-base {
  position: absolute;
  inset: 0;
  background-size: 44px 44px;
  background-image:
    linear-gradient(to right, color-mix(in srgb, var(--accent-color) 7%, transparent) 1px, transparent 1px),
    linear-gradient(to bottom, color-mix(in srgb, var(--accent-color) 7%, transparent) 1px, transparent 1px);
}

/* Grille révélée sous le curseur */
.grid-mesh-reveal {
  position: absolute;
  inset: 0;
  background-size: 44px 44px;
  background-image:
    linear-gradient(to right, color-mix(in srgb, var(--accent-color) 42%, transparent) 1.2px, transparent 1.2px),
    linear-gradient(to bottom, color-mix(in srgb, var(--accent-color) 42%, transparent) 1.2px, transparent 1.2px);
  mask-image: radial-gradient(
    circle 260px at var(--mouse-x, 50vw) var(--mouse-y, 50vh),
    black 0%,
    rgba(0, 0, 0, 0.55) 45%,
    transparent 80%
  );
  -webkit-mask-image: radial-gradient(
    circle 260px at var(--mouse-x, 50vw) var(--mouse-y, 50vh),
    black 0%,
    rgba(0, 0, 0, 0.55) 45%,
    transparent 80%
  );
  opacity: var(--mouse-opacity, 0);
  transition: opacity 0.3s ease;
  pointer-events: none;
}
</style>
