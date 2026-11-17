<script setup>
import { ref, onMounted, onBeforeUnmount, nextTick } from 'vue'
import { CandyCrushEngine } from '@/games/candy-crush/candyCrushEngine.js'

const props = defineProps({
  allowExpand: {
    type: Boolean,
    default: false
  }
})

const emit = defineEmits(['expand'])

const terminalBodyRef = ref(null)
const inputRef = ref(null)

const lines = ref([]) // Tableau de lignes : chaque ligne est un tableau de { text, color }
const currentColor = ref(0)
const isWaitingInput = ref(false)
const currentPrompt = ref('')
const currentPromptMeta = ref(null)
const userInput = ref('')
const isGameOver = ref(false)

let engine = null
let inputResolver = null

const scrollToBottom = () => {
  nextTick(() => {
    if (terminalBodyRef.value) {
      terminalBodyRef.value.scrollTop = terminalBodyRef.value.scrollHeight
    }
  })
}

const addText = (text, isNewline = false) => {
  const parts = String(text).split('\n')
  for (let i = 0; i < parts.length; i++) {
    if (i > 0) {
      lines.value.push([])
    }
    if (parts[i].length > 0) {
      if (lines.value.length === 0) {
        lines.value.push([])
      }
      const currentLine = lines.value[lines.value.length - 1]
      currentLine.push({
        text: parts[i],
        color: currentColor.value
      })
    }
  }
  if (isNewline) {
    lines.value.push([])
  }
  scrollToBottom()
}

const io = {
  print: (str) => {
    addText(str, false)
  },
  println: (str = '') => {
    addText(str, true)
  },
  clear: () => {
    lines.value = [[]]
    scrollToBottom()
  },
  setColor: (code) => {
    currentColor.value = code
  },
  readLine: (promptStr = '', meta = null) => {
    if (promptStr) {
      addText(promptStr, false)
    }
    currentPrompt.value = promptStr
    currentPromptMeta.value = meta
    isWaitingInput.value = true
    userInput.value = ''
    scrollToBottom()
    nextTick(() => {
      focusInput()
    })

    return new Promise((resolve) => {
      inputResolver = resolve
    })
  }
}

const focusInput = () => {
  if (inputRef.value) {
    inputRef.value.focus()
  }
}

const submit = (valToSubmit = null) => {
  if (!isWaitingInput.value || !inputResolver) return

  const value = valToSubmit !== null ? String(valToSubmit) : userInput.value
  // Afficher la commande entrée par l'utilisateur
  addText(value, true)

  isWaitingInput.value = false
  currentPrompt.value = ''
  currentPromptMeta.value = null
  userInput.value = ''

  const resolve = inputResolver
  inputResolver = null
  resolve(value)
}

const restartGame = () => {
  if (engine) {
    engine.abort()
  }
  if (inputResolver) {
    const resolve = inputResolver
    inputResolver = null
    resolve('0')
  }
  isGameOver.value = false
  lines.value = [[]]
  engine = new CandyCrushEngine(io)
  engine.start().then(() => {
    isGameOver.value = true
  })
}

const getColorClass = (code) => {
  switch (code) {
    case 31: return 'ansi-red'
    case 32: return 'ansi-green'
    case 33: return 'ansi-yellow'
    case 34: return 'ansi-blue'
    case 35: return 'ansi-magenta'
    case 36: return 'ansi-cyan'
    case 37: return 'ansi-white'
    default: return 'ansi-reset'
  }
}

onMounted(() => {
  restartGame()
})

onBeforeUnmount(() => {
  if (engine) {
    engine.abort()
  }
  if (inputResolver) {
    inputResolver('0')
    inputResolver = null
  }
})
</script>

