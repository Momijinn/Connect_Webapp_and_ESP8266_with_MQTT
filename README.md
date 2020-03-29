# Connect_Webapp_and_ESP8266_with_MQTT
Connect Web Application(Nuxt.js) and ESP8266 with MQTT(Message Queue Telemetry Transport).  
This repository runs a servo motor connected to ESP8266 from Web app with MQTT.


## Description

<img src="https://user-images.githubusercontent.com/13119897/77838718-58221480-71b1-11ea-8e65-7cfea93da774.jpg" with="500" >

## Demo

Demo video is use a broker that "io.adafruit.com".  
Maybe, Web App can connect to other broker. (Set a host and path and etc.)

add video

## Directory

* mqtt_arduino_servo  
  ESP8266 Program.

* web_app  
  WebAppication (Nuxt.js)

## Usage

1. Flash the mqtt_arduino_servo to ESP8266.
2. Open URL ( )
3. Input Host(Broker) and Port(Broker Port) and etc.
4. Click "connect" button.
5. Submit a value.

<img src="https://user-images.githubusercontent.com/13119897/77838991-f6af7500-71b3-11ea-825d-09ce119fd274.PNG" with="500" >
