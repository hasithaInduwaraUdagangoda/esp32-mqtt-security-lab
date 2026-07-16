# Docker Commands for Mosquitto Broker

## Start the Broker

```bash
docker-compose up -d
```

## Stop the Broker

```bash
docker-compose down
```

## View Logs

```bash
# Follow logs in real-time
docker-compose logs -f mosquitto

# View last 100 lines
docker-compose logs --tail=100 mosquitto
```

## Restart the Broker

```bash
docker-compose restart mosquitto
```

## Rebuild and Start

```bash
docker-compose up -d --build
```

## Access Broker Container

```bash
docker exec -it mqtt-broker sh
```

## Test Connection from Container

```bash
docker exec -it mqtt-broker mosquitto_sub -h localhost -t test/topic -v
```

## Clean Up

```bash
# Stop and remove containers
docker-compose down

# Remove volumes (WARNING: deletes all data)
docker-compose down -v
```

## Troubleshooting

Check if broker is running:
```bash
docker ps | grep mqtt-broker
```

Check broker status:
```bash
docker inspect mqtt-broker
```
