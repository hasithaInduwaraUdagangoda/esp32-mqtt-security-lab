# Generate Server Certificate

This script generates the server certificate for the MQTT broker.

## Steps

1. **Generate Server Private Key**
   ```bash
   openssl genrsa -out server.key 2048
   ```

2. **Generate Server CSR (Certificate Signing Request)**
   ```bash
   openssl req -new -key server.key -out server.csr -subj "/C=US/ST=State/L=City/O=Organization/CN=mqtt-broker"
   ```

3. **Sign Server Certificate with CA**
   ```bash
   openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 3650 -sha256
   ```

## With Subject Alternative Names (SAN)

If you need to include IP addresses or multiple hostnames:

1. **Create SAN configuration file** (san.cnf already exists)
2. **Generate CSR with SAN**
   ```bash
   openssl req -new -key server.key -out server.csr -config san.cnf
   ```
3. **Sign with SAN extension**
   ```bash
   openssl x509 -req -in server.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out server.crt -days 3650 -sha256 -extfile san.cnf -extensions v3_req
   ```

## Verification

Verify the server certificate:
```bash
openssl x509 -in server.crt -text -noout
```

## Notes

- The server certificate is valid for 10 years
- The CN (Common Name) should match the broker hostname
- SAN allows multiple hostnames and IP addresses
