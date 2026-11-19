<script setup>
import { ref, computed, onMounted, onUnmounted } from 'vue'

const newsList = ref([
  {
    date: "18 Novembre 2026",
    category: "IA",
    title: "Mon avis sur l'utilisation de l'IA",
    summary: "Pour le premier article de mon Portfolio, je vous propose mon point de vue sur l'utilisation de l'IA dans le domaine professionnel et scolaire",
    content: "L'IA est devenue omniprésente dans le monde du travail et la question qui revient souvent est 'Est-ce que nous sommes remplacables par celle-ci ?'. Et bien de mon point de vue, pas forcément ! L'arrivée de l'IA peut-être comparable à celle de l'électricité ou encore celle du train à vapeur, ces technologies ont remplacé des emplois mais en ont créé d'autres. De plus, l'IA ne se débrouille pas d'elle même, il faut savoir s'en servir. De mon point de vue, il faut la voir comme un assistant qui connait beaucoup de documentation et qui code très vite ce qui peut faire gagner beaucoup de temps. Cependant elle a tendance à un peu 'mixer' tout ce qu'elle trouve et peut donc par ailleurs faire des erreurs. Ce qui est le plus souvent reproché par mes professeurs n'est pas l'utilisation de l'IA en elle même mais le fait qu'on valide son travail sans relecture et sans le comprendre. Et c'est là qu'est le point le plus important, il faut savoir 'prompter' correctement et comprendre le code produit afin de le corriger si besoin. En conclusion, pour ma part je suis toujours avide de savoir ce qui a été produit pour essayer de le reproduire par la suite et l'utilisation de l'IA permet de m'aider à réaliser beaucoup de chose tout en me laissant du temps pour les études (ce Portfolio est un parfait exemple).",
    images: ["/AI.jpg"]
  }
])

const sortedNews = computed(() => {
  return [...newsList.value].sort((a, b) => new Date(b.date) - new Date(a.date))
})

const activeArticle = ref(null)

const openArticleModal = (article) => {
  activeArticle.value = article
}

const closeArticleModal = () => {
  activeArticle.value = null
}

const onKeydown = (e) => {
  if (e.key === 'Escape' && activeArticle.value) {
    closeArticleModal()
  }
}

onMounted(() => {
  document.addEventListener('keydown', onKeydown)
})

onUnmounted(() => {
  document.removeEventListener('keydown', onKeydown)
})
</script>

<template>
  <section id="news" class="news-section">
    <h2 v-reveal>News</h2>

    <div class="news-grid">
      <article
        v-for="item in sortedNews"
        :key="item.title"
        v-reveal="{ delay: 100 }"
        class="news-card"
        @click="openArticleModal(item)"
      >
        <div class="news-header-meta">
          <span class="news-category">{{ item.category }}</span>
          <span class="news-date">{{ item.date }}</span>
        </div>

        <h3>{{ item.title }}</h3>
        <p>{{ item.summary }}</p>

        <div class="news-read-more">
          <span>Lire le log complet ➔</span>
        </div>
      </article>
    </div>

    <Transition name="modal">
      <div class="modal-backdrop" v-if="activeArticle" @click="closeArticleModal">
        <div class="modal-content" @click.stop>
          <button
            type="button"
            class="modal-close-btn"
            @click="closeArticleModal"
            aria-label="Fermer l'article"
          >
            ✕
          </button>

          <div class="modal-header">
            <div class="modal-meta-row">
              <span class="news-category">{{ activeArticle.category }}</span>
              <span class="news-date">{{ activeArticle.date }}</span>
            </div>
            <h3>{{ activeArticle.title }}</h3>
          </div>

          <div class="modal-body">
            <div class="modal-images-box" v-if="activeArticle.images && activeArticle.images.length">
              <img :src="activeArticle.images[0]" :alt="activeArticle.title" class="modal-img" />
            </div>

            <div class="modal-details">
              <h4>Contenu de l'article</h4>
              <p>{{ activeArticle.content }}</p>
            </div>
          </div>
        </div>
      </div>
    </Transition>
  </section>
</template>

<style scoped>
.news-section {
  padding: 4rem 2rem;
  max-width: 1200px;
  margin: 0 auto;
  scroll-margin-top: calc(var(--navbar-height, 64px) + var(--alert-height, 0px) + 1rem);
  box-sizing: border-box;
}

.news-section > h2 {
  font-family: var(--font-title);
  font-size: 2rem;
  color: var(--accent-color);
  margin-bottom: 2rem;
  text-align: left;
}

.news-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
  gap: 2rem;
}

.news-card {
  background: var(--nav-bg);
  border: 1px solid var(--accent-color);
  border-radius: 12px;
  padding: 2rem;
  display: flex;
  flex-direction: column;
  gap: 1rem;
  box-shadow: 0 0 15px rgba(0, 0, 0, 0.2);
  transition: all 0.3s ease;
  cursor: pointer;
  box-sizing: border-box;
  text-align: left;
  min-width: 0;
}

.news-card:hover {
  box-shadow: 0 0 20px var(--accent-color);
  transform: translateY(-3px);
}

.news-header-meta {
  display: flex;
  justify-content: space-between;
  align-items: center;
  gap: 0.5rem;
  flex-wrap: wrap;
}

