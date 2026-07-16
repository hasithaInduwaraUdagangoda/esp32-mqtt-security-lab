#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

#define MQTT_HOST "YOUR_BROKER_IP"
#define MQTT_PORT 8884

WiFiClientSecure secureClient;
PubSubClient mqttClient(secureClient);

// ================= ROOT CA =================
const char ROOT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_ROOT_CA_CERTIFICATE
-----END CERTIFICATE-----
)EOF";

// ================= CLIENT CERT =================
const char CLIENT_CERT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_CLIENT_CERTIFICATE
-----END CERTIFICATE-----
)EOF";

// ================= CLIENT KEY =================
const char CLIENT_KEY[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
YOUR_CLIENT_PRIVATE_KEY
-----END RSA PRIVATE KEY-----
)EOF";

// ================= CALLBACK =================
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: ");

  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  Serial.println();
}

// ================= WIFI =================
void connectWiFi() {
  Serial.println("Connecting WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

// ================= MQTT =================
void connectMQTT() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting MQTT 8884...");

    if (mqttClient.connect("ESP32_TASK04")) {
      Serial.println("MQTT Connected");

      mqttClient.subscribe("test/task04");

      mqttClient.publish(
        "test/task04",
        "Hello from Task04"
      );

    } else {
      Serial.print("MQTT Failed rc=");
      Serial.println(mqttClient.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("START");

  connectWiFi();

  Serial.println("Loading certificates...");

  secureClient.setCACert(ROOT_CA);
  secureClient.setCertificate(CLIENT_CERT);
  secureClient.setPrivateKey(CLIENT_KEY);
  secureClient.setHandshakeTimeout(30);

  Serial.println("Testing TLS...");

  if (!secureClient.connect(MQTT_HOST, MQTT_PORT)) {
    Serial.println("TLS FAILED");

    char err[128];
    secureClient.lastError(err, sizeof(err));
    Serial.println(err);

    return;
  }

  Serial.println("TLS SUCCESS");
  secureClient.stop();

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
