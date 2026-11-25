<script setup>
import { computed, nextTick, onMounted, onUnmounted, ref, watch } from 'vue';
import { useI18n } from '@/composables/useI18n.js';

const emit = defineEmits(['height-change'])

const { locale, toggleLocale, t } = useI18n()

const isLightMode = ref(false)
const isMenuOpen = ref(false)
const navRef = ref(null)
const navLinksRef = ref(null)

const navItems = computed(() => [
  { href: '#home', label: t('nav.home') },
  { href: '#skills', label: t('nav.skills') },
  { href: '#news', label: t('nav.news') },
  { href: '#projects', label: t('nav.projects') },
  { href: '#footer', label: t('nav.contact') }
])

const activeSection = ref('#home')
const indicatorStyle = ref({
  transform: 'translateX(0)',
  width: '0px',
  opacity: 0
})

let isScrollingManual = false
let manualScrollTimeout = null
let navResizeObserver = null

// Quand la langue change, les libellés changent de largeur : on recalcule immédiatement la barre lumineuse et la hauteur
watch(locale, () => {
  nextTick(() => {
    updateIndicator(activeSection.value)
    reportHeight()
  })
})

const toggleTheme = () => {
  isLightMode.value = !isLightMode.value
  document.body.classList.toggle('light-mode', isLightMode.value)
}

const toggleMenu = () => {
  isMenuOpen.value = !isMenuOpen.value
}

const reportHeight = () => {
  nextTick(() => {
    if (!navRef.value) return
    const exactHeight = navRef.value.getBoundingClientRect().height
    document.documentElement.style.setProperty('--navbar-height', `${exactHeight}px`)
    emit('height-change', exactHeight)
  })
}

