# Task 03: MQTT over Port 8883 (TLS/SSL)

## Objective

Connect ESP32 to MQTT broker using TLS/SSL encryption on port 8883.

## Concepts

- TLS/SSL encryption
- Certificate validation
- Encrypted communication
- Server authentication

## Prerequisites

- MQTT broker running on port 8883
- CA certificate generated
- ESP32 with WiFi connection
- PubSubClient library installed
- WiFiClientSecure library (built-in)

## Configuration

### WiFi Settings
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### MQTT Broker Settings
```cpp
const char* mqtt_server = "192.168.1.100";
const int mqtt_port = 8883;
```

### Certificate
```cpp
const char* ca_cert = \
"-----BEGIN CERTIFICATE-----\n" \
"MIID...\n" \
"-----END CERTIFICATE-----\n";
```

## Convert CA Certificate to DER

ESP32 requires DER format. Convert using OpenSSL:
```bash
cd broker/certs
openssl x509 -in ca.crt -out ca.der -outform DER
```

## Steps

1. Convert CA certificate to DER format
2. Copy DER certificate content to sketch
3. Update WiFi credentials in sketch
4. Update broker IP address
5. Upload sketch to ESP32
6. Open Serial Monitor (115200 baud)
7. Observe connection and messages

## Expected Output

```
Connecting to WiFi...
Connected to WiFi
IP address: 192.168.1.50
Setting up TLS...
Connecting to MQTT broker...
Connected to MQTT broker
Publishing message: Hello from ESP32
Message published
```

## Testing with MQTTBox

1. Create connection to `localhost:8883`
2. Enable SSL/TLS
3. Select CA certificate file
4. Subscribe to topic `esp32/outgoing`
5. You should see messages from ESP32
6. Publish to topic `esp32/incoming`
7. ESP32 should receive and display message

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `tcp.port == 8883`
3. Observe:
   - TLS handshake (Client Hello, Server Hello, etc.)
   - Encrypted application data (not readable)
   - Certificate exchange
4. Note: Messages are encrypted and not visible

## Verification Screenshots

- **Serial Monitor Connection Output**: `screenshots/02_serial_monitor_connection.png`
- **Serial Monitor Message Flow (QoS 0, 1, 2)**: `screenshots/01_serial_monitor_messages.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Payload**: `screenshots/03_mqttbox_publish_subscribe.png`
- **Wireshark Packet Stream Capture**: `screenshots/05_wireshark_packet_capture.png`
- **Wireshark Encrypted TLS Packet Detail**: `screenshots/06_wireshark_encrypted_payload.png`

## Security Notes

✅ **SECURE**: This connection uses TLS encryption:
- All communication is encrypted
- Server identity is verified via certificate
- Messages cannot be read by network sniffers
- Provides confidentiality and integrity

## Next Steps

Proceed to Task 04 to add mutual TLS authentication.

