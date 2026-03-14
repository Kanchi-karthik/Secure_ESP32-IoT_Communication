# Secure_ESP32-IoT_Communication

## Overview

**Secure_ESP32-IoT_Communication** is a cybersecurity-focused IoT project that demonstrates **secure communication between an ESP32 microcontroller and a cloud database**.

The project integrates **Bluetooth communication, WiFi connectivity, encoded message transmission, a Node.js bridge server, and Firebase Realtime Database**.

Additionally, the system includes **network packet analysis using Wireshark** to monitor how encoded data travels through the network.

This project highlights key cybersecurity concepts in IoT systems, including:

* Secure device communication
* Encoded data transmission
* Device authentication
* Cloud-based data storage
* Network-level monitoring and analysis

---

# System Architecture

The system architecture consists of multiple components working together to transmit data securely from an IoT device to the cloud.

```
Mobile Device
      │
      │ Bluetooth Message
      ▼
ESP32 Device
      │
      │ Encoded HTTP Request
      ▼
Node.js Bridge Server
      │
      │ HTTPS Communication
      ▼
Firebase Realtime Database
```

---

# Data Flow

1. A **mobile phone sends a message** to the ESP32 device using Bluetooth.
2. The **ESP32 receives the message** and formats it with device information.
3. The message is **encoded before transmission**.
4. The encoded message is **sent via HTTP** to a Node.js bridge server.
5. The **bridge server decodes the message** and forwards it to Firebase.
6. **Firebase stores the message** as a new database entry.

---

# Hardware Requirements

| Component       | Description                              |
| --------------- | ---------------------------------------- |
| ESP32 Dev Board | Main IoT device used in the project      |
| Smartphone      | Sends Bluetooth messages                 |
| Laptop / PC     | Runs Node.js bridge server and Wireshark |
| WiFi Hotspot    | Provides internet connectivity           |

---

# Software Requirements

| Tool                       | Purpose                           |
| -------------------------- | --------------------------------- |
| Arduino IDE                | ESP32 firmware development        |
| Node.js                    | Bridge server runtime             |
| Firebase Realtime Database | Cloud database storage            |
| Wireshark                  | Network packet analysis           |
| Bluetooth Terminal App     | Send Bluetooth messages           |
| GitHub                     | Version control and documentation |

---

# Repository Structure

```
Secure_ESP32-IoT_Communication
│
├── esp32_firmware
│   ├── Secure_ESP32_IoT.ino
│   ├── cloud_upload.h
│   └── encryption.h
│
├── bridge_server
│   ├── server.js
│   └── package.json
│
├── docs
│   ├── Wireshark_capture-1.png
│   ├── Wireshark_capture-2.png
│   ├── firebase_database.png
│   └── System_Architecture.png
│
├── wireshark_filters.txt
│
└── README.md
```

---

# ESP32 Firmware

The ESP32 firmware is responsible for handling:

* Bluetooth communication
* WiFi connectivity
* Message formatting
* Data encoding
* Cloud communication

### Firmware Files

| File                 | Description                            |
| -------------------- | -------------------------------------- |
| Secure_ESP32_IoT.ino | Main ESP32 program                     |
| cloud_upload.h       | Handles HTTP communication with server |
| encryption.h         | Encodes messages before transmission   |

### Key Features

* Runtime WiFi selection
* Bluetooth message reception
* Device metadata formatting
* Encoded message transmission
* HTTP communication with bridge server

---

# Bridge Server

The **bridge server** is implemented using **Node.js and Express**.

Its purpose is to act as an intermediary between the ESP32 device and Firebase.

### Responsibilities

* Receive HTTP POST requests from ESP32
* Verify device authentication key
* Decode encoded message payload
* Store messages in Firebase Realtime Database

---

# Running the Bridge Server

### Install Dependencies

```
npm install express node-fetch
```

### Start the Server

```
node server.js
```

### Expected Output

```
ESP32 Secure Bridge Server Running
Listening on port 3000
```

---

# ESP32 WiFi Startup

When the ESP32 starts, it scans available WiFi networks.

### Example Output

```
Scanning WiFi...

1: Kanchi_Mobile
2: Network2
3: Network3
```

After selecting the network:

```
WiFi Connected
IP Address: 172.25.77.82
ESP32 MAC: 64:B7:08:4F:D0:10
```

### Bluetooth Initialization

```
Bluetooth Ready
Connect mobile to ESP32_NODE
```

---

# Example Communication Flow

### Message Sent from Mobile

```
Hello
```

### ESP32 Formatted Message

```
ESP32[64:B7:08:4F:D0:10](Kanchi_Mobile,172.25.77.82):Hello
```

### Encoded Network Payload

```
RVNQMzJbNjQ6Qjc6MDg6NEY6RDA6MTBdKEthbmNoaV9Nb2JpbGUsMTcyLjI1Ljc3LjgyKTpIZWxsbw==
```

### Bridge Server Output

```
Encrypted data:
RVNQMzJbNjQ6Qjc6MDg6NEY6RDA6MTBdKEthbmNoaV9Nb2JpbGUsMTcyLjI1Ljc3LjgyKTpIZWxsbw==

Decrypted message:
ESP32[64:B7:08:4F:D0:10](Kanchi_Mobile,172.25.77.82):Hello
```

---

# Wireshark Network Analysis

Wireshark was used to inspect network traffic generated by the ESP32 device.

### Filter Used

```
http && ip.addr == 172.25.77.82
```

This filter isolates HTTP packets generated by the ESP32.

### Captured Packets

```
POST / HTTP/1.1
HTTP/1.1 200 OK
```

These packets represent the request and response communication between the ESP32 device and the bridge server.

---

# Wireshark Screenshot

```
docs/wireshark_capture.png
```

---

# Firebase Database Storage

The bridge server forwards decoded messages to **Firebase Realtime Database**.

Each message becomes a new database entry.

### Example Structure

```
ESP32
  messages
     -Nabc123
        message: ESP32[MAC](wifi,ip):Hello
        timestamp: 1710000000
```

---

# Database Screenshot

```
docs/firebase_database.png
```

---

# Wireshark Filters Reference

Useful filters for analyzing ESP32 network traffic:

```
http
ip.addr == 172.25.77.82
http && ip.addr == 172.25.77.82
tcp.port == 3000
http.request
http.response
```

---

# Security Features

| Feature               | Description                                      |
| --------------------- | ------------------------------------------------ |
| Encoded Transmission  | Messages are encoded before network transmission |
| Device Authentication | API key verification for devices                 |
| Cloud Storage         | Secure data storage using Firebase               |
| Network Monitoring    | Packet inspection using Wireshark                |

---

# Applications

This architecture can be used in multiple IoT and cybersecurity environments:

* Smart home monitoring systems
* IoT telemetry and sensor networks
* Industrial IoT monitoring
* Cybersecurity research environments
* Network traffic analysis studies

---

# Conclusion

This project demonstrates how an IoT device such as the **ESP32** can securely communicate with cloud infrastructure while enabling **network-level monitoring using Wireshark**.

By combining **embedded systems, networking protocols, and cloud databases**, this project provides a practical implementation of **secure IoT communication architecture** suitable for research, cybersecurity analysis, and real-world IoT applications.

---

# Author

**Karthik**

M.Tech – Computer Science and Engineering
IoT Security Project
