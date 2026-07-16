# Common Errors and Solutions

Frequently encountered errors and their fixes.

## ESP32 Errors

### WiFi Connection Errors

#### Error: `WiFi.status() != WL_CONNECTED`
**Cause:** WiFi credentials incorrect or network unavailable
**Solution:**
```cpp
// Verify credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```

#### Error: `E (12345) wifi: esp_wifi_start failed`
**Cause:** WiFi already initialized or hardware issue
**Solution:** Restart ESP32 or call `WiFi.disconnect()` before reconnecting

### MQTT Connection Errors

#### Error: `rc = -1` (Connection refused)
**Cause:** Broker not running or wrong port
**Solution:**
```bash
# Check broker status
docker-compose ps
# Restart broker
docker-compose restart mosquitto
```

#### Error: `rc = -2` (Connection failed)
**Cause:** Network issue or wrong IP
**Solution:** Verify broker IP and network connectivity

#### Error: `rc = 4` (Bad username/password)
**Cause:** Authentication failed
**Solution:** Check username and password in broker password file

#### Error: `rc = 5` (Not authorized)
**Cause:** ACL restrictions or authentication required
**Solution:** Ensure user has permissions or disable authentication

### TLS Errors

#### Error: `certificate verify failed`
**Cause:** CA certificate incorrect or expired
**Solution:**
```cpp
// Verify CA certificate
espClient.setCACert(ca_cert);
```

#### Error: `mbedtls_x509_crt_parse failed`
**Cause:** Certificate format incorrect
**Solution:** Convert to DER format:
```bash
openssl x509 -in ca.crt -out ca.der -outform DER
```

#### Error: `SSL/TLS handshake failed`
**Cause:** Certificate mismatch or protocol version
**Solution:** Verify TLS version and certificate CN matches hostname

## Broker Errors

### Configuration Errors

#### Error: `Error: Unable to open configuration file`
**Cause:** mosquitto.conf path incorrect or permissions
**Solution:**
```bash
# Check file exists
ls -la broker/mosquitto.conf
# Check permissions
chmod 644 broker/mosquitto.conf
```

#### Error: `Error: Invalid configuration`
**Cause:** Syntax error in mosquitto.conf
**Solution:** Validate configuration syntax and check for typos

### Certificate Errors

#### Error: `Error: Unable to load CA certificate`
**Cause:** CA certificate file missing or wrong path
**Solution:**
```bash
# Verify certificate exists
ls -la broker/certs/ca.crt
# Check path in mosquitto.conf
cafile /mosquitto/certs/ca.crt
```

#### Error: `Error: Unable to load server certificate`
**Cause:** Server certificate or key missing
**Solution:**
```bash
# Verify files exist
ls -la broker/certs/server.crt
ls -la broker/certs/server.key
```

### Authentication Errors

#### Error: `Error: Unable to open password file`
**Cause:** Password file missing or wrong path
**Solution:**
```bash
# Generate password file
mosquitto_passwd -c broker/passwd esp32_client
# Update path in mosquitto.conf
password_file /mosquitto/config/passwd
```

#### Error: `Error: Invalid password file`
**Cause:** Password file corrupted
**Solution:** Regenerate password file

## Docker Errors

### Container Errors

#### Error: `docker-compose: command not found`
**Cause:** Docker Compose not installed
**Solution:** Install Docker Desktop (includes Compose)

#### Error: `Cannot connect to Docker daemon`
**Cause:** Docker not running
**Solution:** Start Docker Desktop

#### Error: `Port is already allocated`
**Cause:** Port already in use
**Solution:**
```bash
# Find process using port
netstat -ano | findstr :1883
# Stop conflicting service or change port
```

### Volume Errors

#### Error: `invalid mount path`
**Cause:** Volume path syntax error
**Solution:** Use absolute paths in docker-compose.yml

#### Error: `permission denied`
**Cause:** File permissions on host
**Solution:** Adjust file permissions or run Docker with appropriate access

## Certificate Generation Errors

### OpenSSL Errors

#### Error: `unable to load private key`
**Cause:** Private key file missing or wrong format
**Solution:**
```bash
# Generate new key
openssl genrsa -out ca.key 2048
```

#### Error: `subject does not match issuer`
**Cause:** Self-signed certificate issue
**Solution:** Ensure CA certificate is used to sign other certificates

#### Error: `certificate expired`
**Cause:** Certificate validity period passed
**Solution:** Generate new certificates with longer validity

## Arduino IDE Errors

### Compilation Errors

#### Error: `'PubSubClient' was not declared`
**Cause:** Library not installed
**Solution:** Install PubSubClient via Library Manager

#### Error: `'WiFiClientSecure' was not declared`
**Cause:** Wrong board selected or library issue
**Solution:** Select ESP32 board and reinstall ESP32 core

#### Error: `certificate string too long`
**Cause:** Certificate string exceeds buffer
**Solution:** Use PROGMEM or reduce certificate size

### Upload Errors

#### Error: `Failed to connect to ESP32`
**Cause:** Wrong port or driver issue
**Solution:** Select correct COM port and install USB drivers

#### Error: `Timed out waiting for packet header`
**Cause:** ESP32 not in bootloader mode
**Solution:** Hold BOOT button while pressing EN

## MQTTBox Errors

### Connection Errors

#### Error: `Connection refused`
**Cause:** Broker not running or wrong port
**Solution:** Verify broker is running and port is correct

#### Error: `SSL handshake failed`
**Cause:** Certificate issue
**Solution:** Select correct CA certificate file

### Subscription Errors

#### Error: `Subscription failed`
**Cause:** Invalid topic or permissions
**Solution:** Verify topic syntax and check ACL settings

## Wireshark Errors

### Capture Errors

#### Error: `No interfaces found`
**Cause:** Wireshark permissions or driver issue
**Solution:** Run Wireshark as administrator or reinstall

#### Error: `Capture filter syntax error`
**Cause:** Invalid filter syntax
**Solution:** Use correct filter syntax:
```bash
tcp.port == 1883
```

### Display Errors

#### Error: `No packets matching filter`
**Cause:** No traffic on interface or wrong filter
**Solution:** Select correct interface and verify filter

## General Solutions

### Reset Everything

```bash
# Stop broker
docker-compose down

# Remove volumes (WARNING: deletes data)
docker-compose down -v

# Restart Docker
# Restart Docker Desktop

# Start fresh
docker-compose up -d
```

### Check Logs

```bash
# Broker logs
docker-compose logs -f mosquitto

# ESP32 logs
# Open Serial Monitor in Arduino IDE
```

### Verify Network

```bash
# Ping broker
ping 192.168.1.100

# Check port
telnet 192.168.1.100 1883
```

### Test with Mosquitto Clients

```bash
# Subscribe
mosquitto_sub -h localhost -t test/topic -v

# Publish
mosquitto_pub -h localhost -t test/topic -m "Hello"
```

## Prevention

1. **Always test configuration** before deploying
2. **Keep backups** of working configurations
3. **Use version control** for configuration files
4. **Document changes** to configuration
5. **Test incrementally** - one change at a time
6. **Monitor logs** regularly
7. **Keep certificates secure** and backed up
