# Task 02: MQTT over Port 1884 (Username/Password Authentication)

## Objective

Connect ESP32 to MQTT broker using username and password authentication on port 1884.

## Concepts

- MQTT authentication
- Username/password credentials
- Basic security layer
- Still unencrypted (credentials sent in plain text)

## Prerequisites

- MQTT broker running on port 1884
- Password file configured with user credentials
- ESP32 with WiFi connection
- PubSubClient library installed

## Configuration

### WiFi Settings
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

### MQTT Broker Settings
```cpp
const char* mqtt_server = "192.168.1.100";
const int mqtt_port = 1884;
const char* mqtt_user = "esp32_client";
const char* mqtt_password = "your_password";
```

## Setup Password File

Generate password file:
```bash
cd broker
mosquitto_passwd -c passwd esp32_client
# Enter password when prompted
```

## Steps

1. Generate password file for broker
2. Update WiFi credentials in sketch
3. Update broker IP, username, and password
4. Upload sketch to ESP32
5. Open Serial Monitor (115200 baud)
6. Observe connection and messages

## Expected Output

```
Connecting to WiFi...
Connected to WiFi
IP address: 192.168.1.50
Connecting to MQTT broker...
Connected to MQTT broker
Publishing message: Hello from ESP32
Message published
```

## Testing with MQTTBox

1. Create connection to `localhost:1884`
2. Enter username and password
3. Subscribe to topic `esp32/outgoing`
4. You should see messages from ESP32
5. Publish to topic `esp32/incoming`
6. ESP32 should receive and display message

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `tcp.port == 1884`
3. Observe:
   - CONNECT packet with username/password (base64 encoded)
   - Credentials are visible in packet capture
4. Note: Authentication provides basic security but credentials are still visible

## Verification Screenshots

- **Serial Monitor Connection Output**: `screenshots/01_serial_monitor_connection.png`
- **Serial Monitor Message Flow**: `screenshots/02_serial_monitor_messages.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Payload**: `screenshots/03_mqttbox_publish_subscribe.png`
- **Wireshark Packet Stream Capture**: `screenshots/05_wireshark_packet_list.png`
- **Wireshark Connection Handshake Packets**: `screenshots/06_wireshark_tcp_handshake.png`
- **Wireshark Subscribe Request Details**: `screenshots/07_wireshark_subscribe_request.png`

## Security Notes

⚠️ **WARNING**: This connection is unencrypted. While authentication prevents unauthorized access:
- Credentials are sent in plain text (base64 encoded)
- Anyone on network can capture credentials
- Messages are still visible in plain text

**Use TLS in addition to authentication for production!**

## Next Steps

Proceed to Task 03 to add TLS encryption.

