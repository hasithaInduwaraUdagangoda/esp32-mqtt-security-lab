# Task 05: MQTT over Port 8885 (TLS + Authentication)

## Objective

Connect ESP32 to MQTT broker using both TLS encryption and username/password authentication on port 8885.

## Concepts

- TLS encryption
- Username/password authentication
- Dual security layers
- Defense in depth

## Prerequisites

- MQTT broker running on port 8885
- CA certificate generated
- Password file configured with user credentials
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
const int mqtt_port = 8885;
const char* mqtt_user = "esp32_client";
const char* mqtt_password = "your_password";
```

### Certificate
```cpp
const char* ca_cert = "-----BEGIN CERTIFICATE-----\n...";
```

## Steps

1. Convert CA certificate to DER format
2. Copy DER certificate content to sketch
3. Update WiFi credentials in sketch
4. Update broker IP, username, and password
5. Upload sketch to ESP32
6. Open Serial Monitor (115200 baud)
7. Observe connection and messages

## Expected Output

```
Connecting to WiFi...
Connected to WiFi
IP address: 192.168.1.50
Setting up TLS with authentication...
Connecting to MQTT broker...
Connected to MQTT broker
Publishing message: Hello from ESP32
Message published
```

## Testing with MQTTBox

1. Create connection to `localhost:8885`
2. Enable SSL/TLS
3. Select CA certificate file
4. Enter username and password
5. Subscribe to topic `esp32/outgoing`
6. You should see messages from ESP32
7. Publish to topic `esp32/incoming`
8. ESP32 should receive and display message

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `tcp.port == 8885`
3. Observe:
   - TLS handshake
   - Encrypted CONNECT packet with credentials
   - Encrypted application data
4. Note: Credentials are encrypted and not visible

## Verification Screenshots

- **Serial Monitor Connection Output**: `screenshots/01_serial_monitor_connection.png`
- **Serial Monitor Message Flow**: `screenshots/02_serial_monitor_messages.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Payload**: `screenshots/03_mqttbox_publish_subscribe.png`
- **Wireshark Packet Stream Capture**: `screenshots/05_wireshark_packet_list.png`
- **Wireshark Encrypted Data Capture**: `screenshots/06_wireshark_encrypted_data.png`
- **Wireshark TLS Handshake Details**: `screenshots/07_wireshark_handshake_details.png`

## Security Notes

✅ **VERY SECURE**: This connection uses both TLS and authentication:
- All communication is encrypted
- Server identity is verified
- Client must provide valid credentials
- Defense in depth approach
- Recommended for production use

## Next Steps

Proceed to Task 06 to test TLS without authentication.

