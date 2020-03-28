<template>
  <div class="container">
    <div>
      <div>
        <span>Host: </span>
        <input v-model="host" type="text" placeholder="broker.com" :disabled="!boolDisable">
      </div>

      <div>
        <span>Port: </span>
        <input v-model="port" type="number" placeholder="8000" :disabled="!boolDisable">
      </div>

      <div>
        <span>Recv Topic: </span>
        <input v-model="recv_topic" type="text" placeholder="my-topic/recv" :disabled="!boolDisable">
      </div>

      <div>
        <span>Send Topic: </span>
        <input v-model="send_topic" type="text" placeholder="my-topic/send" :disabled="!boolDisable">
      </div>

      <div>
        <button @click="connect" :disabled="!boolDisable">connect</button>
        <button @click="disconnect" :disabled="boolDisable">disconnect</button>
      </div>

      <br>

      <div v-if="!boolDisable">
         <input v-model="sendMessageValue" type="text" placeholder="value">
        <button @click="sendMessage">submit</button>
      </div>

      <div class="recvMsg">
        <div v-for="(word, key) in recvMessages" :key="key">
          recv {{ key }}: {{ word }}
        </div>
      </div>
    </div>
  </div>
</template>

<script>

export default {
  data () {
    return {
      host: '',
      port: null,
      recv_topic: '',
      send_topic: '',
      recvMessages: [],
      boolDisable: true,
      client: '',
      sendMessageValue: ''
    }
  },

  methods: {
    connect () {
      if (!this.host || !this.port || !this.recv_topic || !this.send_topic) {
        this.showSnackBar('Please input Host and Port and Topics.')
        return
      }

      const mqtt = require('mqtt')
      const options = {
        host: this.host,
        port: this.port,
        path: '/mqtt'
      }

      const client = mqtt.connect(options)
      this.client = client

      client.on('connect', () => {
        this.showSnackBar('Connected')
        client.subscribe(this.recv_topic)
        this.boolDisable = !this.boolDisable
      })

      client.on('error', (err) => {
        this.showSnackBar('Error: ' + err)
        client.end()
      })

      client.on('message', (topic, message) => {
        this.recvMessages.push(message)
      })
    },

    disconnect () {
      this.client.end()
      this.boolDisable = !this.boolDisable
      this.sendMessageValue = ''
      this.showSnackBar('disConnected')
    },

    sendMessage () {
      if (!this.sendMessageValue) {
        this.showSnackBar('message is empty.')
        return
      }

      this.client.publish(this.send_topic, this.sendMessageValue)
      this.showSnackBar('submit')
    },

    showSnackBar (message) {
      this.$snack.show({
        text: message
      })
    }
  }
}
</script>

<style>
.container {
  margin: 0 auto;
  min-height: 100vh;
  display: flex;
  justify-content: center;
  align-items: top;
  text-align: center;
}

.recvMsg {
  text-align: left;
}
</style>
