# Task 06: MQTT over Port 8886 (TLS without Authentication)

## Objective

Connect ESP32 to MQTT broker using TLS encryption without authentication on port 8886.

## Concepts

- TLS encryption without authentication
- Encrypted anonymous connections
- Privacy without access control
- Use case: public data streams

## Prerequisites

- MQTT broker running on port 8886
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
const int mqtt_port = 8886;
```

### Certificate
```cpp
const char* ca_cert = "-----BEGIN CERTIFICATE-----\n...";
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
Setting up TLS without authentication...
Connecting to MQTT broker...
Connected to MQTT broker
Publishing message: Hello from ESP32
Message published
```

## Testing with MQTTBox

1. Create connection to `localhost:8886`
2. Enable SSL/TLS
3. Select CA certificate file
4. No username/password required
5. Subscribe to topic `esp32/outgoing`
6. You should see messages from ESP32
7. Publish to topic `esp32/incoming`
8. ESP32 should receive and display message

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `tcp.port == 8886`
3. Observe:
   - TLS handshake
   - Encrypted CONNECT packet (no credentials)
   - Encrypted application data
4. Note: Messages are encrypted but no authentication

## Verification Screenshots

- **Serial Monitor Connection Output**: `screenshots/01_serial_monitor_connection.png`
- **Serial Monitor Message Flow**: `screenshots/02_serial_monitor_messages.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Payload**: `screenshots/03_mqttbox_publish_subscribe.png`
- **Wireshark Packet Stream Capture**: `screenshots/05_wireshark_packet_list.png`

## Security Notes

⚠️ **PARTIALLY SECURE**: This connection uses TLS only:
- All communication is encrypted
- Server identity is verified
- No client authentication
- Anyone with CA certificate can connect
- Suitable for public data, not sensitive data

## Use Cases

- Public sensor data
- Broadcast notifications
- Anonymous telemetry
- Development/testing

## Next Steps

Proceed to Task 07 to learn about LWT and QoS levels.

