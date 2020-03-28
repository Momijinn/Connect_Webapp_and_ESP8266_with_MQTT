# Connect_Webapp_and_ESP8266_with_MQTT
Connect Web Application(Nuxt.js) and ESP8266 with MQTT(Message Queue Telemetry Transport).  
This repository runs a servo motor connected to ESP8266 from Web app with MQTT.

## Description

<img src="https://user-images.githubusercontent.com/13119897/77827311-347eb000-7158-11ea-919f-727a084ca199.jpg" with="500" >

## Demo

add video

## Directory

* mqtt_arduino_servo  
  ESP8266 Program.

* web_app  
  WebAppication (Nuxt.js)

## Usage

1. Flash the mqtt_arduino_servo to ESP8266.
2. Open URL ( )
3. Input Host(Broker) and Port(Broker Port) and Recv Topic and Send Topic.
4. Click "connect" button.
5. Submit a value.

<img src="https://user-images.githubusercontent.com/13119897/77827436-fe8dfb80-7158-11ea-9c38-996fbf3437a5.PNG" with="500" >

※ broker.hivemq.com is free public broker.