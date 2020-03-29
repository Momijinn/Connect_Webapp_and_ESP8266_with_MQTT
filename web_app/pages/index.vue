<template>
  <div class="container">
    <div>
      <table>
        <tr>
          <th>Host</th>
          <td>
            <input v-model="host" type="text" placeholder="broker.com" :disabled="!boolDisable">
          </td>
          <td>(require)</td>
        </tr>
        <tr>
          <th>Port</th>
          <td>
            <input v-model="port" type="number" placeholder="443" :disabled="!boolDisable">
          </td>
          <td>(require)</td>
        </tr>
        <tr>
          <td>Path</td>
          <td>
            <input v-model="path" type="text" placeholder="/mqtt" :disabled="!boolDisable">
          </td>
          <td>(option)</td>
        </tr>
        <tr>
          <td>UserName</td>
          <td>
            <input v-model="username" type="text" placeholder="username" :disabled="!boolDisable">
          </td>
          <td>(option)</td>
        </tr>
        <tr>
          <td>Password</td>
          <td>
            <input v-model="password" type="password" placeholder="password" :disabled="!boolDisable">
          </td>
          <td>(option)</td>
        </tr>
        <tr>
          <th>Recv Topic</th>
          <td>
            <input v-model="recv_topic" type="text" placeholder="my-topic/recv" :disabled="!boolDisable">
          </td>
          <td>(require)</td>
        </tr>
        <tr>
          <th>Send Topic</th>
          <td>
            <input v-model="send_topic" type="text" placeholder="my-topic/send" :disabled="!boolDisable">
          </td>
          <td>(require)</td>
        </tr>
      </table>

      <div>
        <button :disabled="!boolDisable" @click="connect">
          connect
        </button>
        <button :disabled="boolDisable" @click="disconnect">
          disconnect
        </button>
      </div>

      <br>

      <div v-if="!boolDisable">
        <input v-model="sendMessageValue" type="text" placeholder="value">
        <button @click="sendMessage">
          submit
        </button>
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
      path: '',
      username: '',
      password: '',
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
        port: this.port,
        username: this.username,
        password: this.password,
        path: this.path
      }

      const client = mqtt.connect("wss://" + this.host, options)
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
        this.recvMessages.push(topic + ',' + message)
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
