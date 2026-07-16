#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// ================= WIFI =================
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// ================= MQTT =================
#define MQTT_HOST "YOUR_BROKER_IP"
#define MQTT_PORT 8885
#define MQTT_USER "YOUR_MQTT_USERNAME"
#define MQTT_PASS "YOUR_MQTT_PASSWORD"

// ================= CERT =================
const char ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_ROOT_CA_CERTIFICATE
-----END CERTIFICATE-----
)EOF";

WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

// ================= CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message received");
  Serial.print("Topic: ");
  Serial.println(topic);

  Serial.print("Payload: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// ================= WIFI =================
void connectToWifi() {
  Serial.println("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// ================= MQTT =================
void connectToMqtt() {
  while (!mqttClient.connected()) {

    Serial.println("Connecting to MQTT...");

    if (mqttClient.connect("ESP32_Task05", MQTT_USER, MQTT_PASS)) {
      Serial.println("Connected to MQTT");

      mqttClient.subscribe("test/task05");

      mqttClient.publish(
        "test/task05",
        "Hello from ESP32 Task05"
      );

    } else {
      Serial.print("MQTT Failed, rc=");
      Serial.println(mqttClient.state());
      delay(3000);
    }
  }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  Serial.println();

  connectToWifi();

  secureClient.setCACert(ROOT_CA);
  secureClient.setHandshakeTimeout(30);

  mqttClient.setServer(MQTT_HOST, MQTT_PORT);
  mqttClient.setCallback(callback);

  connectToMqtt();
}

// ================= LOOP =================
void loop() {
  if (!mqttClient.connected()) {
    connectToMqtt();
  }

  mqttClient.loop();
}
