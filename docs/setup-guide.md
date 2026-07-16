# Setup Guide

Complete setup instructions for the ESP32 MQTT Security Lab.

## Prerequisites

### Hardware
- ESP32 development board
- USB cable for programming
- Computer with USB port

### Software
- Arduino IDE (latest version)
- ESP32 board support for Arduino IDE
- Docker Desktop
- MQTTBox (or similar MQTT client)
- Wireshark (for packet analysis)
- OpenSSL (for certificate generation)

## Installation Steps

### 1. Install Arduino IDE

Download and install Arduino IDE from: https://www.arduino.cc/en/software

### 2. Add ESP32 Board Support

1. Open Arduino IDE
2. Go to File > Preferences
3. Add this URL to "Additional Boards Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Go to Tools > Board > Boards Manager
5. Search for "esp32" and install "ESP32 by Espressif Systems"

### 3. Install Docker Desktop

Download and install Docker Desktop from: https://www.docker.com/products/docker-desktop

### 4. Install MQTTBox

Download MQTTBox from: https://mqttbox.github.io/

### 5. Install Wireshark

Download Wireshark from: https://www.wireshark.org/download.html

### 6. Install OpenSSL

- **Windows**: Install Git for Windows (includes OpenSSL) or download from https://slproweb.com/products/Win32OpenSSL.html
- **macOS**: Included with system (via Homebrew: `brew install openssl`)
- **Linux**: `sudo apt-get install openssl`

## Project Setup

### 1. Clone the Repository

```bash
git clone <repository-url>
cd esp32-mqtt-security-lab
```

### 2. Generate Certificates

Navigate to the broker directory and follow the certificate generation scripts:

```bash
cd broker/scripts
```

Follow the instructions in:
- `generate-ca.md`
- `generate-server-cert.md`
- `generate-client-cert.md`

### 3. Generate Password File

```bash
cd ..
mosquitto_passwd -c passwd esp32_client
# Enter password when prompted
```

### 4. Start the MQTT Broker

```bash
cd ../../
docker-compose up -d
```

### 5. Verify Broker is Running

```bash
docker-compose logs -f mosquitto
```

You should see messages indicating the broker is listening on all configured ports.

## ESP32 Configuration

### 1. Connect ESP32

Connect your ESP32 to your computer via USB.

### 2. Select Board in Arduino IDE

1. Go to Tools > Board
2. Select "ESP32 Dev Module"

### 3. Select Port

1. Go to Tools > Port
2. Select the COM port where your ESP32 is connected

### 4. Install Required Libraries

In Arduino IDE, install these libraries via Library Manager:
- PubSubClient by Nick O'Leary
- WiFi (built-in)
- Wire (built-in)

## Next Steps

Once setup is complete, proceed to Task 01 to begin the lab exercises.
