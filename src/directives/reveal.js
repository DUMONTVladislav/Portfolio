export const vReveal = {
  mounted(el, binding) {
    el.classList.add('reveal-on-scroll')

    if (binding.value?.delay) {
      el.style.transitionDelay = `${binding.value.delay}ms`
    }

    if (!('IntersectionObserver' in window)) {
      el.classList.add('is-revealed')
      return
    }

    const observer = new IntersectionObserver(
      (entries, obs) => {
        entries.forEach((entry) => {
          if (entry.isIntersecting) {
            entry.target.classList.add('is-revealed')
            obs.unobserve(entry.target)
          }
        })
      },
      {
        threshold: 0.12,
        rootMargin: '0px 0px -40px 0px'
      }
    )

    observer.observe(el)
    el._scrollObserver = observer
  },
  unmounted(el) {
    if (el._scrollObserver) {
      el._scrollObserver.disconnect()
      delete el._scrollObserver
    }
  }
}
