import { ref, watch } from 'vue'
import { messages } from './i18nTranslations.js'

const STORAGE_KEY = 'portfolio_lang_v1'

const getInitialLocale = () => {
  if (typeof window === 'undefined') return 'fr'

  try {
    const saved = localStorage.getItem(STORAGE_KEY)
    if (saved === 'fr' || saved === 'en') {
      return saved
    }
  } catch {
    // ignore localStorage errors (e.g. privacy mode)
  }

  const browserLang = typeof navigator !== 'undefined'
    ? (navigator.language || navigator.userLanguage || '')
    : ''

  if (browserLang.toLowerCase().startsWith('en')) {
    return 'en'
  }
  return 'fr'
}

// Global reactive state shared across components
const locale = ref(getInitialLocale())

const syncDocumentAndStorage = (lang) => {
  if (typeof document !== 'undefined') {
    document.documentElement.lang = lang
  }
  if (typeof window !== 'undefined') {
    try {
      localStorage.setItem(STORAGE_KEY, lang)
    } catch {
      // ignore localStorage errors
    }
  }
}

// Immediately sync initial locale
syncDocumentAndStorage(locale.value)

watch(locale, (newVal) => {
  syncDocumentAndStorage(newVal)
})

export function useI18n() {
  const toggleLocale = () => {
    locale.value = locale.value === 'fr' ? 'en' : 'fr'
  }

  const resolvePath = (obj, path) => {
    if (!obj || typeof obj !== 'object') return undefined
    const keys = path.split('.')
    let current = obj
    for (const k of keys) {
      if (current === undefined || current === null) return undefined
      current = current[k]
    }
    return current
  }

  const t = (key, params = {}) => {
    const currentLang = locale.value
    let val = resolvePath(messages[currentLang], key)

    // Fallback to 'fr' if absent in 'en' or missing in current
    if (val === undefined || val === null) {
      val = resolvePath(messages.fr, key)
    }

    if (val === undefined || val === null) {
      return key
    }

    if (typeof val === 'string' && Object.keys(params).length > 0) {
      return val.replace(/\{(\w+)\}/g, (_, matchKey) => {
        return params[matchKey] !== undefined ? params[matchKey] : `{${matchKey}}`
      })
    }

    return val
  }

  return {
    locale,
    toggleLocale,
    t
  }
}
