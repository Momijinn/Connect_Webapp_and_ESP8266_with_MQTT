# mqtt_arduino_servo

## Requirement

* ESP8266
* Servo Motor (SG90)
  * Convert to Infinite rotation: https://fukuno.jig.jp/2665

### Library

* https://github.com/knolleary/pubsubclient

## Usage

1. Write to Wifi ssid and passowrd.
```c++
// wifi ssid and wifi password
const char* ssid = "your_ssid";
const char* ssid_pwd = "your_password";
```

2. Write to a Brokser host and a client_id and two topics.  
The send_topic is topic for send a data.  
The recv_topic is topic for recv a data.
```c++
// mqtt
const char* server = "broker.com";
const char* client_id = "client_id";
const char* send_topic = "my-topic/esp";
const char* recv_topic = "my-topic/web";
```

4. Connect ESP8266 and Servo Moter.  
Servo Motor -> ESP8266  
Vcc -> VOUT  
Ground -> GND
PWM -> IO15

5. flash!  
<img src="https://user-images.githubusercontent.com/13119897/77824833-c7afe980-7148-11ea-99ce-69b430d165ca.JPG" height="500">
