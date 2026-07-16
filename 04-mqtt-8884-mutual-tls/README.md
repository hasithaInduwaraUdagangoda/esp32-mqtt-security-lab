# Task 04: MQTT over Port 8884 (Mutual TLS)

## Objective

Connect ESP32 to MQTT broker using mutual TLS authentication on port 8884.

## Concepts

- Mutual TLS authentication
- Client certificates
- Two-way authentication
- Both server and client authenticate each other

## Prerequisites

- MQTT broker running on port 8884
- CA certificate generated
- Client certificate and key generated
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
const int mqtt_port = 8884;
```

### Certificates
```cpp
const char* ca_cert = "-----BEGIN CERTIFICATE-----\n...";
const char* client_cert = "-----BEGIN CERTIFICATE-----\n...";
const char* client_key = "-----BEGIN RSA PRIVATE KEY-----\n...";
```

## Convert Certificates to DER

ESP32 requires DER format. Convert using OpenSSL:
```bash
cd broker/certs
openssl x509 -in ca.crt -out ca.der -outform DER
openssl x509 -in client.crt -out client.der -outform DER
openssl rsa -in client.key -out client_key.der -outform DER
```

## Steps

1. Convert all certificates to DER format
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
Setting up mutual TLS...
Connecting to MQTT broker...
Connected to MQTT broker
Publishing message: Hello from ESP32
Message published
```

## Testing with MQTTBox

1. Create connection to `localhost:8884`
2. Enable SSL/TLS
3. Select CA certificate file
4. Select client certificate and key
5. Subscribe to topic `esp32/outgoing`
6. You should see messages from ESP32
7. Publish to topic `esp32/incoming`
8. ESP32 should receive and display message

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `tcp.port == 8884`
3. Observe:
   - TLS handshake with client certificate
   - Certificate Verify message
   - Encrypted application data
4. Note: Both server and client certificates are exchanged

## Verification Screenshots

- **Serial Monitor Connection Output**: `screenshots/01_serial_monitor_connection.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Payload**: `screenshots/03_mqttbox_publish_subscribe.png`
- **Wireshark Packet Stream Capture**: `screenshots/05_wireshark_packet_list.png`
- **Wireshark TLS Handshake Exchange**: `screenshots/06_wireshark_tls_handshake.png`
- **Wireshark Handshake Details**: `screenshots/07_wireshark_handshake_details.png`

## Security Notes

✅ **HIGHLY SECURE**: This connection uses mutual TLS:
- Server authenticates client via certificate
- Client authenticates server via certificate
- All communication is encrypted
- No passwords needed
- Strongest authentication method

## Next Steps

Proceed to Task 05 to combine TLS with username/password authentication.

