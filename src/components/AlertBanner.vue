<script setup>
import { nextTick, onMounted, onUnmounted, ref, watch } from 'vue';
import { useI18n } from '@/composables/useI18n.js';

const emit = defineEmits(['visibility-change', 'height-change'])

const { t } = useI18n()

const isVisible = ref(false)
const bannerRef = ref(null)
const bannerKey = 'portfolio_alert_v1'
let resizeObserver = null

const reportHeight = () => {
  nextTick(() => {
    const height = isVisible.value && bannerRef.value
      ? bannerRef.value.getBoundingClientRect().height
      : 0
    document.documentElement.style.setProperty('--alert-height', `${height}px`)
    emit('height-change', height)
  })
}

onMounted(() => {
  const dismissed = localStorage.getItem(bannerKey)
  isVisible.value = !dismissed
  emit('visibility-change', isVisible.value)
  reportHeight()

  if (document.fonts && document.fonts.ready) {
    document.fonts.ready.then(reportHeight)
  }

  if (typeof ResizeObserver !== 'undefined') {
    resizeObserver = new ResizeObserver(reportHeight)
    if (bannerRef.value) resizeObserver.observe(bannerRef.value)
  }
})

onUnmounted(() => {
  resizeObserver?.disconnect()
})

watch(isVisible, (val) => {
  emit('visibility-change', val)
  reportHeight()
  nextTick(() => {
    if (val && bannerRef.value && resizeObserver) {
      resizeObserver.observe(bannerRef.value)
    }
  })
})

const closeBanner = () => {
  isVisible.value = false
  localStorage.setItem(bannerKey, 'true')
}

const onAfterLeave = () => {
  document.documentElement.style.setProperty('--alert-height', '0px')
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
        <span class="banner-badge">{{ t('alert.badge') }}</span>
        <p class="banner-text">
          {{ t('alert.textPrefix') }} <strong>{{ t('alert.textStrong') }}</strong> {{ t('alert.textSuffix') }}
        </p>
        <a href="#news" class="banner-link">{{ t('alert.link') }}</a>
      </div>
      <button
        type="button"
        @click="closeBanner"
        class="banner-close-btn"
        :title="t('alert.closeTitle')"
        :aria-label="t('alert.closeAria')"
      >
        ✕
      </button>
    </div>
  </Transition>
</template>

<style scoped>
.alert-banner {
  position: fixed;
  top: calc(var(--navbar-height, 64px) - 0.5px);
  left: 0;
  width: 100%;
  background: color-mix(in srgb, var(--accent-color) 15%, var(--nav-bg));
  border-bottom: 1px solid var(--accent-color);
  padding: 0.65rem 2rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 1rem;
  z-index: 999;
  box-shadow: 0 4px 14px rgba(0, 0, 0, 0.35);
  -webkit-backdrop-filter: blur(10px);
  backdrop-filter: blur(10px);
  box-sizing: border-box;
  transform: translateZ(0);
}

.banner-content {
  display: flex;
  align-items: center;
  gap: 1rem;
  flex: 1;
  justify-content: center;
  flex-wrap: wrap;
  text-align: center;
  min-width: 0;
}

.banner-badge {
  font-family: var(--font-title);
  font-size: 0.65rem;
  color: var(--accent-color);
  background: color-mix(in srgb, var(--accent-color) 25%, transparent);
  border: 1px solid var(--accent-color);
  padding: 0.15rem 0.45rem;
  border-radius: 4px;
  text-transform: uppercase;
  letter-spacing: 1px;
  flex-shrink: 0;
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
  white-space: nowrap;
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
  width: 28px;
  height: 28px;
  border-radius: 50%;
  font-size: 0.8rem;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  touch-action: manipulation;
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

.banner-slide-enter-active,
.banner-slide-leave-active {
  transition: transform 0.4s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.35s ease;
}

.banner-slide-enter-from,
.banner-slide-leave-to {
  transform: translateY(-100%);
  opacity: 0;
}

@media (max-width: 768px) {
  .alert-banner {
    padding: 0.55rem 1rem;
    gap: 0.75rem;
  }

  .banner-content {
    justify-content: flex-start;
    text-align: left;
    gap: 0.35rem 0.65rem;
  }

  .banner-text {
    font-size: 0.78rem;
    line-height: 1.35;
  }

  .banner-link {
    font-size: 0.75rem;
  }
}

@media (max-width: 480px) {
  .alert-banner {
    padding: 0.5rem 0.75rem;
  }

  .banner-badge {
    font-size: 0.6rem;
    padding: 0.1rem 0.35rem;
  }

  .banner-text {
    font-size: 0.74rem;
  }
}
</style>