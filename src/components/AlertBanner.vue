<script setup>
import { ref, watch, onMounted, onUnmounted, nextTick } from 'vue'

const emit = defineEmits(['visibility-change', 'height-change'])

const isVisible = ref(false)
const bannerRef = ref(null)
const bannerKey = 'portfolio_alert_v1'

const reportHeight = () => {
  nextTick(() => {
    const height = isVisible.value ? (bannerRef.value?.offsetHeight || 46) : 0
    emit('height-change', height)
  })
}

onMounted(() => {
  const dismissed = localStorage.getItem(bannerKey)
  isVisible.value = !dismissed
  emit('visibility-change', isVisible.value)
  reportHeight()
  window.addEventListener('resize', reportHeight)
})

onUnmounted(() => {
  window.removeEventListener('resize', reportHeight)
})

watch(isVisible, (val) => {
  emit('visibility-change', val)
  reportHeight()
})

const closeBanner = () => {
  isVisible.value = false
  localStorage.setItem(bannerKey, 'true')
}

const onAfterLeave = () => {
  emit('height-change', 0)
}

const resetBanner = () => {
  localStorage.removeItem(bannerKey)
  isVisible.value = true
}

defineExpose({
  resetBanner
})
</script>

<template>
  <Transition name="banner-slide" @after-leave="onAfterLeave">
    <div v-if="isVisible" ref="bannerRef" class="alert-banner">
      <div class="banner-content">
        <span class="banner-badge">News</span>
        <p class="banner-text">
          ⚡ <strong>Nouvel article disponible :</strong> Découvrez mon point de vue sur l'utilisation de l'IA !
        </p>
        <a href="#news" class="banner-link">Lire l'article ➔</a>
      </div>
      <button @click="closeBanner" class="banner-close-btn" title="Fermer l'alerte">✕</button>
    </div>
  </Transition>
</template>

<style scoped>
.alert-banner {
  position: fixed;
  top: var(--navbar-height, 64px);
  left: 0;
  width: 100%;
  background: color-mix(in srgb, var(--accent-color) 15%, var(--nav-bg));
  border-bottom: 1px solid var(--accent-color);
  padding: 0.65rem 2rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
  z-index: 999;
  box-shadow: 0 4px 14px rgba(0, 0, 0, 0.35);
  backdrop-filter: blur(10px);
  box-sizing: border-box;
}

.banner-content {
  display: flex;
  align-items: center;
  gap: 1rem;
  flex: 1;
  justify-content: center;
  flex-wrap: wrap;
  text-align: center;
}

.banner-badge {
  font-family: var(--font-title);
  font-size: 0.65rem;
  color: var(--accent-color);
  background: color-mix(in srgb, var(--accent-color) 25%, transparent);
  border: 1px solid var(--accent-color);
  padding: 0.1rem 0.4rem;
  border-radius: 4px;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.banner-text {
  font-size: 0.85rem;
  color: var(--text-color);
  margin: 0;
}

.banner-link {
  font-family: var(--font-title);
  font-size: 0.8rem;
  color: var(--accent-color);
  text-decoration: none;
  font-weight: 600;
  transition: opacity 0.3s ease;
}

.banner-link:hover {
  text-decoration: underline;
  opacity: 0.8;
}

.banner-close-btn {
  background: transparent;
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  width: 26px;
  height: 26px;
  border-radius: 50%;
  font-size: 0.8rem;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: all 0.3s ease;
  flex-shrink: 0;
}

.banner-close-btn:hover {
  background: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 8px var(--accent-color);
  transform: rotate(90deg) scale(1.1);
}

.banner-close-btn:active {
  transform: rotate(90deg) scale(0.95);
}

/* Animations d'ouverture et de fermeture de la bannière */
.banner-slide-enter-active,
.banner-slide-leave-active {
  transition: transform 0.4s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.35s ease;
}

.banner-slide-enter-from,
.banner-slide-leave-to {
  transform: translateY(-100%);
  opacity: 0;
}
</style>