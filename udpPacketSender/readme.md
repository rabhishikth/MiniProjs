# UDP Packet Sender (Qt)

A Qt/C++ GUI-based UDP packet sender used to generate and transmit configurable UDP traffic for testing, debugging, and validation on LAN networks.

---

## Features

- Configurable **destination IP address and UDP port**
- Fixed-size UDP payload transmission
- Optional **rate-controlled sending** (kbps / KB per second)
- Supports **incrementing payload counter** (last byte or multi-byte counter)
- Real-time **hex data logging** in the GUI
- Precise timer-driven transmission using `QTimer`
- Validated using **Wireshark** and **Hercules**

---

## Use Cases

- Network throughput and stress testing
- UDP protocol simulation
- Embedded and system-level network debugging
- Packet inspection and validation
- LAN communication testing

---

## Build Requirements

- Qt 5 or Qt 6
- qmake build system
- C++17 compatible compiler

---

## Build Instructions

```bash
qmake
make
```

On Windows (Qt Creator):
- Open the `.pro` file
- Configure kit
- Build and Run

---

## Application Controls

| Control | Description |
|------|------------|
| Destination IP | Target receiver IP address |
| Port | Target UDP port |
| Payload Size | Number of bytes per UDP packet |
| Interval / Tick | Timer interval for sending |
| Pattern Byte | Hex byte used to fill payload |
| Increment Content | Enables payload counter |
| Rate Mode | Enables bandwidth-controlled sending |
| Log Window | Displays sent packet details in hex |

---

## Payload Behavior

### Without Increment Content
- Entire payload is filled with the selected pattern byte

### With Increment Content Enabled
- Payload size remains constant
- A forward-counting counter is embedded in the **last byte(s)** of the payload
- Counter increases every packet and supports values beyond 255 using multi-byte encoding

Example (last-byte increment):
```
00 00 00 ... 00 01
00 00 00 ... 00 02
```

---

## Rate Control

When rate mode is enabled:
- Target bandwidth can be set in **kbps** or **KB/s**
- Application sends packets in bursts per timer tick
- Payload size and tick interval can be tuned to achieve desired throughput

Recommended values:
- Payload size: 1200–1400 bytes
- Tick interval: 20–50 ms

---

## Testing & Verification

- **Hercules**: Used as UDP receiver for functional testing
- **Wireshark**: Used to verify packet structure, payload content, and throughput

---

## Notes

- Maximum UDP payload size is **65507 bytes**
- To avoid IP fragmentation, keep payload size below MTU (≈1400 bytes)
- Network checksum offloading may cause false warnings in Wireshark

---

## Author

Developed as a reusable UDP traffic generation and testing utility using Qt and C++.

---

## License

This project is intended for internal testing and educational purposes.

