# mqtt_arduino_servo

## Requirement

* ESP8266
* Servo Motor (SG90)
  * Convert to Infinite rotation: https://fukuno.jig.jp/2665

### Library

* https://github.com/knolleary/pubsubclient

### Connect to Broker

* https://io.adafruit.com

## Usage

1. Write to Wifi ssid and passowrd.
```c++
// wifi ssid and wifi password
const char* ssid = "your_ssid";
const char* ssid_pwd = "your_password";
```

2. Write to a user_name and a key(password) and a client_id and two topics.  
The send_topic is topic for send a data.  
The recv_topic is topic for recv a data.  

    You can get a user_name and a key by  "Adafruit IO Key" button push.  
    <img src="https://user-images.githubusercontent.com/13119897/77838529-c49c1400-71af-11ea-986c-351621343b65.PNG" height="400">

```c++
// mqtt
const char* server = "io.adafruit.com";
int port = 1883;
const char* user_name = "userName";
const char* key = "password";
const char* client_id = "client_id";
const char* send_topic = "userName/feeds/esp";
const char* recv_topic = "userName/feeds/web";
```

4. Connect ESP8266 and Servo Moter.  
Servo Motor -> ESP8266  
Vcc -> VOUT  
Ground -> GND
PWM -> IO15

5. flash!  
<img src="https://user-images.githubusercontent.com/13119897/77824833-c7afe980-7148-11ea-99ce-69b430d165ca.JPG" height="500">
