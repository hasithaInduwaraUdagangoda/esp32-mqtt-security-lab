# Docker Setup Guide

Setting up and running the Mosquitto MQTT broker using Docker.

## Prerequisites

- Docker Desktop installed
- Docker Compose installed (included with Docker Desktop)

## Docker Compose Configuration

The project uses `docker-compose.yml` to configure the Mosquitto broker:

```yaml
version: '3.8'

services:
  mosquitto:
    image: eclipse-mosquitto:2.0.18
    container_name: mqtt-broker
    ports:
      - "1883:1883"   # Unencrypted
      - "1884:1884"   # Authenticated
      - "8883:8883"   # TLS
      - "8884:8884"   # Mutual TLS
      - "8885:8885"   # TLS + Auth
      - "8886:8886"   # TLS without Auth
    volumes:
      - ./broker/mosquitto.conf:/mosquitto/config/mosquitto.conf
      - ./broker/passwd:/mosquitto/config/passwd
      - ./broker/certs:/mosquitto/certs
      - ./broker/data:/mosquitto/data
      - ./broker/logs:/mosquitto/logs
    restart: unless-stopped
    networks:
      - mqtt-network

networks:
  mqtt-network:
    driver: bridge
```

## Starting the Broker

### Start in Detached Mode
```bash
docker-compose up -d
```

### Start with Logs
```bash
docker-compose up
```

## Stopping the Broker

### Stop and Remove Containers
```bash
docker-compose down
```

### Stop but Keep Containers
```bash
docker-compose stop
```

## Managing the Broker

### View Logs
```bash
# Follow logs in real-time
docker-compose logs -f mosquitto

# View last 100 lines
docker-compose logs --tail=100 mosquitto

# View logs since specific time
docker-compose logs --since 2024-01-01T00:00:00 mosquitto
```

### Restart the Broker
```bash
docker-compose restart mosquitto
```

### Rebuild and Start
```bash
docker-compose up -d --build
```

### Access Container Shell
```bash
docker exec -it mqtt-broker sh
```

## Volume Management

### View Volumes
```bash
docker volume ls
```

### Inspect Volume
```bash
docker volume inspect mqtt_broker_data
```

### Remove Volumes (WARNING: Deletes Data)
```bash
docker-compose down -v
```

## Network Management

### View Networks
```bash
docker network ls
```

### Inspect Network
```bash
docker network inspect mqtt_mqtt-network
```

## Troubleshooting

### Broker Not Starting

Check logs:
```bash
docker-compose logs mosquitto
```

Common issues:
- Port already in use
- Configuration file errors
- Certificate file missing
- Permission issues

### Port Already in Use

Find process using the port:
```bash
# Windows
netstat -ano | findstr :1883

# Linux/Mac
lsof -i :1883
```

Kill the process if needed, or change port in `docker-compose.yml`.

### Certificate Issues

Ensure certificate files exist in `broker/certs/`:
```bash
ls -la broker/certs/
```

Verify file permissions on Linux/Mac:
```bash
chmod 644 broker/certs/*.crt
chmod 600 broker/certs/*.key
```

### Configuration Errors

Validate configuration:
```bash
docker exec -it mqtt-broker mosquitto -c /mosquitto/config/mosquitto.conf -t
```

## Testing the Broker

### Using Mosquitto Clients

Install mosquitto-clients:
```bash
# Ubuntu/Debian
sudo apt-get install mosquitto-clients

# macOS
brew install mosquitto

# Windows
# Download from https://mosquitto.org/download/
```

### Subscribe to Topic
```bash
mosquitto_sub -h localhost -p 1883 -t test/topic -v
```

### Publish to Topic
```bash
mosquitto_pub -h localhost -p 1883 -t test/topic -m "Hello MQTT"
```

### Test TLS Connection
```bash
mosquitto_sub -h localhost -p 8883 -t test/topic -v --cafile broker/certs/ca.crt
```

## Performance Tuning

### Adjust Memory Limits

Add to `docker-compose.yml`:
```yaml
services:
  mosquitto:
    deploy:
      resources:
        limits:
          memory: 512M
```

### Adjust CPU Limits

Add to `docker-compose.yml`:
```yaml
services:
  mosquitto:
    deploy:
      resources:
        limits:
          cpus: '1.0'
```

## Backup and Restore

### Backup Configuration and Certificates
```bash
tar -czf mqtt-backup.tar.gz broker/
```

### Restore
```bash
tar -xzf mqtt-backup.tar.gz
```

## Updating Mosquitto

### Pull Latest Image
```bash
docker-compose pull mosquitto
```

### Restart with New Image
```bash
docker-compose up -d
```

## Security Considerations

1. **Don't expose ports publicly** unless necessary
2. **Use strong passwords** for authentication
3. **Keep certificates secure** - don't commit to git
4. **Regularly update** Mosquitto image
5. **Monitor logs** for suspicious activity
6. **Use firewall rules** to restrict access
