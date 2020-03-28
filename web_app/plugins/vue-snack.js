import Vue from 'vue'
import VueSnackbar from 'vue-snack'
import 'vue-snack/dist/vue-snack.min.css'

const options = { position: 'bottom', time: 3000 }

Vue.use(VueSnackbar, options)
