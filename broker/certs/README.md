# TLS Certificates & Generation Guide

This folder contains all SSL/TLS certificates used for securing MQTT communication between the ESP32 client and Mosquitto broker.

Certificates are generated using Docker and `frapsoft/openssl`.

---

## Folder Structure

```text
certs/
│
├── ca.crt          # Root Certificate Authority
├── ca.key          # Root CA Private Key (ignored by git)
├── ca.srl          # CA Serial Number tracking
├── server.crt      # Mosquitto Broker Certificate
├── server.csr      # Server Signing Request
├── server.key      # Server Private Key (ignored by git)
├── client.crt      # ESP32 Client Certificate
├── client.csr      # Client Signing Request
├── client.key      # Client Private Key (ignored by git)
├── san.cnf         # Subject Alternative Name IP Config
└── README.md       # Documentation
```

> [!IMPORTANT]
> Private key files (`ca.key`, `server.key`, `client.key`) are sensitive and intentionally ignored in `.gitignore`.

---

## Task Certificate Requirements Matrix

| Task | Port | Security Configuration | Required Certificates on ESP32 |
|---|---|---|---|
| **Task 01** | 1883 | Unencrypted | None |
| **Task 02** | 1884 | Username + Password | None |
| **Task 03** | 8883 | TLS (No Auth) | `ca.crt` |
| **Task 04** | 8884 | TLS + Client Certificate Authentication | `ca.crt`, `client.crt`, `client.key` |
| **Task 05** | 8885 | TLS + Username/Password Authentication | `ca.crt` |
| **Task 06** | 8886 | TLS (No Auth) | `ca.crt` |
| **Task 07** | 1883 | Birth / LWT / QoS / Retain | None |

---

## Certificate Generation Procedure (16 Steps via Docker)

Run the following commands sequentially in Command Prompt (`cmd`) from the root directory:

### Step 1 — Navigate to Project Root
```cmd
cd C:\Users\hasit\mqtt-secure-lab
```

### Step 2 — Stop Mosquitto Broker
```cmd
docker compose down
```

### Step 3 — Remove Previous Certificates
```cmd
del mosquitto\certs\*.crt
del mosquitto\certs\*.csr
del mosquitto\certs\*.key
del mosquitto\certs\*.srl
del mosquitto\certs\san.cnf
```

Check directory (should be empty):
```cmd
dir mosquitto\certs
```

### Step 4 — Pull OpenSSL Docker Image
```cmd
docker pull frapsoft/openssl
```

### Step 5 — Generate Root CA Private Key
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/ca.key 2048
```

### Step 6 — Generate Self-Signed Root CA Certificate
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl req -x509 -new -nodes -key /certs/ca.key -sha256 -days 3650 -out /certs/ca.crt -subj "/CN=Hasitha-CA"
```

### Step 7 — Generate Server Private Key
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/server.key 2048
```

### Step 8 — Generate Server Certificate Signing Request (CSR)
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl req -new -key /certs/server.key -out /certs/server.csr -subj "/CN=10.26.32.36"
```

### Step 9 — Create Subject Alternative Name (SAN) Configuration
```cmd
echo subjectAltName=IP:10.26.32.36> mosquitto\certs\san.cnf
```

### Step 10 — Generate & Sign Server Certificate
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl x509 -req -in /certs/server.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/server.crt -days 3650 -sha256 -extfile /certs/san.cnf
```

### Step 11 — Generate Client Private Key
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/client.key 2048
```

### Step 12 — Generate Client Certificate Signing Request (CSR)
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl req -new -key /certs/client.key -out /certs/client.csr -subj "/CN=esp32-client"
```

### Step 13 — Generate & Sign Client Certificate
```cmd
docker run --rm -v "C:\Users\hasit\mqtt-secure-lab\mosquitto\certs:/certs" frapsoft/openssl x509 -req -in /certs/client.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/client.crt -days 3650 -sha256
```

### Step 14 — Verify File Creation
```cmd
dir mosquitto\certs
```

Expected output includes `ca.crt`, `ca.key`, `server.crt`, `server.key`, `client.crt`, `client.key`, `san.cnf`, etc.

### Step 15 — Start Mosquitto Broker Container
```cmd
docker compose up -d
```

### Step 16 — Inspect Broker Logs
```cmd
docker logs mosquitto-broker
```

Verify that all sockets on ports `1883`, `1884`, `8883`, `8884`, `8885`, and `8886` open cleanly.