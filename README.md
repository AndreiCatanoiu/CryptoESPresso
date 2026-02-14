# CryptoESPresso

**Interactive Cryptography Visualizer Powered by ESP32**

CryptoESPresso is a portable cryptography education tool that runs entirely on an ESP32 microcontroller. No internet, no external components, just plug it in and explore how encryption works, step by step.

---

## How It Works

1. **Power on** the ESP32
2. **Connect** to the `CryptoESPresso` Wi-Fi network (password: `AndreiCatanoiu`)
3. **Type any text**, select an algorithm, and see the result

The ESP32 acts as both a **Wi-Fi Access Point** and a **Web Server**, hosting an interactive page where users can visualize cryptographic algorithms processing their input in real time.

---

## Supported Algorithms

| # | Algorithm | Type |
|---|-----------|------|
| 1 | **AES-128** | Symmetric Block Cipher |
| 2 | **AES-256** | Symmetric Block Cipher |
| 3 | **DES** | Legacy Block Cipher |
| 4 | **3DES** | Legacy Block Cipher |
| 5 | **ChaCha20** | Stream Cipher |
| 6 | **SHA-256** | Hash Function |
| 7 | **SHA-512** | Hash Function |
| 8 | **MD5** | Legacy Hash Function |
| 9 | **HMAC-SHA256** | Message Authentication |

---

## Requirements

- 1× ESP32 development board (any variant: DevKit v1, WROOM-32, etc.)
- USB cable for power
- [PlatformIO](https://platformio.org/) (VS Code extension or CLI)

---

## Educational Purpose

This project is built for **learning and demonstration purposes**. It aims to make abstract cryptographic concepts tangible by showing what actually happens inside these algorithms, not just the final output, but every transformation along the way.

Ideal for:
- Cybersecurity courses and workshops
- University projects
- CTF team training
- Personal learning