<template>
  <div class="candy-terminal-wrapper" @click="focusInput">
    <!-- Barre supérieure de la fenêtre de terminal -->
    <div class="terminal-header">
      <div class="terminal-dots">
        <span class="dot red"></span>
        <span class="dot yellow"></span>
        <span class="dot green"></span>
      </div>
      <div class="terminal-title">
        <span class="terminal-icon">&gt;_</span> candy_crush.cpp
      </div>
      <div class="terminal-actions">
        <button 
          type="button" 
          class="terminal-action-btn" 
          @click.stop="restartGame" 
          title="Relancer le jeu"
        >
          ↺ Menu
        </button>
        <button 
          v-if="allowExpand" 
          type="button" 
          class="terminal-action-btn expand-btn" 
          @click.stop="emit('expand')" 
          title="Plein écran"
        >
          ⛶
        </button>
      </div>
    </div>

    <!-- Corps du terminal (affichage texte ANSI) -->
    <div class="terminal-screen" ref="terminalBodyRef">
      <div class="terminal-output">
        <div v-for="(line, lineIdx) in lines" :key="lineIdx" class="terminal-line">
          <span
            v-for="(segment, segIdx) in line"
            :key="segIdx"
            :class="['term-segment', getColorClass(segment.color)]"
          >{{ segment.text }}</span>
        </div>
      </div>

      <!-- Ligne de saisie interactive -->
      <div v-if="isWaitingInput" class="terminal-input-row">
        <span class="terminal-cursor-prompt">&gt;</span>
        <input
          ref="inputRef"
          type="text"
          v-model="userInput"
          class="terminal-real-input"
          @keydown.enter="submit()"
          autocomplete="off"
          spellcheck="false"
        />
        <span class="terminal-cursor-blink">█</span>
      </div>
    </div>

    <!-- Clavier virtuel / Raccourcis contextuels -->
    <div class="terminal-quick-bar" v-if="isWaitingInput && currentPromptMeta" @click.stop>
      <!-- Menu principal -->
      <template v-if="currentPromptMeta.type === 'menu'">
        <button class="quick-btn" @click="submit('1')">1. Histoire</button>
        <button class="quick-btn" @click="submit('2')">2. Classique</button>
        <button class="quick-btn" @click="submit('3')">3. 1v1</button>
        <button class="quick-btn" @click="submit('4')">4. Scores</button>
        <button class="quick-btn" @click="submit('5')">5. Règles</button>
        <button class="quick-btn danger" @click="submit('0')">0. Quitter</button>
      </template>

      <!-- Directions Z Q S D -->
      <template v-else-if="currentPromptMeta.type === 'direction'">
        <span class="quick-label">Direction :</span>
        <button class="quick-btn" @click="submit('z')">Z (Haut ↑)</button>
        <button class="quick-btn" @click="submit('q')">Q (Gauche ←)</button>
        <button class="quick-btn" @click="submit('s')">S (Bas ↓)</button>
        <button class="quick-btn" @click="submit('d')">D (Droite →)</button>
      </template>

      <!-- Numéro de colonne ou ligne -->
      <template v-else-if="currentPromptMeta.type === 'col' || currentPromptMeta.type === 'row'">
        <span class="quick-label">{{ currentPromptMeta.type === 'col' ? 'Colonne' : 'Ligne' }} :</span>
        <button
          v-for="n in (currentPromptMeta.max || 5)"
          :key="n"
          class="quick-btn num-btn"
          @click="submit(n)"
        >
          {{ n }}
        </button>
      </template>

      <!-- Confirmation 1 -->
      <template v-else-if="currentPromptMeta.type === 'confirm_1'">
        <button class="quick-btn highlight" @click="submit('1')">1. Continuer</button>
      </template>

      <!-- Confirmation 2 -->
      <template v-else-if="currentPromptMeta.type === 'confirm_2'">
        <button class="quick-btn highlight" @click="submit('2')">2. Jouer</button>
      </template>

      <!-- Retour Menu 0 -->
      <template v-else-if="currentPromptMeta.type === 'confirm_0'">
        <button class="quick-btn" @click="submit('0')">0. Retour Menu</button>
      </template>

      <!-- Taille de grille -->
      <template v-else-if="currentPromptMeta.type === 'size'">
        <span class="quick-label">Taille :</span>
        <button class="quick-btn" @click="submit('5')">5</button>
        <button class="quick-btn" @click="submit('6')">6</button>
        <button class="quick-btn" @click="submit('7')">7</button>
        <button class="quick-btn" @click="submit('8')">8</button>
      </template>
    </div>
  </div>
</template>

<style scoped>
.candy-terminal-wrapper {
  display: flex;
  flex-direction: column;
  width: 100%;
  height: 100%;
  background: #06090f;
  color: #f1f5f9;
  font-family: 'Space Mono', 'Consolas', 'Monaco', 'Courier New', monospace;
  border-radius: 8px;
  overflow: hidden;
  box-sizing: border-box;
  text-align: left;
  user-select: text;
}

/* En-tête du terminal */
.terminal-header {
  background: #0f172a;
  padding: 0.4rem 0.8rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  border-bottom: 1px solid rgba(255, 255, 255, 0.08);
  font-size: 0.75rem;
  letter-spacing: 0.5px;
}

.terminal-dots {
  display: flex;
  gap: 6px;
  align-items: center;
}

