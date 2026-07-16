@echo off
REM Script to regenerate all SSL/TLS certificates using Docker OpenSSL

echo ===================================================
echo   Mosquitto MQTT Broker Certificate Generator
echo ===================================================

SET BROKER_IP=10.26.32.36
SET CERTS_DIR=%CD%\mosquitto\certs

IF NOT EXIST "%CERTS_DIR%" (
    SET CERTS_DIR=%CD%\certs
)

echo Certificate target folder: %CERTS_DIR%

REM Step 2 - Stop Broker
echo Stopping Docker containers...
docker compose down

REM Step 3 - Remove Old Certificates
echo Cleaning old certificates...
del /Q "%CERTS_DIR%\*.crt" 2>nul
del /Q "%CERTS_DIR%\*.csr" 2>nul
del /Q "%CERTS_DIR%\*.key" 2>nul
del /Q "%CERTS_DIR%\*.srl" 2>nul
del /Q "%CERTS_DIR%\san.cnf" 2>nul

REM Step 4 - Pull Docker Image
echo Pulling OpenSSL container...
docker pull frapsoft/openssl

REM Step 5 & 6 - CA Key and Cert
echo Generating Root CA key and certificate...
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl genrsa -out /certs/ca.key 2048
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl req -x509 -new -nodes -key /certs/ca.key -sha256 -days 3650 -out /certs/ca.crt -subj "/CN=Hasitha-CA"

REM Step 7, 8, 9, 10 - Server Key, CSR, SAN, Cert
echo Generating Server key, CSR, SAN, and signing certificate...
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl genrsa -out /certs/server.key 2048
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl req -new -key /certs/server.key -out /certs/server.csr -subj "/CN=%BROKER_IP%"
echo subjectAltName=IP:%BROKER_IP%> "%CERTS_DIR%\san.cnf"
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl x509 -req -in /certs/server.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/server.crt -days 3650 -sha256 -extfile /certs/san.cnf

REM Step 11, 12, 13 - Client Key, CSR, Cert
echo Generating Client key, CSR, and signing certificate...
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl genrsa -out /certs/client.key 2048
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl req -new -key /certs/client.key -out /certs/client.csr -subj "/CN=esp32-client"
docker run --rm -v "%CERTS_DIR%:/certs" frapsoft/openssl x509 -req -in /certs/client.csr -CA /certs/ca.crt -CAkey /certs/ca.key -CAcreateserial -out /certs/client.crt -days 3650 -sha256

REM Step 14 - Verify files
echo Verifying files...
dir "%CERTS_DIR%"

REM Step 15 - Start Docker
echo Starting Docker containers...
docker compose up -d

REM Step 16 - Show Logs
echo Fetching docker logs...
docker logs mosquitto-broker

echo Certificate generation process completed!
