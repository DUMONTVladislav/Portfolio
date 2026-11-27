import { nextTick, onUnmounted, watch } from 'vue'

const FOCUSABLE_SELECTOR = [
  'a[href]',
  'button:not([disabled])',
  'input:not([disabled])',
  'select:not([disabled])',
  'textarea:not([disabled])',
  '[tabindex]:not([tabindex="-1"])'
].join(', ')

const getFocusableElements = (container) => {
  if (!container) return []
  return Array.from(container.querySelectorAll(FOCUSABLE_SELECTOR)).filter((el) => {
    return el.getClientRects().length > 0 && window.getComputedStyle(el).visibility !== 'hidden'
  })
}

let activeLockCount = 0
let savedBodyOverflow = ''

const lockScroll = () => {
  if (typeof document === 'undefined') return
  if (activeLockCount === 0) {
    savedBodyOverflow = document.body.style.overflow
    document.body.style.overflow = 'hidden'
  }
  activeLockCount++
}

const unlockScroll = () => {
  if (typeof document === 'undefined') return
  if (activeLockCount > 0) {
    activeLockCount--
    if (activeLockCount === 0) {
      document.body.style.overflow = savedBodyOverflow
    }
  }
}

export function useFocusTrap(containerRef, isOpen, options = {}) {
  const { isSuspended } = options
  let previousFocusedElement = null
  let isLockedHere = false

  const onKeydown = (e) => {
    if (e.key !== 'Tab') return
    if (!isOpen.value || isSuspended?.value) return

    const container = containerRef.value
    if (!container) return

    const focusable = getFocusableElements(container)
    if (focusable.length === 0) {
      e.preventDefault()
      container.focus({ preventScroll: true })
      return
    }

    const first = focusable[0]
    const last = focusable[focusable.length - 1]
    const active = document.activeElement

    if (e.shiftKey) {
      if (active === first || !container.contains(active)) {
        e.preventDefault()
        last.focus({ preventScroll: true })
      }
    } else {
      if (active === last || !container.contains(active)) {
        e.preventDefault()
        first.focus({ preventScroll: true })
      }
    }
  }

  watch(
    isOpen,
    (open) => {
      if (open) {
        previousFocusedElement = document.activeElement instanceof HTMLElement
          ? document.activeElement
          : null

        if (!isLockedHere) {
          lockScroll()
          isLockedHere = true
        }

        document.addEventListener('keydown', onKeydown)

        nextTick(() => {
          const container = containerRef.value
          if (!container) return
          const focusable = getFocusableElements(container)
          if (focusable.length > 0) {
            focusable[0].focus({ preventScroll: true })
          } else {
            container.focus({ preventScroll: true })
          }
        })
      } else {
        document.removeEventListener('keydown', onKeydown)
        if (isLockedHere) {
          unlockScroll()
          isLockedHere = false
        }

        nextTick(() => {
          if (previousFocusedElement && typeof previousFocusedElement.focus === 'function') {
            previousFocusedElement.focus({ preventScroll: true })
          }
          previousFocusedElement = null
        })
      }
    }
  )

  onUnmounted(() => {
    document.removeEventListener('keydown', onKeydown)
    if (isLockedHere) {
      unlockScroll()
      isLockedHere = false
    }
  })
}
