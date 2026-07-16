# MQTTBox Guide

Using MQTTBox to test MQTT connections.

## What is MQTTBox?

MQTTBox is a cross-platform MQTT client for testing and debugging MQTT brokers. It provides a graphical interface for:
- Creating MQTT connections
- Publishing messages
- Subscribing to topics
- Viewing message history

## Installation

Download MQTTBox from: https://mqttbox.github.io/

Available for:
- Windows
- macOS
- Linux
- Chrome Extension

## Creating a Connection

### Basic Connection (Port 1883)

1. Click "Create MQTT Client"
2. Fill in the connection details:
   - **MQTT Client Name**: Task01-Unencrypted
   - **Protocol**: mqtt://
   - **Host**: localhost (or broker IP)
   - **Port**: 1883
   - **Client ID**: (auto-generated or custom)
3. Click "Save"

### Authenticated Connection (Port 1884)

1. Click "Create MQTT Client"
2. Fill in the connection details:
   - **MQTT Client Name**: Task02-Authenticated
   - **Protocol**: mqtt://
   - **Host**: localhost
   - **Port**: 1884
   - **Username**: esp32_client
   - **Password**: (your password)
3. Click "Save"

### TLS Connection (Port 8883)

1. Click "Create MQTT Client"
2. Fill in the connection details:
   - **MQTT Client Name**: Task03-TLS
   - **Protocol**: mqtts://
   - **Host**: localhost
   - **Port**: 8883
3. Click "SSL/TLS" tab
4. Enable SSL/TLS
5. Select "CA Certificate" and browse to `broker/certs/ca.crt`
6. Click "Save"

### Mutual TLS Connection (Port 8884)

1. Click "Create MQTT Client"
2. Fill in the connection details:
   - **MQTT Client Name**: Task04-MutualTLS
   - **Protocol**: mqtts://
   - **Host**: localhost
   - **Port**: 8884
3. Click "SSL/TLS" tab
4. Enable SSL/TLS
5. Select certificates:
   - **CA Certificate**: `broker/certs/ca.crt`
   - **Client Certificate**: `broker/certs/client.crt`
   - **Client Key**: `broker/certs/client.key`
6. Click "Save"

## Publishing Messages

### Basic Publish

1. Select a connection
2. Click "Publish" tab
3. Enter:
   - **Topic**: test/topic
   - **Message**: Hello MQTT
   - **QoS**: 0
   - **Retain**: Unchecked
4. Click "Publish"

### Publish with QoS

1. Select QoS level (0, 1, or 2)
2. Higher QoS ensures delivery but uses more bandwidth

### Publish with Retain

1. Check "Retain" checkbox
2. Message will be stored by broker
3. New subscribers receive the last retained message

## Subscribing to Topics

### Basic Subscribe

1. Select a connection
2. Click "Subscribe" tab
3. Enter:
   - **Topic**: test/#
   - **QoS**: 0
4. Click "Subscribe"

### Subscribe with Wildcards

- Single level: `sensors/+/temperature`
- Multi level: `sensors/#`

### Unsubscribe

1. Click "Unsubscribe" next to the topic
2. Or click "Unsubscribe All"

## Viewing Messages

### Message History

Messages appear in the message list with:
- Timestamp
- Topic
- Payload
- QoS level

### Message Details

Click on a message to see:
- Full payload
- Message properties
- Raw data

## Advanced Features

### Last Will and Testament (LWT)

1. Click "Options" tab
2. Configure LWT:
   - **Will Topic**: status/client
   - **Will Message**: offline
   - **Will QoS**: 0
   - **Will Retain**: Checked
3. Save connection

### Clean Session

- **Enabled**: Broker discards session data on disconnect
- **Disabled**: Broker maintains session data

### Keep Alive

- Interval in seconds for connection keep-alive
- Default: 60 seconds
- Adjust based on network conditions

## Troubleshooting

### Connection Refused

- Check broker is running
- Verify host and port
- Check firewall settings

### Authentication Failed

- Verify username and password
- Check password file exists
- Ensure user is in password file

### SSL/TLS Errors

- Verify certificate files
- Check certificate validity
- Ensure CA certificate is correct
- For mutual TLS, verify client certificate

### No Messages Received

- Check topic matches exactly
- Verify QoS settings
- Check if broker is receiving messages
- Use Wireshark to capture packets

## Tips

1. **Use descriptive connection names** for easy identification
2. **Test with simple topics** before complex hierarchies
3. **Monitor message history** to track communication
4. **Use different colors** for different connections
5. **Save connection configurations** for reuse
6. **Test with command-line tools** if GUI has issues

## Common Use Cases

### Testing ESP32 Connection

1. Create connection matching ESP32 configuration
2. Subscribe to topics ESP32 publishes to
3. Publish to topics ESP32 subscribes to
4. Verify bidirectional communication

### Debugging

1. Subscribe to `#` to see all messages
2. Monitor message flow
3. Check QoS levels
4. Verify message format

### Load Testing

1. Create multiple connections
2. Publish messages rapidly
3. Monitor broker performance
4. Check for message loss
