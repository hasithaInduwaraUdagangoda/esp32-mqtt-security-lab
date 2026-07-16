#include <WiFi.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
#include <WiFiClientSecure.h>
#include <ArduinoMqttClient.h>

// ================= WIFI =================

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// =============== MQTT ===================
#define MQTT_HOST "YOUR_BROKER_IP"   // Laptop IP
#define MQTT_PORT 8883

WiFiClientSecure wifiClient;
MqttClient mqttClient(wifiClient);

TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

// ========================================

void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");

  // TLS enable (skip certificate validation for testing)
  wifiClient.setInsecure();

  if (!mqttClient.connect(MQTT_HOST, MQTT_PORT)) {
    Serial.println("Disconnected from MQTT!");
    Serial.print("Reason: ");
    Serial.println(mqttClient.connectError());

    xTimerStart(mqttReconnectTimer, 0);
    return;
  }

  onMqttConnect(false);
}

void WiFiEvent(WiFiEvent_t event) {
  Serial.print("[WiFi-event] event: ");
  Serial.println(event);

  switch (event) {

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());

      connectToMqtt();
      break;

    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      xTimerStop(mqttReconnectTimer, 0);
      xTimerStart(wifiReconnectTimer, 0);
      break;

    default:
      break;
  }
}

// MQTT connected
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);

  if (!mqttClient.subscribe("test/hasitha/task03")) {
    Serial.println("Subscribe failed!");
  } else {
    onMqttSubscribe(1, 2);
  }

  // QoS0 publish
  mqttClient.beginMessage("test/hasitha/task03");
  mqttClient.print("TLS QoS0");
  mqttClient.endMessage();
  Serial.println("Publishing at QoS 0");

  delay(1000);

  // QoS1 simulation
  mqttClient.beginMessage("test/hasitha/task03");
  mqttClient.print("TLS QoS1");
  mqttClient.endMessage();
  Serial.println("Publishing at QoS 1");

  delay(1000);

  // QoS2 simulation
  mqttClient.beginMessage("test/hasitha/task03");
  mqttClient.print("TLS QoS2");
  mqttClient.endMessage();
  Serial.println("Publishing at QoS 2");

  onMqttPublish(1);
}

void onMqttDisconnect(int reason) {
  Serial.println("Disconnected from MQTT!");
  Serial.print("Reason: ");
  Serial.println(reason);

  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttSubscribe(uint16_t packetId, uint8_t qos) {
  Serial.println("Subscribe acknowledged.");
  Serial.print("packetId: ");
  Serial.println(packetId);
  Serial.print("qos: ");
  Serial.println(qos);
}

void onMqttMessage() {
  int messageSize = mqttClient.parseMessage();

  if (messageSize) {
    Serial.println("Publish received.");

    Serial.print("topic: ");
    Serial.println(mqttClient.messageTopic());

    Serial.print("payload: ");

    while (mqttClient.available()) {
      char c = (char)mqttClient.read();
      Serial.print(c);
    }
    Serial.println();

    Serial.print("len: ");
    Serial.println(messageSize);
  }
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("packetId: ");
  Serial.println(packetId);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);

  mqttReconnectTimer = xTimerCreate(
    "mqttTimer",
    pdMS_TO_TICKS(3000),
    pdFALSE,
    (void*)0,
    reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt)
  );

  wifiReconnectTimer = xTimerCreate(
    "wifiTimer",
    pdMS_TO_TICKS(3000),
    pdFALSE,
    (void*)0,
    reinterpret_cast<TimerCallbackFunction_t>(connectToWifi)
  );

  WiFi.onEvent(WiFiEvent);

  connectToWifi();
}

void loop() {
  if (mqttClient.connected()) {
    onMqttMessage();
  }
}