const updateIndicator = (targetHref) => {
  nextTick(() => {
    if (!navLinksRef.value || window.innerWidth <= 868) return
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
  isMenuOpen.value = false
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

  const atBottom = window.innerHeight + window.scrollY >= document.documentElement.scrollHeight - 60
  if (atBottom) {
    if (activeSection.value !== '#footer') {
      activeSection.value = '#footer'
      updateIndicator('#footer')
    }
    return
  }

  const navOffset = (navRef.value?.getBoundingClientRect().height || 64) + 116
  const scrollPosition = window.scrollY + navOffset
  for (let i = navItems.value.length - 1; i >= 0; i--) {
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
  if (window.innerWidth > 868) {
    isMenuOpen.value = false
  }
  updateIndicator(activeSection.value)
}

const onDocumentClick = (e) => {
  if (isMenuOpen.value && navRef.value && !navRef.value.contains(e.target)) {
    isMenuOpen.value = false
  }
}

const onKeydown = (e) => {
  if (e.key === 'Escape' && isMenuOpen.value) {
    isMenuOpen.value = false
  }
}

onMounted(() => {
  reportHeight()
  if (document.fonts && document.fonts.ready) {
    document.fonts.ready.then(reportHeight)
  }
  if (typeof ResizeObserver !== 'undefined' && navRef.value) {
    navResizeObserver = new ResizeObserver(reportHeight)
    navResizeObserver.observe(navRef.value)
  }
  if (window.location.hash && navItems.value.some(item => item.href === window.location.hash)) {
    activeSection.value = window.location.hash
  }
  updateIndicator(activeSection.value)
  window.addEventListener('resize', onResize)
  window.addEventListener('scroll', onScroll, { passive: true })
  document.addEventListener('click', onDocumentClick)
  document.addEventListener('keydown', onKeydown)
})

onUnmounted(() => {
  navResizeObserver?.disconnect()
  window.removeEventListener('resize', onResize)
  window.removeEventListener('scroll', onScroll)
  document.removeEventListener('click', onDocumentClick)
  document.removeEventListener('keydown', onKeydown)
  clearTimeout(manualScrollTimeout)
})
</script>

<template>
  <nav ref="navRef" class="navbar">
    <div class="nav-brand">
      <a href="#home" class="logo-text" @click="onNavClick('#home')">
        <span class="logo-first">Vladislav</span>
        <span class="logo-last">Dumont</span>
      </a>
    </div>

    <ul
      ref="navLinksRef"
      class="nav-links"
      :class="{ 'is-open': isMenuOpen }"
      @mouseleave="onNavLeave"
    >
      <li v-for="item in navItems" :key="item.href">
        <a
          :href="item.href"
          :class="{ active: activeSection === item.href }"
          @click="onNavClick(item.href)"
          @mouseenter="onNavHover(item.href)"
        >{{ item.label }}</a>
      </li>
      <span class="nav-indicator" :style="indicatorStyle"></span>
    </ul>

    <div class="nav-actions">
      <button
        type="button"
        @click="toggleLocale"
        class="lang-btn"
        :title="t('nav.toggleLang')"
        :aria-label="t('nav.langSwitchAria')"
      >
        <span class="lang-text">{{ locale === 'fr' ? 'EN' : 'FR' }}</span>
      </button>

      <button type="button" @click="toggleTheme" class="theme-btn" :title="t('nav.toggleTheme')">
        {{ t('nav.theme') }}
      </button>

      <button
        type="button"
        class="hamburger-btn"
        :class="{ 'is-active': isMenuOpen }"
        @click="toggleMenu"
        :aria-label="t('nav.menuAria')"
        :aria-expanded="isMenuOpen"
      >
        <span class="hamburger-bar"></span>
        <span class="hamburger-bar"></span>
        <span class="hamburger-bar"></span>
      </button>
    </div>
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
  gap: 1rem;
  padding: calc(1rem + env(safe-area-inset-top, 0px)) 2rem 1rem 2rem;
  background-color: var(--nav-bg);
  border-bottom: 1px solid color-mix(in srgb, var(--accent-color) 25%, transparent);
  -webkit-backdrop-filter: blur(10px);
  backdrop-filter: blur(10px);
  z-index: 1000;
  box-sizing: border-box;
  transform: translateZ(0);
  transition: padding 0.3s ease, border-color 0.3s ease, background-color 0.3s ease;
}

.nav-brand {
  flex-shrink: 0;
}

.logo-text {
  font-family: 'Courier New', Courier, monospace;
  font-size: 1.15rem;
  letter-spacing: 2px;
  text-transform: uppercase;
  text-decoration: none;
  white-space: nowrap;
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
  white-space: nowrap;
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

.nav-actions {
  display: flex;
  align-items: center;
  gap: 0.75rem;
  flex-shrink: 0;
}

.lang-btn,
.theme-btn {
  background: transparent;
  border: 2px solid var(--accent-color);
  color: var(--text-color);
  padding: 0.5rem 0.85rem;
  border-radius: 8px;
  cursor: pointer;
  font-family: var(--font-body);
  white-space: nowrap;
  font-weight: 600;
  letter-spacing: 0.5px;
  transition: all 0.3s cubic-bezier(0.16, 1, 0.3, 1);
}

.lang-btn {
  min-width: 44px;
  text-align: center;
}

.lang-btn:hover,
.theme-btn:hover {
  background-color: var(--accent-color);
  color: #fff;
  transform: translateY(-2px);
  box-shadow: 0 0 12px var(--accent-color);
}

.lang-btn:active,
.theme-btn:active {
  transform: translateY(0) scale(0.96);
}

.hamburger-btn {
  display: none;
  background: transparent;
  border: 1px solid var(--accent-color);
  border-radius: 6px;
  width: 38px;
  height: 38px;
  cursor: pointer;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  gap: 5px;
  padding: 0;
  touch-action: manipulation;
  transition: all 0.3s ease;
}

.hamburger-btn:hover {
  background: color-mix(in srgb, var(--accent-color) 15%, transparent);
  box-shadow: 0 0 8px var(--accent-color);
}

.hamburger-bar {
  display: block;
  width: 20px;
  height: 2px;
  background-color: var(--accent-color);
  border-radius: 2px;
  transition: transform 0.3s ease, opacity 0.3s ease;
}

.hamburger-btn.is-active .hamburger-bar:nth-child(1) {
  transform: translateY(7px) rotate(45deg);
}

.hamburger-btn.is-active .hamburger-bar:nth-child(2) {
  opacity: 0;
}

.hamburger-btn.is-active .hamburger-bar:nth-child(3) {
  transform: translateY(-7px) rotate(-45deg);
}

@media (max-width: 1024px) and (min-width: 869px) {
  .navbar {
    padding: calc(0.9rem + env(safe-area-inset-top, 0px)) 1.5rem 0.9rem 1.5rem;
  }

  .nav-links {
    gap: 1.25rem;
  }

  .nav-links a {
    font-size: 0.92rem;
  }
}

@media (max-width: 868px) {
  .navbar {
    padding: calc(0.85rem + env(safe-area-inset-top, 0px)) 1.5rem 0.85rem 1.5rem;
  }

  .hamburger-btn {
    display: flex;
  }

  .nav-indicator {
    display: none;
  }

  .nav-links {
    position: fixed;
    top: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) - 0.5px);
    left: 0;
    width: 100%;
    background-color: var(--nav-bg);
    border-bottom: 2px solid var(--accent-color);
    box-shadow: 0 12px 30px rgba(0, 0, 0, 0.6);
    flex-direction: column;
    gap: 0;
    padding: 0.5rem 0;
    max-height: 0;
    overflow: hidden;
    opacity: 0;
    pointer-events: none;
    transition: max-height 0.35s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.3s ease;
    -webkit-backdrop-filter: blur(12px);
    backdrop-filter: blur(12px);
    box-sizing: border-box;
  }

  .nav-links.is-open {
    max-height: 380px;
    opacity: 1;
    pointer-events: auto;
  }

  .nav-links li {
    width: 100%;
    text-align: center;
  }

  .nav-links a {
    display: block;
    padding: 0.9rem 1.5rem;
    font-size: 1.05rem;
    width: 100%;
    box-sizing: border-box;
    border-left: 3px solid transparent;
    transition: background 0.2s ease, border-color 0.2s ease, color 0.2s ease;
  }

  .nav-links a:hover,
  .nav-links a.active {
    background: color-mix(in srgb, var(--accent-color) 15%, transparent);
    border-left-color: var(--accent-color);
    color: var(--accent-color);
  }
}

@media (max-width: 480px) {
  .navbar {
    padding: calc(0.75rem + env(safe-area-inset-top, 0px)) 1rem 0.75rem 1rem;
    gap: 0.5rem;
  }

  .logo-text {
    font-size: 1.15rem;
    letter-spacing: 2px;
  }

  .lang-btn,
  .theme-btn {
    padding: 0.4rem 0.6rem;
    font-size: 0.78rem;
  }

  .hamburger-btn {
    width: 34px;
    height: 34px;
  }

  .hamburger-bar {
    width: 18px;
  }

  .hamburger-btn.is-active .hamburger-bar:nth-child(1) {
    transform: translateY(7px) rotate(45deg);
  }

  .hamburger-btn.is-active .hamburger-bar:nth-child(3) {
    transform: translateY(-7px) rotate(-45deg);
  }
}
</style>