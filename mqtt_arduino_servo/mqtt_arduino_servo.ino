#include <Servo.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

Servo myservo;

// wifi ssid and wifi password
const char* ssid = "your_ssid";
const char* ssid_pwd = "your_password";

// mqtt
const char* server = "broker.com";
const char* client_id = "client_id";
const char* send_topic = "my-topic/esp";
const char* recv_topic = "my-topic/web";

WiFiClient espClient;
PubSubClient client;

void connectNetwork(){
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, ssid_pwd);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("connected to WiFi");
}


void recvMessageCallback(char* topic, byte* payload, unsigned int length){
  if(!strcmp(topic, recv_topic)){
    char recv_message = (char)payload[0];
    if(recv_message == '0'){
      myservo.detach();
      client.publish(send_topic, "stop");
    }else if(recv_message == '1'){
      myservo.attach(15);
      myservo.write(10);
      client.publish(send_topic, "turn left");
    }else if(recv_message == '2'){
      myservo.attach(15);
      myservo.write(370);
      client.publish(send_topic, "turn right");
    }else{
      Serial.println("not supoort");
      client.publish(send_topic, "not supoort");
    }
  }
}


void connectMqtt(){
  Serial.print("Connecting to ");
  Serial.println(server);

  client.setClient(espClient);
  client.setServer(server, 1883);
  client.setCallback(recvMessageCallback);

  if( client.connect(client_id) ){
    Serial.println("connected to MQTT");
    client.subscribe(recv_topic);
  } else{
    // Error Code 
    // -4 : MQTT_CONNECTION_TIMEOUT - the server didn't respond within the keepalive time
    // -3 : MQTT_CONNECTION_LOST - the network connection was broken
    // -2 : MQTT_CONNECT_FAILED - the network connection failed
    // -1 : MQTT_DISCONNECTED - the client is disconnected cleanly
    // 0 : MQTT_CONNECTED - the client is connected
    // 1 : MQTT_CONNECT_BAD_PROTOCOL - the server doesn't support the requested version of MQTT
    // 2 : MQTT_CONNECT_BAD_CLIENT_ID - the server rejected the client identifier
    // 3 : MQTT_CONNECT_UNAVAILABLE - the server was unable to accept the connection
    // 4 : MQTT_CONNECT_BAD_CREDENTIALS - the username/password were rejected
    // 5 : MQTT_CONNECT_UNAUTHORIZED - the client was not authorized to connect
    Serial.print("failed, rc=");
    Serial.print(client.state());
    Serial.println("");
    delay(1000);
  }
}


void setup() {
  Serial.begin(115200);

  connectNetwork();

  while(!client.connected()){
    connectMqtt();
  }
}


void loop() {
  if(!client.connected()){
    Serial.println("disconnected to MQTT");
    connectMqtt();
  }

  client.loop();
}
