<script setup>
import { useI18n } from '@/composables/useI18n.js'

const { t } = useI18n()
</script>

<template>
  <footer id="footer" class="footer-section">
    <div v-reveal class="footer-container">
      <div class="footer-info">
        <h3>{{ t('footer.contactTitle') }}</h3>
        <p>{{ t('footer.subtitle') }}</p>
        <p>{{ t('footer.university') }}</p>
        <p>
          {{ t('footer.emailLabel') }}
          <a href="mailto:vladislav.dumont@gmail.com" class="footer-link">vladislav.dumont@gmail.com</a>
        </p>
        <div class="footer-socials">
          <a
            href="https://github.com/DUMONTVladislav"
            target="_blank"
            rel="noopener noreferrer"
            class="footer-link"
          >
            GitHub
          </a>
          <span class="social-separator">•</span>
          <a
            href="https://www.linkedin.com/in/vladislav-dumont-2301753b3"
            target="_blank"
            rel="noopener noreferrer"
            class="footer-link"
          >
            LinkedIn
          </a>
        </div>
      </div>

      <div class="footer-legal">
        <h3>{{ t('footer.legalTitle') }}</h3>
        <p>{{ t('footer.legalP1') }}</p>
        <p>{{ t('footer.legalP2') }}</p>
      </div>
    </div>
  </footer>
</template>

<style scoped>
.footer-section {
  background: var(--nav-bg);
  border-top: 1px solid var(--accent-color);
  padding: 3rem 2rem;
  margin-top: 4rem;
  box-sizing: border-box;
  overflow-x: clip;
}

.footer-container {
  max-width: 1200px;
  margin: 0 auto;
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 3rem;
  text-align: left;
}

.footer-info,
.footer-legal {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  min-width: 0;
}

.footer-section h3 {
  font-family: var(--font-title);
  font-size: 1.1rem;
  color: var(--accent-color);
  margin-bottom: 0.5rem;
  text-transform: uppercase;
  letter-spacing: 1px;
}

.footer-section p {
  font-size: 0.85rem;
  opacity: 0.8;
  margin: 0;
  line-height: 1.45;
  color: var(--text-color);
}

.footer-socials {
  display: flex;
  gap: 0.5rem;
  align-items: center;
  flex-wrap: wrap;
  margin-top: 0.35rem;
}

.social-separator {
  color: var(--accent-color);
  opacity: 0.6;
}

.footer-link {
  color: var(--accent-color);
  text-decoration: none;
  overflow-wrap: anywhere;
  transition: opacity 0.3s ease;
}

.footer-link:hover {
  text-decoration: underline;
  opacity: 1;
}

@media (max-width: 1024px) {
  .footer-section {
    padding: 2.75rem 1.75rem;
    margin-top: 3.5rem;
  }

  .footer-container {
    gap: 2rem;
  }
}

@media (max-width: 768px) {
  .footer-section {
    padding: 2.5rem 1.25rem;
    margin-top: 3rem;
  }

  .footer-container {
    grid-template-columns: 1fr;
    gap: 2rem;
    text-align: center;
  }

  .footer-socials {
    justify-content: center;
    gap: 0.65rem;
  }

  .footer-socials .footer-link {
    padding: 0.25rem 0.4rem;
  }
}

@media (max-width: 480px) {
  .footer-section {
    padding: 2rem 1rem;
    margin-top: 2.5rem;
  }

  .footer-container {
    gap: 1.75rem;
  }

  .footer-section h3 {
    font-size: 1rem;
  }

  .footer-section p {
    font-size: 0.8rem;
  }
}
</style>