<script setup>
import { ref, onMounted, onBeforeUnmount, nextTick } from 'vue'
import { CandyCrushEngine } from '@/games/candy-crush/candyCrushEngine.js'
import { useI18n } from '@/composables/useI18n.js'

const { t } = useI18n()

defineProps({
  allowExpand: {
    type: Boolean,
    default: false
  }
})

const emit = defineEmits(['expand'])

const terminalBodyRef = ref(null)
const inputRef = ref(null)

const lines = ref([])
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
      terminalBodyRef.value.scrollLeft = 0
    }
  })
}

const isGridOrAsciiLine = (str) => {
  const trimmed = str.trim()
  if (!trimmed) return false
  if (/^[+\-=_#|/\\[\]]{3,}/.test(trimmed)) return true
  if ((str.match(/\|/g) || []).length >= 3) return true
  if (/\s{4,}/.test(str)) return true
  return false
}

const wrapNarrativeText = (str) => {
  if (isGridOrAsciiLine(str)) return str
  const maxWidth = window.innerWidth <= 480 ? 46 : window.innerWidth <= 768 ? 60 : 78
  if (str.length <= maxWidth) return str

  const words = str.split(' ')
  const wrapped = []
  let current = ''

  for (const word of words) {
    if (!current) {
      current = word
    } else if (current.length + 1 + word.length <= maxWidth) {
      current += ' ' + word
    } else {
      wrapped.push(current)
      current = word
    }
  }
  if (current) wrapped.push(current)

  return wrapped.join('\n')
}

const addText = (text, isNewline = false) => {
  const rawStr = String(text)
  const normalized = isNewline
    ? rawStr.split('\n').map(wrapNarrativeText).join('\n')
    : wrapNarrativeText(rawStr)

  const parts = normalized.split('\n')
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
    inputRef.value.focus({ preventScroll: true })
  }
}

const submit = (valToSubmit = null) => {
  if (!isWaitingInput.value || !inputResolver) return

  const value = valToSubmit !== null ? String(valToSubmit) : userInput.value
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
          :title="t('terminal.restartTitle')"
        >
          {{ t('terminal.restartBtn') }}
        </button>
        <button
          v-if="allowExpand"
          type="button"
          class="terminal-action-btn expand-btn"
          @click.stop="emit('expand')"
          :title="t('terminal.fullscreenTitle')"
        >
          ⛶
        </button>
      </div>
    </div>

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

    <div class="terminal-quick-bar" v-if="isWaitingInput && currentPromptMeta" @click.stop>
      <template v-if="currentPromptMeta.type === 'menu'">
        <button type="button" class="quick-btn" @click="submit('1')">{{ t('terminal.quickStory') }}</button>
        <button type="button" class="quick-btn" @click="submit('2')">{{ t('terminal.quickClassic') }}</button>
        <button type="button" class="quick-btn" @click="submit('3')">{{ t('terminal.quick1v1') }}</button>
        <button type="button" class="quick-btn" @click="submit('4')">{{ t('terminal.quickScores') }}</button>
        <button type="button" class="quick-btn" @click="submit('5')">{{ t('terminal.quickRules') }}</button>
        <button type="button" class="quick-btn danger" @click="submit('0')">{{ t('terminal.quickQuit') }}</button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'direction'">
        <span class="quick-label">{{ t('terminal.quickDirection') }}</span>
        <button type="button" class="quick-btn" @click="submit('z')">Z ↑</button>
        <button type="button" class="quick-btn" @click="submit('q')">Q ←</button>
        <button type="button" class="quick-btn" @click="submit('s')">S ↓</button>
        <button type="button" class="quick-btn" @click="submit('d')">D →</button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'col' || currentPromptMeta.type === 'row'">
        <span class="quick-label">{{ currentPromptMeta.type === 'col' ? t('terminal.quickCol') : t('terminal.quickRow') }}</span>
        <button
          v-for="n in (currentPromptMeta.max || 5)"
          :key="n"
          type="button"
          class="quick-btn num-btn"
          @click="submit(n)"
        >
          {{ n }}
        </button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'confirm_1'">
        <button type="button" class="quick-btn highlight" @click="submit('1')">{{ t('terminal.quickContinue') }}</button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'confirm_2'">
        <button type="button" class="quick-btn highlight" @click="submit('2')">{{ t('terminal.quickPlay') }}</button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'confirm_0'">
        <button type="button" class="quick-btn" @click="submit('0')">{{ t('terminal.quickBackMenu') }}</button>
      </template>

      <template v-else-if="currentPromptMeta.type === 'size'">
        <span class="quick-label">{{ t('terminal.quickSize') }}</span>
        <button type="button" class="quick-btn" @click="submit('5')">5</button>
        <button type="button" class="quick-btn" @click="submit('6')">6</button>
        <button type="button" class="quick-btn" @click="submit('7')">7</button>
        <button type="button" class="quick-btn" @click="submit('8')">8</button>
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
  min-width: 0;
  min-height: 0;
  background: #06090f;
  color: #f1f5f9;
  font-family: 'Space Mono', 'Consolas', 'Monaco', 'Courier New', monospace;
  border-radius: 8px;
  overflow: hidden;
  box-sizing: border-box;
  text-align: left;
  user-select: text;
}

.terminal-header {
  background: #0f172a;
  padding: 0.4rem 0.8rem;
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 0.5rem;
  border-bottom: 1px solid rgba(255, 255, 255, 0.08);
  font-size: 0.75rem;
  letter-spacing: 0.5px;
  flex-shrink: 0;
}

.terminal-dots {
  display: flex;
  gap: 6px;
  align-items: center;
  flex-shrink: 0;
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
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}

.terminal-icon {
  color: var(--accent-color, #38bdf8);
  font-weight: bold;
  flex-shrink: 0;
}

.terminal-actions {
  display: flex;
  align-items: center;
  gap: 0.45rem;
  flex-shrink: 0;
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
  white-space: nowrap;
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

.terminal-screen {
  flex: 1;
  min-height: 0;
  padding: 0.75rem;
  overflow: auto;
  font-size: 0.8rem;
  line-height: 1.35;
  background: #06090f;
  display: flex;
  flex-direction: column;
  -webkit-overflow-scrolling: touch;
}

.terminal-output {
  display: flex;
  flex-direction: column;
  width: max-content;
  min-width: 100%;
}

.terminal-line {
  min-height: 1.25em;
  white-space: pre;
}

.term-segment {
  display: inline;
}

.ansi-reset { color: #f1f5f9; }
.ansi-red { color: #f87171; font-weight: bold; }
.ansi-green { color: #4ade80; font-weight: bold; }
.ansi-yellow { color: #facc15; font-weight: bold; }
.ansi-blue { color: #60a5fa; font-weight: bold; }
.ansi-magenta { color: #e879f9; font-weight: bold; }
.ansi-cyan { color: #22d3ee; font-weight: bold; }
.ansi-white { color: rgba(255, 255, 255, 0.15); }

.terminal-input-row {
  display: flex;
  align-items: center;
  gap: 0.4rem;
  margin-top: 0.3rem;
  flex-shrink: 0;
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
  min-width: 0;
  caret-color: transparent;
}

.terminal-cursor-blink {
  color: var(--accent-color, #38bdf8);
  font-size: 0.8rem;
  animation: blink 1s step-start infinite;
}

@keyframes blink {
  50% { opacity: 0; }
}

.terminal-quick-bar {
  background: #0b1120;
  border-top: 1px solid rgba(255, 255, 255, 0.08);
  padding: 0.35rem 0.6rem;
  display: flex;
  flex-wrap: wrap;
  gap: 0.35rem;
  align-items: center;
  flex-shrink: 0;
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
  padding: 0.25rem 0.55rem;
  border-radius: 4px;
  cursor: pointer;
  touch-action: manipulation;
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
  min-width: 28px;
  text-align: center;
  font-weight: bold;
}

@media (max-width: 768px) {
  .terminal-header {
    padding: 0.35rem 0.6rem;
  }

  .terminal-dots {
    gap: 4px;
  }

  .dot {
    width: 8px;
    height: 8px;
  }

  .terminal-title {
    font-size: 0.7rem;
  }

  .terminal-screen {
    padding: 0.55rem;
    font-size: 0.68rem;
    line-height: 1.3;
  }

  .terminal-real-input {
    font-size: 0.8rem;
  }

  .terminal-quick-bar {
    padding: 0.35rem 0.45rem;
    gap: 0.3rem;
  }

  .quick-btn {
    font-size: 0.68rem;
    padding: 0.25rem 0.45rem;
  }
}

@media (max-width: 480px) {
  .terminal-screen {
    padding: 0.45rem;
    font-size: 0.56rem;
    line-height: 1.28;
  }

  .quick-label {
    font-size: 0.64rem;
  }

  .quick-btn {
    font-size: 0.65rem;
    padding: 0.25rem 0.4rem;
  }

  .quick-btn.num-btn {
    min-width: 24px;
    padding: 0.25rem 0.25rem;
  }
}
</style>