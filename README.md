# ESP32 MQTT Security Lab

<p align="center">
  ESP32-based MQTT security analysis covering authentication, TLS encryption, QoS, Last Will & Testament (LWT), and packet inspection using Docker Mosquitto Broker, MQTTBox, and Wireshark.
</p>

---

## Project Overview

This repository contains a complete MQTT security laboratory implementation using an ESP32 microcontroller and a self-hosted Mosquitto MQTT broker running in Docker.

The project demonstrates multiple MQTT security configurations, starting from basic unencrypted communication to advanced secure communication using TLS encryption, mutual certificate authentication, and authenticated secure connections.

Each task includes:

- Arduino / ESP32 source code
- Broker configuration
- MQTTBox verification
- Wireshark packet analysis
- Screenshots and results
- Security explanation

---

## Objectives

Main objectives of this lab:

- Understand MQTT protocol fundamentals
- Implement MQTT publish / subscribe communication
- Analyze insecure MQTT communication
- Apply username/password authentication
- Implement TLS encryption
- Implement mutual TLS authentication
- Analyze MQTT Quality of Service (QoS)
- Understand Last Will and Testament (LWT)
- Inspect MQTT packets using Wireshark

---

## Technology Stack

### Hardware
- ESP32 Development Board
- WiFi Network
- PC / Laptop

### Software
- Arduino IDE
- Docker Desktop
- Mosquitto MQTT Broker
- MQTTBox
- Wireshark
- OpenSSL

### Protocols
- MQTT
- TCP/IP
- TLS / SSL

---

## System Architecture

```text
ESP32
   |
   | WiFi
   |
MQTT Broker (Mosquitto Docker)
   |
   ├── MQTTBox
   └── Wireshark Packet Capture
```

Communication Flow:

1. ESP32 connects to WiFi
2. ESP32 connects to MQTT Broker
3. Publish messages to topics
4. Subscribe to topics
5. MQTTBox verifies messages
6. Wireshark analyzes packets

---

## Repository Structure

```bash
esp32-mqtt-security-lab/
│
├── broker/
├── docs/
├── 01-mqtt-1883-unencrypted/
├── 02-mqtt-1884-authenticated/
├── 03-mqtt-8883-tls/
├── 04-mqtt-8884-mutual-tls/
├── 05-mqtt-8885-tls-auth/
├── 06-mqtt-8886-tls-noauth/
├── 07-mqtt-lwt-qos/
└── assets/
```

---

## Task Summary

| Task | Port | Security Mode | Description |
|------|------|---------------|-------------|
| Task 01 | 1883 | Unencrypted | Basic MQTT publish / subscribe |
| Task 02 | 1884 | Authentication | Username/password protected MQTT |
| Task 03 | 8883 | TLS | Encrypted MQTT communication |
| Task 04 | 8884 | Mutual TLS | Client certificate authentication |
| Task 05 | 8885 | TLS + Authentication | Encrypted + username/password |
| Task 06 | 8886 | TLS (No Auth) | Encrypted without authentication |
| Task 07 | Mixed | QoS + LWT | Reliability and disconnection handling |

---

# Task Details

---

## Task 01 — MQTT over Port 1883 (Unencrypted)

Features:

- No encryption
- No authentication
- Plain text communication

Security Risk:

- Packets visible in Wireshark
- Credentials/messages exposed

Topics Covered:

- Publish
- Subscribe
- MQTT packet structure

---

## Task 02 — MQTT over Port 1884 (Authenticated)

Features:

- Username/password authentication
- No encryption

Security Risk:

- Authentication exists
- Traffic still visible

Topics Covered:

- Broker credential validation
- Login failure handling

---

## Task 03 — MQTT over Port 8883 (TLS)

Features:

- TLS encryption
- Server certificate validation
- Secure channel

Advantages:

- Prevents packet sniffing
- Encrypts MQTT payload

Topics Covered:

- CA certificate
- TLS handshake
- Certificate verification

---

## Task 04 — MQTT over Port 8884 (Mutual TLS)

Features:

- TLS encryption
- Client certificate required
- Mutual authentication

Advantages:

- Server verifies client
- Strong security

Topics Covered:

- Client certificate
- Client private key
- Mutual TLS handshake

---

## Task 05 — MQTT over Port 8885 (TLS + Authentication)

Features:

- TLS encryption
- Username/password
- Secure authenticated connection

Advantages:

- Double security layer

Topics Covered:

- Secure login
- TLS + credentials

---

## Task 06 — MQTT over Port 8886 (Encrypted, No Authentication)

Features:

- TLS encryption
- No username/password

Advantages:

- Encrypted communication
- Simpler deployment

Topics Covered:

- Secure transport
- TLS verification

---

## Task 07 — QoS & Last Will and Testament

Features:

### QoS 0
At most once delivery

### QoS 1
At least once delivery

### QoS 2
Exactly once delivery

### LWT
Broker publishes message when client disconnects unexpectedly.

Example:

```text
Client Offline
```

Topics Covered:

- Reliability
- Message delivery guarantees
- Failure detection

---

# Broker Configuration

Mosquitto broker runs inside Docker.

Example:

```yaml
services:
  mosquitto:
    image: eclipse-mosquitto
```

Broker supports:

- Port 1883
- Port 1884
- Port 8883
- Port 8884
- Port 8885
- Port 8886

---

## Certificates Used

Certificates generated using OpenSSL.

Generated files:

- ca.crt
- ca.key
- server.crt
- server.key
- client.crt
- client.key

Certificate Roles:

### CA Certificate
Signs all certificates

### Server Certificate
Used by broker

### Client Certificate
Used by ESP32

---

## MQTTBox Testing

MQTTBox used for:

- Connection verification
- Topic subscription
- Publish testing
- Authentication testing

Used to verify whether broker communication works correctly.

---

## Wireshark Analysis

Wireshark used to inspect:

- TCP packets
- MQTT packets
- TLS handshake
- Encrypted traffic

Example filters:

```text
mqtt
```

```text
tcp.port == 1883
```

```text
tcp.port == 8883
```

---

## Key Findings

### Unencrypted MQTT
- Easy to inspect
- Unsafe for production

### Authenticated MQTT
- Better access control
- Still vulnerable to sniffing

### TLS MQTT
- Payload encrypted
- Secure against packet inspection

### Mutual TLS
- Strongest security
- Prevents unauthorized clients

---

## Results

Successfully implemented:

- MQTT communication on ESP32
- TLS encrypted connections
- Certificate authentication
- Username/password authentication
- QoS levels
- LWT handling
- Packet analysis

All seven tasks were completed and validated using MQTTBox and Wireshark.

---

## Future Improvements

Possible future enhancements:

- MQTT over WebSockets
- Cloud broker integration
- OTA firmware update
- MQTT over AWS IoT
- Certificate rotation
- JWT authentication

---

## References

- MQTT Version 3.1.1 Specification
- Eclipse Mosquitto Documentation
- ESP32 Arduino Documentation
- Wireshark Documentation
- OpenSSL Documentation

---

## Author

**Hasitha Induwara**  
Electrical & Electronic Engineering Undergraduate  
SLIIT  
Founder — Migo Labs

---

## License

This project is intended for academic and educational purposes.