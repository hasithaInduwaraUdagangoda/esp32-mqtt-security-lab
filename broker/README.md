# MQTT Broker Configuration

This folder contains all broker-related configurations for the ESP32 MQTT Security Lab.

The MQTT broker used in this project is:

- Eclipse Mosquitto
- Running inside Docker
- Supports multiple security configurations

---

## Folder Structure

```bash
broker/
│
├── certs/
├── data/
├── logs/
├── scripts/
├── mosquitto.conf
└── passwd.example
```

---

## Broker Overview

The Mosquitto broker is configured to support multiple MQTT security modes.

| Port | Security Mode | Description |
|------|---------------|-------------|
| 1883 | Unencrypted | Basic MQTT |
| 1884 | Authentication | Username + Password |
| 8883 | TLS | Encrypted MQTT |
| 8884 | Mutual TLS | Client certificate required |
| 8885 | TLS + Authentication | Encrypted + Credentials |
| 8886 | TLS (No Auth) | Encrypted only |

---

## Docker Setup

Broker runs using Docker Compose.

Start broker:

```bash
docker compose up -d
```

Stop broker:

```bash
docker compose down
```

Check logs:

```bash
docker logs -f mosquitto-broker
```

Check exposed ports:

```bash
docker port mosquitto-broker
```

---

## Configuration File

Main configuration file:

```text
broker/mosquitto.conf
```

This file contains:

- Listener ports
- TLS settings
- Authentication settings
- Certificate paths

---

## Authentication

Authentication uses username/password.

Example credentials:

```text
Username: hasitha
Password: 12345
```

Password file location:

```text
broker/passwd
```

Example file:

```text
broker/passwd.example
```

Generate actual password file:

```bash
docker run --rm -it -v "%cd%\broker:/mosquitto/config" eclipse-mosquitto mosquitto_passwd -c /mosquitto/config/passwd hasitha
```

---

## TLS Certificates

Certificates stored inside:

```text
broker/certs/
```

Files:

- `ca.crt` & `ca.key`
- `server.crt` & `server.key`
- `client.crt` & `client.key`
- `san.cnf`

### Generation Guides & Scripts

- [Docker OpenSSL Generation Guide (Step 1 - Step 16)](file:///e:/SLT/MQTT/broker/scripts/generate-certificates-docker.md)
- [Batch Script for Windows Automation](file:///e:/SLT/MQTT/broker/scripts/generate_certs.bat)
- [Certificates README](file:///e:/SLT/MQTT/broker/certs/README.md)


## Certificate Roles

### CA Certificate
Used to sign broker and client certificates.

### Server Certificate
Used by broker during TLS handshake.

### Client Certificate
Used by ESP32 for mutual TLS authentication.

---

## Security Notes

Do NOT upload private keys to public repositories.

Sensitive files:

- ca.key
- server.key
- client.key
- passwd

These files are ignored using `.gitignore`.

---

## Verification Tools

Broker functionality was verified using:

- ESP32
- MQTTBox
- Wireshark
- OpenSSL

---

## Expected Broker Logs

Successful startup:

```text
Opening ipv4 listen socket on port 1883
Opening ipv4 listen socket on port 1884
Opening ipv4 listen socket on port 8883
Opening ipv4 listen socket on port 8884
Opening ipv4 listen socket on port 8885
Opening ipv4 listen socket on port 8886
```