.dot {
  width: 10px;
  height: 10px;
  border-radius: 50%;
  display: inline-block;
}

.dot.red { background: #ef4444; }
.dot.yellow { background: #eab308; }
.dot.green { background: #22c55e; }

.terminal-title {
  color: #94a3b8;
  font-size: 0.75rem;
  display: flex;
  align-items: center;
  gap: 0.4rem;
  font-family: var(--font-title, sans-serif);
}

.terminal-icon {
  color: var(--accent-color, #38bdf8);
  font-weight: bold;
}

.terminal-actions {
  display: flex;
  align-items: center;
  gap: 0.5rem;
}

.terminal-action-btn {
  background: rgba(255, 255, 255, 0.06);
  border: 1px solid rgba(255, 255, 255, 0.15);
  color: #cbd5e1;
  font-size: 0.7rem;
  padding: 0.15rem 0.5rem;
  border-radius: 4px;
  cursor: pointer;
  font-family: inherit;
  transition: all 0.2s ease;
}

.terminal-action-btn:hover {
  background: var(--accent-color, #38bdf8);
  color: #ffffff;
  border-color: var(--accent-color, #38bdf8);
}

.expand-btn {
  font-size: 0.8rem;
  padding: 0.1rem 0.4rem;
}

/* Écran du terminal */
.terminal-screen {
  flex: 1;
  padding: 0.75rem;
  overflow-y: auto;
  font-size: 0.8rem;
  line-height: 1.35;
  background: #06090f;
  display: flex;
  flex-direction: column;
}

.terminal-output {
  display: flex;
  flex-direction: column;
}

.terminal-line {
  min-height: 1.25em;
  white-space: pre-wrap;
  word-break: break-all;
}

.term-segment {
  display: inline;
}

/* Couleurs ANSI */
.ansi-reset { color: #f1f5f9; }
.ansi-red { color: #f87171; font-weight: bold; }
.ansi-green { color: #4ade80; font-weight: bold; }
.ansi-yellow { color: #facc15; font-weight: bold; }
.ansi-blue { color: #60a5fa; font-weight: bold; }
.ansi-magenta { color: #e879f9; font-weight: bold; }
.ansi-cyan { color: #22d3ee; font-weight: bold; }
.ansi-white { color: rgba(255, 255, 255, 0.15); } /* Valeur 0 rendue discrète */

/* Ligne de saisie interactive */
.terminal-input-row {
  display: flex;
  align-items: center;
  gap: 0.4rem;
  margin-top: 0.3rem;
}

.terminal-cursor-prompt {
  color: var(--accent-color, #38bdf8);
  font-weight: bold;
}

.terminal-real-input {
  background: transparent;
  border: none;
  outline: none;
  color: #f8fafc;
  font-family: inherit;
  font-size: 0.85rem;
  flex: 1;
  caret-color: transparent; /* Curseur customisé */
}

.terminal-cursor-blink {
  color: var(--accent-color, #38bdf8);
  font-size: 0.8rem;
  animation: blink 1s step-start infinite;
}

@keyframes blink {
  50% { opacity: 0; }
}

/* Barre de raccourcis rapides contextuelle */
.terminal-quick-bar {
  background: #0b1120;
  border-top: 1px solid rgba(255, 255, 255, 0.08);
  padding: 0.35rem 0.6rem;
  display: flex;
  flex-wrap: wrap;
  gap: 0.35rem;
  align-items: center;
}

.quick-label {
  font-size: 0.7rem;
  color: #94a3b8;
  margin-right: 0.2rem;
}

.quick-btn {
  background: rgba(255, 255, 255, 0.08);
  border: 1px solid rgba(255, 255, 255, 0.15);
  color: #f1f5f9;
  font-family: inherit;
  font-size: 0.72rem;
  padding: 0.2rem 0.5rem;
  border-radius: 4px;
  cursor: pointer;
  transition: all 0.2s ease;
}

.quick-btn:hover {
  background: var(--accent-color, #0055a5);
  color: #ffffff;
  border-color: var(--accent-color, #0055a5);
  transform: translateY(-1px);
}

.quick-btn.danger {
  color: #f87171;
  border-color: rgba(239, 68, 68, 0.3);
}

.quick-btn.danger:hover {
  background: #ef4444;
  color: #ffffff;
}

.quick-btn.highlight {
  border-color: var(--accent-color, #0055a5);
  color: var(--accent-color, #38bdf8);
}

.quick-btn.num-btn {
  min-width: 24px;
  text-align: center;
  font-weight: bold;
}
</style>
