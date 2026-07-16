# Task 07: MQTT LWT (Last Will and Testament) & QoS Levels

## Objective

Implement Last Will and Testament (LWT) and test different QoS levels with ESP32.

## Concepts

- Last Will and Testament (LWT)
- QoS levels (0, 1, 2)
- Message delivery guarantees
- Connection loss handling

## Prerequisites

- MQTT broker running (any port)
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
const int mqtt_port = 1883; // Use any configured port
```

### LWT Settings
```cpp
const char* lwt_topic = "esp32/status";
const char* lwt_message = "offline";
const int lwt_qos = 0;
const bool lwt_retain = true;
```

## QoS Levels

### QoS 0 - At Most Once
- Fire and forget
- No acknowledgment
- Possible message loss
- Lowest overhead

### QoS 1 - At Least Once
- Acknowledged delivery
- Possible duplicates
- Guaranteed delivery
- Medium overhead

### QoS 2 - Exactly Once
- Four-way handshake
- No duplicates
- Guaranteed delivery
- Highest overhead

## Steps

1. Update WiFi credentials in sketch
2. Update broker IP address
3. Configure LWT settings
4. Set desired QoS level
5. Upload sketch to ESP32
6. Open Serial Monitor (115200 baud)
7. Test LWT by disconnecting ESP32
8. Test different QoS levels

## Expected Output

```
Connecting to WiFi...
Connected to WiFi
IP address: 192.168.1.50
Connecting to MQTT broker...
Connected to MQTT broker
LWT configured: esp32/status -> offline
Publishing online status
Publishing message with QoS 0
Message published
```

## Testing LWT

1. Subscribe to `esp32/status` topic
2. Observe "online" message when ESP32 connects
3. Disconnect ESP32 (power off or reset)
4. Observe "offline" message (LWT triggered)
5. Reconnect ESP32
6. Observe "online" message again

## Testing QoS Levels

### QoS 0
```cpp
client.publish(topic, message, false); // QoS 0
```

### QoS 1
```cpp
client.publish(topic, message, true); // QoS 1 (retain flag)
```

### QoS 2
```cpp
client.publish(topic, message, false, 2); // QoS 2
```

## Wireshark Analysis

1. Start Wireshark capture
2. Filter: `mqtt`
3. Observe:
   - CONNECT packet with LWT parameters
   - PUBLISH packets with different QoS flags
   - PUBACK for QoS 1
   - PUBREC/PUBREL/PUBCOMP for QoS 2

## Use Cases

### LWT
- Device status monitoring
- Alert systems
- Presence detection
- Failover handling

### QoS 0
- Real-time sensor data
- High-frequency updates
- Non-critical data

### QoS 1
- Commands and control
- Important notifications
- Configuration updates

### QoS 2
- Financial transactions
- Critical alerts
- Billing systems

## Verification Screenshots

- **Serial Monitor Output (Messages & Status)**: `screenshots/01_serial_monitor_messages.png`
- **MQTTBox Client Connection Status**: `screenshots/04_mqttbox_client_connected.png`
- **MQTTBox Publish & Subscribed Topics**: `screenshots/03_mqttbox_publish_subscribe.png`
- **MQTTBox LWT Status & QoS Message Flow**: `screenshots/05_mqttbox_lwt_qos_messages.png`
- **Wireshark LWT & Birth Message Packets**: `screenshots/06_wireshark_lwt_birth_packets.png`
- **Wireshark QoS Delivery Stream**: `screenshots/07_wireshark_lwt_qos_packets.png`

## Security Notes

This task uses unencrypted connection for simplicity. In production:
- Use TLS encryption
- Combine with authentication
- Secure LWT topics if sensitive

## Completion

Congratulations! You have completed all 7 tasks of the ESP32 MQTT Security Lab.