.news-category {
  font-family: var(--font-title);
  font-size: 0.7rem;
  color: var(--accent-color);
  background: color-mix(in srgb, var(--accent-color) 15%, transparent);
  border: 1px solid var(--accent-color);
  padding: 0.1rem 0.5rem;
  border-radius: 4px;
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.news-date {
  font-size: 0.75rem;
  opacity: 0.7;
  font-family: var(--font-title);
}

.news-card h3 {
  font-family: var(--font-title);
  font-size: 1.2rem;
  color: var(--text-color);
  margin: 0;
  overflow-wrap: anywhere;
}

.news-card p {
  font-size: 0.9rem;
  opacity: 0.85;
  margin: 0;
  line-height: 1.5;
  color: var(--text-color);
}

.news-read-more {
  margin-top: auto;
  font-family: var(--font-title);
  font-size: 0.8rem;
  color: var(--accent-color);
  letter-spacing: 0.5px;
}

.modal-backdrop {
  position: fixed;
  inset: 0;
  background: rgba(0, 0, 0, 0.8);
  backdrop-filter: blur(5px);
  z-index: 1000;
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 2rem;
  box-sizing: border-box;
}

.modal-content {
  background: var(--nav-bg);
  border: 2px solid var(--accent-color);
  border-radius: 14px;
  width: 100%;
  max-width: 800px;
  max-height: 90vh;
  overflow-y: auto;
  overscroll-behavior: contain;
  -webkit-overflow-scrolling: touch;
  padding: 2.5rem;
  position: relative;
  box-shadow: 0 0 30px var(--accent-color);
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  box-sizing: border-box;
}

.modal-header {
  padding-right: 3rem;
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  text-align: left;
}

.modal-meta-row {
  display: flex;
  align-items: center;
  gap: 1rem;
  flex-wrap: wrap;
}

.modal-close-btn {
  position: absolute;
  top: 1.5rem;
  right: 1.5rem;
  background: transparent;
  border: 1px solid var(--accent-color);
  color: var(--accent-color);
  width: 35px;
  height: 35px;
  border-radius: 50%;
  font-size: 1rem;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: all 0.3s ease;
  z-index: 10;
}

.modal-close-btn:hover {
  background: var(--accent-color);
  color: #ffffff;
  box-shadow: 0 0 10px var(--accent-color);
  transform: rotate(90deg) scale(1.1);
}

.modal-close-btn:active {
  transform: rotate(90deg) scale(0.95);
}

.modal-header h3 {
  font-family: var(--font-title);
  font-size: 1.6rem;
  color: var(--text-color);
  margin: 0;
  text-align: left;
  overflow-wrap: anywhere;
}

.modal-body {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  text-align: left;
}

.modal-images-box {
  width: 100%;
  height: 280px;
  background: color-mix(in srgb, var(--accent-color) 5%, rgba(0, 0, 0, 0.8));
  border: 1px solid var(--accent-color);
  border-radius: 8px;
  overflow: hidden;
  display: flex;
  align-items: center;
  justify-content: center;
}

.modal-img {
  width: 100%;
  height: 100%;
  object-fit: contain;
}

.modal-details {
  background: color-mix(in srgb, var(--text-color) 3%, transparent);
  border: 1px solid color-mix(in srgb, var(--accent-color) 30%, transparent);
  border-left: 3px solid var(--accent-color);
  border-radius: 8px;
  padding: 1.2rem;
}

.modal-details h4 {
  font-family: var(--font-title);
  font-size: 0.9rem;
  color: var(--accent-color);
  margin-bottom: 0.5rem;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.modal-details p {
  font-size: 0.95rem;
  line-height: 1.6;
  opacity: 0.9;
  color: var(--text-color);
  margin: 0;
  overflow-wrap: anywhere;
}

.modal-enter-active,
.modal-leave-active {
  transition: opacity 0.3s cubic-bezier(0.16, 1, 0.3, 1);
}

.modal-enter-from,
.modal-leave-to {
  opacity: 0;
}

.modal-enter-active .modal-content,
.modal-leave-active .modal-content {
  transition: transform 0.35s cubic-bezier(0.16, 1, 0.3, 1), opacity 0.3s ease;
}

.modal-enter-from .modal-content,
.modal-leave-to .modal-content {
  opacity: 0;
  transform: scale(0.92) translateY(20px);
}

@media (max-width: 1024px) and (min-width: 769px) {
  .news-section {
    padding: 3.5rem 1.75rem;
  }

  .news-grid {
    grid-template-columns: repeat(auto-fit, minmax(270px, 1fr));
    gap: 1.5rem;
  }
}

@media (max-width: 768px) {
  .news-section {
    padding: 3rem 1.25rem;
  }

  .news-section > h2 {
    font-size: clamp(1.4rem, 5vw, 1.8rem);
    margin-bottom: 1.5rem;
  }

  .news-grid {
    grid-template-columns: 1fr;
    gap: 1.25rem;
  }

  .news-card {
    padding: 1.5rem;
  }

  .modal-backdrop {
    padding: 0.75rem;
  }

  .modal-content {
    padding: 1.75rem 1.25rem;
    max-height: 94vh;
  }

  .modal-header h3 {
    font-size: 1.3rem;
  }

  .modal-images-box {
    height: 200px;
  }
}

@media (max-width: 480px) {
  .news-section {
    padding: 2.5rem 1rem;
  }

  .news-card {
    padding: 1.2rem;
  }

  .news-card h3 {
    font-size: 1.1rem;
  }

  .news-card p {
    font-size: 0.85rem;
  }

  .modal-content {
    padding: 1.5rem 1rem;
  }

  .modal-close-btn {
    top: 1rem;
    right: 1rem;
    width: 30px;
    height: 30px;
    font-size: 0.85rem;
  }

  .modal-images-box {
    height: 170px;
  }
}
</style>