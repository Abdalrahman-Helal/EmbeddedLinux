# Chapter 3: IP Addresses, Structs, and Data Munging

## 3.1 IP Addresses, Versions 4 and 6

### IPv4 (Internet Protocol Version 4)
- **Original Internet Protocol** used for most of the Internet.  
- **Address size:** 4 bytes (32 bits).  
- **Format:** Dotted-decimal, e.g., `192.0.2.111`.  
- **Current use:** Almost every website still uses IPv4.  
- **Problem – address exhaustion:**  
  - Initially, organizations like MIT, Xerox, HP, Apple were given large blocks of addresses.  
  - Today, billions of devices exist, so IPv4 addresses are running out.  
- **Loopback address:** `127.0.0.1`  
  - Always points to the **local machine**.  
  - Used for testing or internal communication without leaving the device.

### IPv6 (Internet Protocol Version 6)
- **Created to solve IPv4 shortage** by offering vastly more addresses.  
- **Address size:** 128 bits (16 bytes) → ~3.4×10³⁸ addresses.  
- **Format:** Hexadecimal, divided into **8 groups of 2 bytes** separated by colons, e.g.,  
```

2001:0db8:c9d2:aee5:73e3:934a:a5ae:9551

````
- **Compressed notation:**  
- Consecutive zeros → replaced by `::` **once per address**.  
- Leading zeros in a block can be omitted.  
- Example:  
  ```
  Full: 2001:0db8:c9d2:0012:0000:0000:0000:0051
  Compressed: 2001:db8:c9d2:12::51
  ```  
- **Loopback:** `::1` (equivalent to IPv4’s `127.0.0.1`).  
- **IPv4 compatibility:**  
- IPv4 address `192.0.2.33` can be represented inside IPv6 as `::ffff:192.0.2.33`.  
- **Reserved addresses:** Some are reserved for special use, but IPv6 has **more than enough** addresses for all devices far into the future.  

**Key Points:**
1. IPv4 → 32 bits, dotted decimal, limited addresses, loopback = 127.0.0.1.  
2. IPv6 → 128 bits, hexadecimal, compressed notation, loopback = ::1, supports IPv4 compatibility.  
3. IPv6 solves the address shortage problem and is future-proof.  

---

## 3.1.1 Subnets

- **Subnet:** Splits an IP address into:
1. **Network portion** – identifies the network.
2. **Host portion** – identifies individual devices on that network.

- **IPv4 example:**
- IP: `192.0.2.12`
- Suppose first 3 bytes = network, last byte = host → `host 12 on network 192.0.2.0`.

- **Old Class System (IPv4):**
- **Class A:** 1 byte network, 3 bytes host (~16 million hosts)
- **Class B:** 2 bytes network, 2 bytes host
- **Class C:** 3 bytes network, 1 byte host (256 hosts)

- **Netmask:**
- Defines which bits are network vs host.
- Example: `255.255.255.0`
  ```
  IP: 192.0.2.12
  Netmask: 255.255.255.0
  Network: 192.0.2.0  (192.0.2.12 AND 255.255.255.0)
  ```
- Modern networks allow **arbitrary number of network bits**, e.g., `255.255.255.252` → 30 network bits, 2 host bits.

- **CIDR Notation (Compact):**
- Format: `<IP address>/<number of network bits>`
- Examples:
  - IPv4: `192.0.2.12/30` → network = 30 bits, host = 2 bits → 2 usable hosts.
  - IPv6: `2001:db8::/32` → first 32 bits network, last 96 bits host.  
    `2001:db8:5413:4028::9db9/64` → first 64 bits network, last 64 bits host.

- **Key Points:**
1. Subnets divide IP addresses into **network + host**.
2. **Netmask** or **CIDR** defines network portion.
3. CIDR is flexible and compact; works for IPv4 and IPv6.

---

## 3.1.2 Port Numbers – Explanation

### Role of Port Numbers
- In the **Layered Network Model**:  
- **Internet Layer (IP):** identifies the device/computer on the network.  
- **Transport Layer (TCP/UDP):** identifies **services or applications** on that device.  

- **Analogy:**  
- IP address = street address of a building (device)  
- Port number = room number in that building  
- Together, IP + port = exact destination for communication  

### What is a port?
- A **port number** is a **16-bit integer** → range: `0` to `65535`  
- Used by **TCP (stream sockets)** and **UDP (datagram sockets)** to identify specific services on a host  

### Examples of Well-Known Ports

| Service | Port Number |
|---------|-------------|
| HTTP (Web) | 80 |
| Telnet | 23 |
| SMTP (Mail) | 25 |
| Game DOOM | 666 |

- **Ports < 1024** are **special** and usually need **OS privileges**  
- Ports ≥ 1024 are **user-level or dynamic ports**  

### Why Ports Matter
- A single computer can run **multiple services on the same IP**  
- Example:  
- Web server → IP 192.0.2.1, port 80  
- Mail server → same IP 192.0.2.1, port 25  
- Both services coexist because the **port differentiates them**  

### Key Takeaways
1. **Port number** = 16-bit local address for a service  
2. Works with **TCP and UDP**  
3. Lets multiple services run on **one IP**  
4. Well-known ports are standardized (HTTP = 80, SMTP = 25, etc.)  
5. Ports < 1024 → special privileges; ports ≥ 1024 → general use


