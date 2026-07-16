# Troubleshooting Guide

Common issues and solutions for the ESP32 MQTT Security Lab.

## Connection Issues

### ESP32 Cannot Connect to WiFi

**Symptoms:**
- Serial output shows "Connecting to WiFi..." indefinitely
- WiFi status never becomes WL_CONNECTED

**Solutions:**
1. Verify WiFi credentials are correct
2. Check if WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
3. Ensure WiFi network is within range
4. Check if MAC address filtering is enabled on router
5. Try restarting ESP32 and router

### ESP32 Cannot Connect to MQTT Broker

**Symptoms:**
- Serial output shows "Attempting MQTT connection... failed"
- Connection retry loop continues

**Solutions:**
1. Verify broker IP address is correct
2. Check if broker is running: `docker-compose ps`
3. Verify port is correct for the task
4. Check firewall settings
5. Ensure ESP32 and broker are on same network
6. Check broker logs: `docker-compose logs mosquitto`

### Connection Drops Frequently

**Symptoms:**
- ESP32 connects then disconnects repeatedly
- Intermittent connection loss

**Solutions:**
1. Increase keep-alive interval in broker config
2. Check WiFi signal strength
3. Reduce publish frequency
4. Add delay in loop to prevent overwhelming broker
5. Check for power supply issues

## Certificate Issues

### Certificate Validation Failed

**Symptoms:**
- TLS connection fails
- Error: "certificate verify failed"

**Solutions:**
1. Verify CA certificate is correct
2. Check certificate expiration date
3. Ensure certificate is in correct format (PEM/DER)
4. Verify broker hostname matches certificate CN
5. Check if SAN includes broker IP

### Client Certificate Not Accepted

**Symptoms:**
- Mutual TLS connection fails
- Broker rejects client certificate

**Solutions:**
1. Verify client certificate is signed by CA
2. Check client certificate expiration
3. Ensure client key matches certificate
4. Verify broker has `require_certificate true`
5. Check broker logs for specific error

### Certificate Format Errors

**Symptoms:**
- Compilation errors with certificate strings
- Runtime certificate parsing errors

**Solutions:**
1. Convert certificates to DER format for ESP32
2. Ensure proper line breaks in certificate strings
3. Use `\n` for line breaks in code
4. Verify no extra characters in certificate
5. Check certificate file encoding (UTF-8)

## Authentication Issues

### Authentication Failed

**Symptoms:**
- Connection rejected with authentication error
- Error code: 4 or 5 in CONNACK

**Solutions:**
1. Verify username and password are correct
2. Check password file exists on broker
3. Ensure user is in password file
4. Regenerate password file if corrupted
5. Check broker logs for authentication errors

### Password File Not Found

**Symptoms:**
- Broker fails to start
- Error: "password_file not found"

**Solutions:**
1. Verify password file path in mosquitto.conf
2. Check if password file exists
3. Ensure file permissions are correct
4. Generate password file using mosquitto_passwd
5. Restart broker after creating file

## Docker Issues

### Container Won't Start

**Symptoms:**
- `docker-compose up` fails
- Container exits immediately

**Solutions:**
1. Check Docker Desktop is running
2. Verify docker-compose.yml syntax
3. Check port conflicts with other services
4. Review container logs: `docker-compose logs`
5. Ensure sufficient system resources

### Port Already in Use

**Symptoms:**
- Error: "bind: address already in use"
- Broker cannot bind to ports

**Solutions:**
1. Find process using the port
2. Stop conflicting service
3. Change ports in docker-compose.yml
4. Restart Docker daemon
5. Check for zombie containers

### Volume Mount Issues

**Symptoms:**
- Certificate files not accessible in container
- Configuration not loaded

**Solutions:**
1. Verify volume paths are correct
2. Check file permissions on host
3. Ensure paths are absolute, not relative
4. Restart container after adding volumes
5. Check Docker Desktop shared drives settings

## ESP32 Issues

### Upload Failed

**Symptoms:**
- Arduino IDE shows upload error
- ESP32 not recognized

**Solutions:**
1. Check USB cable (use data cable, not charge-only)
2. Verify correct COM port selected
3. Put ESP32 in bootloader mode (hold BOOT button)
4. Try different USB port
5. Reinstall ESP32 board support

### Serial Monitor Shows Garbage

**Symptoms:**
- Unreadable characters in Serial Monitor
- Baud rate mismatch

**Solutions:**
1. Set Serial Monitor baud rate to 115200
2. Check if ESP32 is using correct baud rate
3. Try different baud rates (9600, 57600)
4. Restart Serial Monitor
5. Check USB driver installation

### Out of Memory

**Symptoms:**
- ESP32 crashes or restarts
- Heap allocation errors

**Solutions:**
1. Reduce certificate string sizes
2. Use PROGMEM for large constant strings
3. Free memory when not needed
4. Reduce buffer sizes
5. Monitor heap with `ESP.getFreeHeap()`

## MQTTBox Issues

### Cannot Connect

**Symptoms:**
- MQTTBox connection fails
- Timeout errors

**Solutions:**
1. Verify broker is running
2. Check host and port settings
3. Disable firewall temporarily
4. Try with different protocol (mqtt:// vs mqtts://)
5. Check broker logs

### SSL/TLS Errors

**Symptoms:**
- Certificate errors in MQTTBox
- Handshake failures

**Solutions:**
1. Select correct CA certificate file
2. Verify certificate format
3. Check broker hostname matches certificate
4. Try with SSL verification disabled (testing only)
5. Update MQTTBox to latest version

## Wireshark Issues

### No MQTT Packets Visible

**Symptoms:**
- Wireshark capture shows no MQTT traffic
- Only TCP packets visible

**Solutions:**
1. Verify correct network interface selected
2. Check capture filter syntax
3. Ensure broker is actually sending traffic
4. Try capturing on loopback interface for localhost
5. Check if traffic is encrypted (use display filter)

### Cannot Decrypt TLS

**Symptoms:**
- Encrypted packets not readable
- Cannot see message content

**Solutions:**
1. Need server private key for decryption
2. Configure TLS preferences in Wireshark
3. Use key log file if available
4. Note: Production traffic cannot be decrypted
5. Use unencrypted connection for debugging

## Performance Issues

### High Latency

**Symptoms:**
- Messages take long to arrive
- Delayed responses

**Solutions:**
1. Check network congestion
2. Reduce message size
3. Optimize publish frequency
4. Use appropriate QoS level
5. Check broker performance

### Message Loss

**Symptoms:**
- Messages not arriving
- Gaps in message sequence

**Solutions:**
1. Use higher QoS level (1 or 2)
2. Check network stability
3. Verify broker capacity
4. Implement message queuing
5. Add error handling and retry logic

## Getting Help

If issues persist:
1. Check broker logs: `docker-compose logs -f mosquitto`
2. Review ESP32 Serial Monitor output
3. Capture Wireshark traces
4. Verify all configuration files
5. Consult documentation in /docs directory
