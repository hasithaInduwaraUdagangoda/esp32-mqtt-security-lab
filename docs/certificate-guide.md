# Certificate Guide

Understanding SSL/TLS certificates for MQTT security.

## Certificate Basics

### What is a Certificate?

A digital certificate is an electronic document used to prove the ownership of a public key. It includes:
- Subject information (who it belongs to)
- Public key
- Issuer information (who signed it)
- Validity period
- Digital signature

### Certificate Hierarchy

```
Root CA (Certificate Authority)
    |
    |-- Intermediate CA
        |
        |-- Server Certificate
        |-- Client Certificate
```

## Certificate Types

### CA Certificate (Certificate Authority)
- Root of trust
- Signs other certificates
- Distributed to all clients
- `ca.crt` in this lab

### Server Certificate
- Identifies the MQTT broker
- Signed by CA
- Contains broker hostname/IP
- `server.crt` and `server.key` in this lab

### Client Certificate
- Identifies MQTT clients
- Signed by CA
- Used for mutual authentication
- `client.crt` and `client.key` in this lab

## Certificate Formats

### PEM Format
- Base64 encoded
- Text format
- Commonly used on Linux/Unix
- Files end with `.crt` or `.pem`

### DER Format
- Binary format
- Used by ESP32
- Files end with `.der`

### PKCS#12 Format
- Bundled format
- Contains certificate and private key
- Password protected
- Files end with `.p12` or `.pfx`

## Converting Certificates for ESP32

ESP32 requires DER format certificates. Convert using OpenSSL:

### Convert CA Certificate to DER
```bash
openssl x509 -in ca.crt -out ca.der -outform DER
```

### Convert Client Certificate to DER
```bash
openssl x509 -in client.crt -out client.der -outform DER
```

### Convert Client Key to DER
```bash
openssl rsa -in client.key -out client.der -outform DER
```

## Certificate Validation

### Verify Certificate Chain
```bash
openssl verify -CAfile ca.crt server.crt
openssl verify -CAfile ca.crt client.crt
```

### View Certificate Details
```bash
openssl x509 -in server.crt -text -noout
openssl x509 -in client.crt -text -noout
```

### Check Certificate Expiration
```bash
openssl x509 -in server.crt -noout -dates
```

## Subject Alternative Names (SAN)

SAN allows certificates to be valid for multiple hostnames and IP addresses:

```
DNS.1 = localhost
DNS.2 = mqtt-broker
IP.1 = 127.0.0.1
IP.2 = 192.168.1.100
```

This is important for:
- Testing with different hostnames
- Multiple network interfaces
- Dynamic IP environments

## Security Best Practices

1. **Key Size**: Use at least 2048-bit keys (RSA)
2. **Hash Algorithm**: Use SHA-256 or higher
3. **Validity**: Set appropriate expiration dates
4. **Private Keys**: Never commit to version control
5. **CA Key**: Keep extremely secure
6. **Revocation**: Implement certificate revocation if needed
7. **Renewal**: Plan for certificate renewal before expiration

## Troubleshooting

### Certificate Verification Failed
- Check CA certificate is correct
- Verify certificate chain
- Check expiration dates

### Hostname Mismatch
- Ensure CN matches broker hostname
- Use SAN for multiple hostnames
- Check DNS resolution

### Key Mismatch
- Verify key and certificate match
- Check key format
- Ensure correct key type

## Common OpenSSL Commands

```bash
# Generate private key
openssl genrsa -out private.key 2048

# Generate CSR
openssl req -new -key private.key -out request.csr

# Sign certificate
openssl x509 -req -in request.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out certificate.crt -days 365

# Convert formats
openssl x509 -in cert.pem -outform DER -out cert.der
openssl rsa -in key.pem -outform DER -out key.der

# Verify certificate
openssl verify -CAfile ca.crt certificate.crt
```
