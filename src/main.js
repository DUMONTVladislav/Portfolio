import { createApp } from 'vue'
import App from './App.vue'
import router from './router'
import { vReveal } from './directives/reveal.js'
import './assets/style.css'

const app = createApp(App)

app.directive('reveal', vReveal)
app.use(router)

app.mount('#app')
