# MQTT Theory

Understanding the MQTT protocol fundamentals.

## What is MQTT?

MQTT (Message Queuing Telemetry Transport) is a lightweight publish/subscribe messaging protocol designed for constrained devices and low-bandwidth, high-latency networks.

## Key Concepts

### Publish/Subscribe Model

MQTT uses a publish/subscribe pattern:
- **Publisher**: Sends messages to topics
- **Subscriber**: Receives messages from topics
- **Broker**: Mediates between publishers and subscribers

### Topics

Topics are hierarchical UTF-8 strings:
- `home/temperature`
- `sensors/room1/humidity`
- `devices/esp32/status`

Wildcards:
- `+`: Single-level wildcard (e.g., `sensors/+/temperature`)
- `#`: Multi-level wildcard (e.g., `sensors/#`)

### Quality of Service (QoS) Levels

1. **QoS 0 - At most once**: Fire and forget, no acknowledgment
2. **QoS 1 - At least once**: Acknowledged delivery, possible duplicates
3. **QoS 2 - Exactly once**: Assured delivery, no duplicates

### Last Will and Testament (LWT)

A message that the broker sends if a client disconnects unexpectedly:
- Configured when connecting
- Notifies other clients of unexpected disconnection
- Useful for device status monitoring

### Retained Messages

Messages stored by the broker:
- New subscribers receive the last retained message
- Useful for state information
- Set with the retained flag

## MQTT Packet Types

1. **CONNECT**: Initiates connection
2. **CONNACK**: Connection acknowledgment
3. **PUBLISH**: Publish message
4. **PUBACK**: Publish acknowledgment (QoS 1)
5. **PUBREC**: Publish received (QoS 2)
6. **PUBREL**: Publish release (QoS 2)
7. **PUBCOMP**: Publish complete (QoS 2)
8. **SUBSCRIBE**: Subscribe to topics
9. **SUBACK**: Subscription acknowledgment
10. **UNSUBSCRIBE**: Unsubscribe from topics
11. **UNSUBACK**: Unsubscribe acknowledgment
12. **PINGREQ**: Keep-alive request
13. **PINGRESP**: Keep-alive response
14. **DISCONNECT**: Graceful disconnect

## Security Considerations

### Authentication
- Username/password
- Client certificates
- Token-based authentication

### Encryption
- TLS/SSL for encrypted communication
- Prevents eavesdropping
- Ensures data integrity

### Authorization
- Access control lists (ACL)
- Topic-based permissions
- Client-specific restrictions

## MQTT vs HTTP

| Feature | MQTT | HTTP |
|---------|------|------|
| Pattern | Pub/Sub | Request/Response |
| Overhead | Low (2 bytes header) | High (headers) |
| Latency | Low | Higher |
| Scalability | High | Limited |
| Bidirectional | Yes | Limited |
| Stateful | Yes | Stateless |

## Best Practices

1. Use appropriate QoS levels
2. Design topic hierarchies carefully
3. Implement proper error handling
4. Use connection keep-alive
5. Implement LWT for critical devices
6. Secure connections in production
7. Monitor broker performance
