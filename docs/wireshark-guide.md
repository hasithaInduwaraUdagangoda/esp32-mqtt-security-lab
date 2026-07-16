# Wireshark Guide

Using Wireshark to analyze MQTT traffic.

## What is Wireshark?

Wireshark is a network protocol analyzer that captures and displays network packets in real-time. It's essential for:
- Debugging MQTT connections
- Analyzing protocol behavior
- Security auditing
- Performance analysis

## Installation

Download Wireshark from: https://www.wireshark.org/download.html

Available for:
- Windows
- macOS
- Linux

## Capturing MQTT Traffic

### Select Network Interface

1. Open Wireshark
2. Select the network interface to capture
   - **Loopback** (lo) for localhost traffic
   - **Wi-Fi** or **Ethernet** for network traffic
3. Click "Start capturing packets"

### Capture Filters

Use capture filters to reduce noise:

#### Capture MQTT Traffic Only
```
tcp port 1883 or tcp port 1884 or tcp port 8883 or tcp port 8884 or tcp port 8885 or tcp port 8886
```

#### Capture Specific IP
```
host 192.168.1.100
```

#### Capture Unencrypted MQTT Only
```
tcp port 1883 or tcp port 1884
```

### Start Capture

1. Enter capture filter in the filter bar
2. Click the blue shark fin to start
3. Perform MQTT operations
4. Click the red square to stop

## Display Filters

Use display filters to analyze captured packets:

### Filter by Protocol
```
mqtt
```

### Filter by Specific Port
```
tcp.port == 1883
```

### Filter by MQTT Message Type
```
mqtt.msgtype == 3  # PUBLISH
mqtt.msgtype == 8  # SUBSCRIBE
mqtt.msgtype == 1  # CONNECT
```

### Filter by Topic
```
mqtt.topic == "test/topic"
```

### Filter by Client ID
```
mqtt.clientid == "esp32_client"
```

### Combine Filters
```
mqtt && tcp.port == 1883
mqtt.msgtype == 3 && mqtt.topic == "sensors/temperature"
```

## Analyzing MQTT Packets

### Packet Structure

Each MQTT packet has:
- **Frame**: Physical layer info
- **Ethernet**: MAC addresses
- **IP**: Source/destination IPs
- **TCP**: Port numbers, sequence numbers
- **MQTT**: Protocol-specific data

### MQTT Packet Types

1. **CONNECT (1)**: Connection initiation
2. **CONNACK (2)**: Connection acknowledgment
3. **PUBLISH (3)**: Message publish
4. **PUBACK (4)**: Publish acknowledgment
5. **PUBREC (5)**: Publish received
6. **PUBREL (6)**: Publish release
7. **PUBCOMP (7)**: Publish complete
8. **SUBSCRIBE (8)**: Topic subscription
9. **SUBACK (9)**: Subscription acknowledgment
10. **UNSUBSCRIBE (10)**: Unsubscribe
11. **UNSUBACK (11)**: Unsubscribe acknowledgment
12. **PINGREQ (12)**: Ping request
13. **PINGRESP (13)**: Ping response
14. **DISCONNECT (14)**: Disconnect

### Viewing Packet Details

1. Click on a packet in the list
2. Expand the MQTT section in the packet details pane
3. View:
   - Message type
   - QoS level
   - Topic name
   - Payload
   - Flags

## Analyzing TLS Traffic

### TLS Handshake

For encrypted MQTT (ports 8883-8886), you'll see:
- **Client Hello**: TLS version, cipher suites
- **Server Hello**: Selected cipher suite
- **Certificate**: Server certificate
- **Server Key Exchange**: Key exchange parameters
- **Client Key Exchange**: Client key exchange
- **Change Cipher Spec**: Switch to encrypted
- **Finished**: Handshake complete

### Decrypting TLS Traffic

To decrypt TLS traffic:

1. **Get Private Key**: You need the server private key
2. **Configure Wireshark**:
   - Edit > Preferences > Protocols > TLS
   - Add "(pre)-Master-Secret log filename"
   - Point to key log file

**Note**: This is for debugging only. Never use in production.

## Common Analysis Tasks

### Verify Connection Establishment

1. Filter: `mqtt.msgtype == 1 or mqtt.msgtype == 2`
2. Look for CONNECT followed by CONNACK
3. Check return code in CONNACK

### Track Message Flow

1. Filter: `mqtt.msgtype == 3`
2. Follow PUBLISH messages
3. Check QoS and topic

### Analyze QoS Levels

1. Filter by message type:
   - QoS 0: Only PUBLISH
   - QoS 1: PUBLISH + PUBACK
   - QoS 2: PUBLISH + PUBREC + PUBREL + PUBCOMP

### Monitor Keep-Alive

1. Filter: `mqtt.msgtype == 12 or mqtt.msgtype == 13`
2. Check PINGREQ/PINGRESP timing
3. Verify keep-alive interval

### Debug Authentication

1. Filter: `mqtt.msgtype == 1`
2. Check CONNECT packet for username
3. Verify CONNACK return code

## Exporting Data

### Export Packets

1. File > Export Packet Dissections
2. Choose format:
   - Plain Text
   - JSON
   - CSV
   - PDML

### Export Objects

1. File > Export Objects > MQTT
2. Select messages to export
3. Save payloads

## Tips

1. **Use capture filters** to reduce packet load
2. **Colorize packets** for better visibility
3. **Save filters** for reuse
4. **Follow TCP stream** to see full conversation
5. **Use statistics** for protocol analysis
6. **Check packet comments** for notes

## Statistics

### Protocol Hierarchy

Statistics > Protocol Hierarchy
- Shows protocol distribution
- Useful for seeing MQTT vs other traffic

### Conversations

Statistics > Conversations > MQTT
- Shows client-broker pairs
- Message counts per conversation

### IO Graph

Statistics > IO Graph
- Visualize traffic over time
- Compare different protocols

## Troubleshooting

### No MQTT Packets Visible

- Check capture filter
- Verify correct interface
- Ensure broker is running
- Check if traffic is encrypted

### Encrypted Traffic Not Decrypted

- Need server private key
- Configure TLS preferences
- Check cipher suite support

### High Packet Loss

- Check network interface
- Reduce capture filter
- Use faster storage
- Close other applications

## Security Considerations

1. **Don't capture sensitive data** on shared networks
2. **Secure captured files** - they may contain credentials
3. **Delete captures** after analysis
4. **Use on authorized networks only**
5. **Comply with privacy policies**
