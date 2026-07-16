#include <WiFi.h>
#include <PubSubClient.h>

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define MQTT_HOST "YOUR_BROKER_IP"
#define MQTT_PORT 1883

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

void connectWifi() {
  Serial.println("Connecting WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.println(WiFi.localIP());
}

void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting MQTT...");

    bool ok = mqttClient.connect(
      "ESP32_Task07",
      "status/esp32",   // LWT topic
      1,                // LWT QoS
      true,             // retain
      "ESP32 Offline"   // LWT payload
    );

    if (ok) {
      Serial.println("MQTT Connected");

      mqttClient.subscribe("test/qos");

      // Birth message
      mqttClient.publish(
        "status/esp32",
        "ESP32 Online",
        true
      );

      // QoS0 demo
      mqttClient.publish(
        "test/qos",
        "QoS0 Message"
      );

    } else {
      Serial.print("Failed rc=");
      Serial.println(mqttClient.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  connectWifi();

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(callback);

  connectMQTT();
}

void loop() {
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();
}
