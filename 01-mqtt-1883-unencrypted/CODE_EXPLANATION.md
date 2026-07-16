# Task 01 Code Explanation

This document explains the ESP32 Arduino code used for Task 01 (Basic MQTT communication over port 1883).

---

# 1. Header Files

```cpp
#include <WiFi.h>
```

This library is used to connect the ESP32 to a Wi-Fi network.

It provides functions such as:

- `WiFi.begin()`
- `WiFi.localIP()`
- Wi-Fi event handling

---

```cpp
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
```

These libraries provide FreeRTOS timer functionality.

They are used to:

- automatically reconnect Wi-Fi
- automatically reconnect MQTT

This helps avoid blocking the ESP32.

---

```cpp
#include <AsyncMqttClient.h>
```

This library handles MQTT communication asynchronously.

It allows:

- MQTT connection
- Publishing messages
- Subscribing to topics
- Receiving messages

without blocking the main program.

---

# 2. Wi-Fi Configuration

```cpp
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
```

These store Wi-Fi credentials.

Purpose:

- connect ESP32 to internet
- enable broker communication

---

# 3. MQTT Broker Configuration

```cpp
#define MQTT_HOST "test.mosquitto.org"
#define MQTT_PORT 1883
```

These define broker settings.

### MQTT_HOST
Broker address.

Here:

```text
test.mosquitto.org
```

Public MQTT test broker.

### MQTT_PORT
Broker port number.

Port:

```text
1883
```

This is standard MQTT port for:

- unencrypted communication
- no authentication

---

# 4. MQTT Client Object

```cpp
AsyncMqttClient mqttClient;
```

Creates MQTT client object.

Used to:

- connect broker
- publish messages
- subscribe topics

---

# 5. Timer Objects

```cpp
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;
```

These timers help reconnect automatically when connection fails.

Two timers are used:

### mqttReconnectTimer
Reconnect MQTT after disconnect.

### wifiReconnectTimer
Reconnect Wi-Fi after disconnect.

---

# 6. Wi-Fi Connection Function

```cpp
void connectToWifi()
```

This function connects ESP32 to Wi-Fi.

Inside:

```cpp
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
```

Starts Wi-Fi connection.

---

# 7. MQTT Connection Function

```cpp
void connectToMqtt()
```

Connects ESP32 to MQTT broker.

Inside:

```cpp
mqttClient.connect();
```

Starts broker connection.

---

# 8. Wi-Fi Event Handler

```cpp
void WiFiEvent(WiFiEvent_t event)
```

This function handles Wi-Fi events.

Examples:

- connected
- disconnected
- IP assigned

---

## When Wi-Fi Connected

```cpp
case ARDUINO_EVENT_WIFI_STA_GOT_IP:
```

Triggered when ESP32 receives an IP address.

Actions:

- prints Wi-Fi connected
- prints IP address
- starts MQTT connection

---

## When Wi-Fi Disconnects

```cpp
case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
```

Triggered when Wi-Fi connection is lost.

Actions:

- stop MQTT reconnect timer
- start Wi-Fi reconnect timer

This ensures automatic recovery.

---

# 9. MQTT Connect Callback

```cpp
void onMqttConnect(bool sessionPresent)
```

This function runs after successful MQTT connection.

---

## Subscribe

```cpp
mqttClient.subscribe("test/task01", 2);
```

ESP32 subscribes to topic:

```text
test/task01
```

QoS level:

```text
2
```

QoS 2 ensures exactly-once delivery.

---

## Publish Messages

### QoS 0

```cpp
mqttClient.publish("test/task01", 0, true, "test 1");
```

Sends message using QoS 0.

Characteristics:

- fastest
- no acknowledgment
- possible packet loss

---

### QoS 1

```cpp
mqttClient.publish("test/task01", 1, true, "test 2");
```

Sends message using QoS 1.

Characteristics:

- broker acknowledges delivery
- may duplicate

---

### QoS 2

```cpp
mqttClient.publish("test/task01", 2, true, "test 3");
```

Sends message using QoS 2.

Characteristics:

- most reliable
- exactly once delivery
- more packets exchanged

---

# 10. MQTT Disconnect Callback

```cpp
void onMqttDisconnect(...)
```

Runs when MQTT connection is lost.

Purpose:

- detect broker disconnection
- reconnect automatically

---

# 11. Message Receive Callback

```cpp
void onMqttMessage(...)
```

Runs when subscribed message arrives.

Parameters include:

- topic
- payload
- QoS
- message length

---

## Print Topic

```cpp
Serial.println(topic);
```

Displays message topic.

Example:

```text
test/task01
```

---

## Print Payload

```cpp
for (size_t i = 0; i < len; i++)
```

Prints each character of received message.

Example output:

```text
test 3
```

---

## Print QoS

```cpp
Serial.println(properties.qos);
```

Displays received message QoS.

Example:

```text
2
```

---

# 12. Setup Function

```cpp
void setup()
```

Runs only once after ESP32 starts.

Tasks performed:

- start Serial Monitor
- create timers
- register Wi-Fi event handler
- register MQTT callbacks
- configure broker
- connect Wi-Fi

---

## Serial Monitor

```cpp
Serial.begin(115200);
```

Starts serial communication.

Baud rate:

```text
115200
```

Used for debugging.

---

## Register MQTT Callbacks

```cpp
mqttClient.onConnect(...)
mqttClient.onDisconnect(...)
mqttClient.onMessage(...)
```

Registers callback functions.

These functions automatically run on events.

---

## Set MQTT Server

```cpp
mqttClient.setServer(MQTT_HOST, MQTT_PORT);
```

Tells ESP32 which broker to connect to.

---

## Start Wi-Fi

```cpp
connectToWifi();
```

Begins Wi-Fi connection.

---

# 13. Loop Function

```cpp
void loop()
{
}
```

Empty because Async MQTT Client handles everything using callbacks.

No continuous polling is required.

---

# Summary

This code demonstrates basic MQTT communication using ESP32 over port 1883.

Features implemented:

- Wi-Fi connection
- MQTT connection
- Topic subscription
- Message publishing
- Message receiving
- QoS 0
- QoS 1
- QoS 2
- Automatic reconnection

Security level:

- Encryption: No
- Authentication: No