# Docker OpenSSL Certificate Generation Guide

This guide details the step-by-step procedure to generate X.509 TLS certificates (CA, Server, Client) for Mosquitto MQTT Broker using Docker and `frapsoft/openssl`.

---

## Prerequisites & Requirements

- Docker installed and running.
- Local Broker IP Address configured (Default SAN IP: `10.26.32.36`).
- Command Prompt (cmd) running from the project root directory.

---

## Step-by-Step Command Execution

### Step 1 — Navigate to Project Directory
```cmd
cd C:\Users\hasit\mqtt-secure-lab
```

---

### Step 2 — Stop Mosquito Broker Containers
```cmd
docker compose down
```

---

### Step 3 — Clean Old Certificates
```cmd
del mosquitto\certs\*.crt
del mosquitto\certs\*.csr
del mosquitto\certs\*.key
del mosquitto\certs\*.srl
del mosquitto\certs\san.cnf
```

Verify that the folder is empty:
```cmd
dir mosquitto\certs
```

---

### Step 4 — Pull OpenSSL Docker Image
```cmd
docker pull frapsoft/openssl
```

---

### Step 5 — Generate CA Private Key
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/ca.key 2048
```

---

### Step 6 — Generate CA Certificate
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl req -x509 -new -nodes -key /certs/ca.key -sha256 -days 3650 -out /certs/ca.crt -subj "/CN=Hasitha-CA"
```

---

### Step 7 — Generate Server Private Key
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/server.key 2048
```

---

### Step 8 — Generate Server CSR (Certificate Signing Request)
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl req -new -key /certs/server.key -out /certs/server.csr -subj "/CN=10.26.32.36"
```

---

### Step 9 — Create SAN (Subject Alternative Name) Configuration File
```cmd
echo subjectAltName=IP:10.26.32.36> mosquitto\certs\san.cnf
```

---

### Step 10 — Generate Server Certificate
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl x509 -req -in /certs/server.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/server.crt -days 3650 -sha256 -extfile /certs/san.cnf
```

---

### Step 11 — Generate Client Private Key
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl genrsa -out /certs/client.key 2048
```

---

### Step 12 — Generate Client CSR
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl req -new -key /certs/client.key -out /certs/client.csr -subj "/CN=esp32-client"
```

---

### Step 13 — Generate Client Certificate
```cmd
docker run --rm -v "%CD%\mosquitto\certs:/certs" frapsoft/openssl x509 -req -in /certs/client.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/client.crt -days 3650 -sha256
```

---

### Step 14 — Verify Generated Certificate Files
```cmd
dir mosquitto\certs
```

Expected files in `mosquitto\certs`:
- `ca.crt`
- `ca.key`
- `ca.srl`
- `server.crt`
- `server.csr`
- `server.key`
- `client.crt`
- `client.csr`
- `client.key`
- `san.cnf`

---

### Step 15 — Start Docker Containers
```cmd
docker compose up -d
```

---

### Step 16 — Verify Mosquitto Broker Logs
```cmd
docker logs mosquitto-broker
```

Look for active listening ports: `1883`, `1884`, `8883`, `8884`, `8885`, `8886`.

---

## Target Usage by Security Task

| Task | Port | Protocol / Security | Certificates Needed on ESP32 |
|---|---|---|---|
| **Task 01** | 1883 | Unencrypted | None |
| **Task 02** | 1884 | Username / Password | None |
| **Task 03** | 8883 | TLS (No Auth) | `ca.crt` |
| **Task 04** | 8884 | TLS (Mutual Authentication) | `ca.crt`, `client.crt`, `client.key` |
| **Task 05** | 8885 | TLS + Username / Password | `ca.crt` |
| **Task 06** | 8886 | TLS (No Auth) | `ca.crt` |
| **Task 07** | 1883 | LWT / QoS / Retain | None |
