<script setup>
import { ref, onMounted, onUnmounted, nextTick } from 'vue'

const emit = defineEmits(['height-change'])

const isLightMode = ref(false)
const navRef = ref(null)
const navLinksRef = ref(null)

const navItems = [
  { href: '#home', label: 'Accueil' },
  { href: '#skills', label: 'Compétences' },
  { href: '#news', label: 'News' },
  { href: '#projects', label: 'Projets' },
  { href: '#footer', label: 'Contact' }
]

const activeSection = ref('#home')
const indicatorStyle = ref({
  transform: 'translateX(0)',
  width: '0px',
  opacity: 0
})

let isScrollingManual = false
let manualScrollTimeout = null

const toggleTheme = () => {
  isLightMode.value = !isLightMode.value
  document.body.classList.toggle('light-mode', isLightMode.value)
}

const reportHeight = () => {
  nextTick(() => {
    const height = navRef.value?.offsetHeight || 64
    emit('height-change', height)
  })
}

const updateIndicator = (targetHref) => {
  nextTick(() => {
    if (!navLinksRef.value) return
    const activeLink = navLinksRef.value.querySelector(`a[href="${targetHref}"]`)
    if (activeLink) {
      const parentRect = navLinksRef.value.getBoundingClientRect()
      const linkRect = activeLink.getBoundingClientRect()
      const offsetLeft = linkRect.left - parentRect.left
      indicatorStyle.value = {
        transform: `translateX(${offsetLeft}px)`,
        width: `${linkRect.width}px`,
        opacity: 1
      }
    }
  })
}

const onNavClick = (href) => {
  activeSection.value = href
  updateIndicator(href)
  isScrollingManual = true
  clearTimeout(manualScrollTimeout)
  manualScrollTimeout = setTimeout(() => {
    isScrollingManual = false
  }, 800)
}

const onNavHover = (href) => {
  updateIndicator(href)
}

const onNavLeave = () => {
  updateIndicator(activeSection.value)
}

const onScroll = () => {
  if (isScrollingManual) return

  // Si on est tout en bas de la page, sélectionner le contact
  const atBottom = window.innerHeight + window.scrollY >= document.documentElement.scrollHeight - 60
  if (atBottom) {
    if (activeSection.value !== '#footer') {
      activeSection.value = '#footer'
      updateIndicator('#footer')
    }
    return
  }

  // Détection de la section visible
  const scrollPosition = window.scrollY + 180
  for (let i = navItems.length - 1; i >= 0; i--) {
    const item = navItems[i]
    const el = document.querySelector(item.href)
    if (el) {
      if (scrollPosition >= el.offsetTop) {
        if (activeSection.value !== item.href) {
          activeSection.value = item.href
          updateIndicator(item.href)
        }
        break
      }
    }
  }
}

const onResize = () => {
  reportHeight()
  updateIndicator(activeSection.value)
}

onMounted(() => {
  reportHeight()
  if (window.location.hash && navItems.some(item => item.href === window.location.hash)) {
    activeSection.value = window.location.hash
  }
  updateIndicator(activeSection.value)
  window.addEventListener('resize', onResize)
  window.addEventListener('scroll', onScroll, { passive: true })
})

onUnmounted(() => {
  window.removeEventListener('resize', onResize)
  window.removeEventListener('scroll', onScroll)
  clearTimeout(manualScrollTimeout)
})
</script>

<template>
  <nav ref="navRef" class="navbar">
    <div class="nav-brand">
      <span class="logo-text">
        <span class="logo-first">Vladislav</span>
        <span class="logo-last">Dumont</span>
      </span>
    </div>

    <ul ref="navLinksRef" class="nav-links" @mouseleave="onNavLeave">
      <li v-for="item in navItems" :key="item.href">
        <a 
          :href="item.href"
          :class="{ 'active': activeSection === item.href }"
          @click="onNavClick(item.href)"
          @mouseenter="onNavHover(item.href)"
        >{{ item.label }}</a>
      </li>
      <span class="nav-indicator" :style="indicatorStyle"></span>
    </ul>

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
  font-family: 'Courier New', Courier, monospace;
  font-size: 1.15rem;
  letter-spacing: 2px;
  text-transform: uppercase;
}

.logo-first {
  color: var(--text-color);
  font-weight: 400;
}

.logo-last {
  color: var(--accent-color);
  font-weight: 700;
  text-shadow: 0 0 10px color-mix(in srgb, var(--accent-color) 40%, transparent);
}

.nav-links {
  position: relative;
  list-style: none;
  display: flex;
  gap: 2rem;
  margin: 0;
  padding: 0.4rem 0;
  align-items: center;
}

.nav-links a {
  text-decoration: none;
  color: var(--text-color);
  font-weight: 500;
  padding: 0.3rem 0.2rem;
  display: inline-block;
  transition: color 0.3s ease, text-shadow 0.3s ease;
  position: relative;
}

.nav-links a.active {
  color: var(--accent-color);
  font-weight: 600;
  text-shadow: 0 0 10px color-mix(in srgb, var(--accent-color) 40%, transparent);
}

.nav-links a:hover {
  color: var(--accent-color);
}

.nav-indicator {
  position: absolute;
  bottom: 0;
  left: 0;
  height: 2.5px;
  background: var(--accent-color);
  border-radius: 3px;
  box-shadow: 0 0 8px var(--accent-color), 0 0 16px var(--accent-color);
  transition: transform 0.35s cubic-bezier(0.16, 1, 0.3, 1), width 0.35s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.25s ease;
  pointer-events: none;
}

.theme-btn {
  background: transparent;
  border: 2px solid var(--accent-color);
  color: var(--text-color);
  padding: 0.5rem 1rem;
  border-radius: 8px;
  cursor: pointer;
  font-family: var(--font-body);
  transition: all 0.3s cubic-bezier(0.16, 1, 0.3, 1);
}

.theme-btn:hover {
  background-color: var(--accent-color);
  color: #fff;
  transform: translateY(-2px);
  box-shadow: 0 0 12px var(--accent-color);
}

.theme-btn:active {
  transform: translateY(0) scale(0.96);
}
</style>