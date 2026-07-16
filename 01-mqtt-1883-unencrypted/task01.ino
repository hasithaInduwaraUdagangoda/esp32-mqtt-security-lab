#include <WiFi.h>
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

// ================= WiFi Configuration =================
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// ================= MQTT Broker =================
#define MQTT_HOST "test.mosquitto.org"
#define MQTT_PORT 1883

AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

// ================= WiFi Connection =================
void connectToWifi() {
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

// ================= MQTT Connection =================
void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event) {
  switch (event) {

    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.print("IP Address: ");
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

// ================= MQTT Callbacks =================
void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT Broker!");

  mqttClient.subscribe("test/task01", 2);

  mqttClient.publish("test/task01", 0, true, "test 1");
  mqttClient.publish("test/task01", 1, true, "test 2");
  mqttClient.publish("test/task01", 2, true, "test 3");
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT");

  if (WiFi.isConnected()) {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

void onMqttMessage(
    char* topic,
    char* payload,
    AsyncMqttClientMessageProperties properties,
    size_t len,
    size_t index,
    size_t total) {

  Serial.println("Message Received");

  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (size_t i = 0; i < len; i++) {
    Serial.print(payload[i]);
  }
  Serial.println();

  Serial.print("QoS: ");
  Serial.println(properties.qos);
}

void setup() {
  Serial.begin(115200);

  mqttReconnectTimer = xTimerCreate(
    "mqttTimer",
    pdMS_TO_TICKS(2000),
    pdFALSE,
    (void*)0,
    reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt)
  );

  wifiReconnectTimer = xTimerCreate(
    "wifiTimer",
    pdMS_TO_TICKS(2000),
    pdFALSE,
    (void*)0,
    reinterpret_cast<TimerCallbackFunction_t>(connectToWifi)
  );

  WiFi.onEvent(WiFiEvent);

  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onMessage(onMqttMessage);

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
}

void loop() {
}