# Generate CA (Certificate Authority)

This script generates the Certificate Authority that will sign all server and client certificates.

## Steps

1. **Generate CA Private Key**
   ```bash
   openssl genrsa -out ca.key 2048
   ```

2. **Generate CA Certificate**
   ```bash
   openssl req -new -x509 -days 3650 -key ca.key -out ca.crt -subj "/C=US/ST=State/L=City/O=Organization/CN=CA"
   ```

## Verification

Verify the CA certificate:
```bash
openssl x509 -in ca.crt -text -noout
```

## Notes

- The CA certificate is valid for 10 years (3650 days)
- Keep `ca.key` secure - it can sign any certificate
- Distribute `ca.crt` to all clients for verification
