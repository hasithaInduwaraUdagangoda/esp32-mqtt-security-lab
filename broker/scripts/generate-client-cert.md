# Generate Client Certificate

This script generates client certificates for ESP32 devices or other MQTT clients.

## Steps

1. **Generate Client Private Key**
   ```bash
   openssl genrsa -out client.key 2048
   ```

2. **Generate Client CSR (Certificate Signing Request)**
   ```bash
   openssl req -new -key client.key -out client.csr -subj "/C=US/ST=State/L=City/O=Organization/CN=esp32-client"
   ```

3. **Sign Client Certificate with CA**
   ```bash
   openssl x509 -req -in client.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client.crt -days 3650 -sha256
   ```

## For Multiple Clients

For each client, repeat the steps with a unique CN:

```bash
# Client 1
openssl genrsa -out client1.key 2048
openssl req -new -key client1.key -out client1.csr -subj "/C=US/ST=State/L=City/O=Organization/CN=esp32-client-1"
openssl x509 -req -in client1.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client1.crt -days 3650 -sha256

# Client 2
openssl genrsa -out client2.key 2048
openssl req -new -key client2.key -out client2.csr -subj "/C=US/ST=State/L=City/O=Organization/CN=esp32-client-2"
openssl x509 -req -in client2.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out client2.crt -days 3650 -sha256
```

## Verification

Verify the client certificate:
```bash
openssl x509 -in client.crt -text -noout
```

## Notes

- Each client should have a unique CN (Common Name)
- The client certificate is valid for 10 years
- For ESP32, you'll need to convert certificates to DER format
