# ESP32-Motion-Alert-System 🚨

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-Compatible-blue)](https://platformio.org/)
[![ESP32](https://img.shields.io/badge/Hardware-ESP32-green)](https://www.espressif.com/en/products/socs/esp32)
[![Security](https://img.shields.io/badge/Security-Enhanced-red)](./SECURITY.md)

> **🔒 Security Update:** ระบบความปลอดภัยได้รับการปรับปรุงแล้ว! ข้อมูลส่วนบุคคลถูกแยกออกจาก source code

โปรเจคระบบตรวจจับการเคลื่อนไหว (Motion Detection System) โดยใช้เซ็นเซอร์ PIR และ ESP32 พร้อมระบบแจ้งเตือนผ่าน LINE Messaging API แบบเรียลไทม์

## 📋 รายละเอียดโปรเจค

ระบบตรวจจับการเคลื่อนไหวแบบอัตโนมัติที่ใช้ **Interrupt-based detection** เพื่อประสิทธิภาพสูง สามารถส่งการแจ้งเตือนผ่าน LINE ทันทีเมื่อตรวจพบการเคลื่อนไหวในพื้นที่ที่ต้องการเฝ้าระวัง 

**เหมาะสำหรับ:**
- 🏠 ระบบรักษาความปลอดภัยในบ้าน
- 🏢 การตรวจสอบการเข้าออกสำนักงาน
- 🏪 ระบบแจ้งเตือนลูกค้าเข้าร้าน
- 🚪 การตรวจสอบประตูหลัก
- 📦 การเฝ้าระวังพื้นที่เก็บของ

## ✨ ฟีเจอร์หลัก

### 🎯 **ฟีเจอร์หลัก**
- 🔍 **ตรวจจับการเคลื่อนไหวแบบ Interrupt** - ใช้เซ็นเซอร์ PIR แบบประสิทธิภาพสูง
- 📱 **แจ้งเตือนผ่าน LINE แบบเรียลไทม์** - ส่งข้อความทันทีเมื่อตรวจพบ
- ⏰ **ระบบ Cooldown อัจฉริยะ** - ป้องกันการแจ้งเตือนซ้ำๆ (ปรับได้ 5-300 วินาที)
- 🌐 **การเชื่อมต่อ WiFi ที่เสถียร** - Auto-reconnection และ retry mechanism
- 📊 **Serial Monitor แบบละเอียด** - ติดตามสถานะแบบเรียลไทม์

### 🔒 **ความปลอดภัยและเสถียรภาพ**
- �️ **HTTPS Support** - การเชื่อมต่อ LINE API แบบปลอดภัย
- 🔐 **Credentials Management** - แยกข้อมูลส่วนบุคคลออกจาก source code
- 🔄 **Auto-reconnection** - เชื่อมต่อ WiFi อัตโนมัติเมื่อหลุด
- ⚡ **Memory Efficient** - ใช้ Static JSON เพื่อประหยัด RAM
- 🎛️ **Configurable Settings** - ปรับแต่งได้ผ่าน config.h

### 🆕 **ฟีเจอร์ใหม่ล่าสุด**
- 🔧 **Multi-environment Build** - รองรับ debug และ release mode
- 📈 **Enhanced Error Handling** - ระบบจัดการข้อผิดพลาดที่ครอบคลุม
- 🎯 **Quick Start Guide** - คู่มือเริ่มต้นใช้งานแบบเร็ว (5 นาที)
- 📝 **Comprehensive Documentation** - เอกสารครบถ้วนทุกระดับ

## � Quick Start

> **⚡ เริ่มต้นใช้งานได้ใน 5 นาที!** อ่าน [QUICKSTART.md](QUICKSTART.md) สำหรับคำแนะนำแบบเร็ว

### การติดตั้งแบบย่อ

1. **Clone repository:** `git clone https://github.com/Ohmies/ESP-Project-MotionAlert.git`
2. **Setup credentials:** `cp include/credentials.h.example include/credentials.h`
3. **แก้ไข WiFi & LINE API:** ใส่ข้อมูลจริงใน `credentials.h`
4. **ต่อสาย:** ESP32 (3.3V, GND, GPIO4) ↔ PIR Sensor (VCC, GND, OUT)
5. **Upload:** `pio run --target upload`

**📖 คำแนะนำละเอียด:** อ่าน [QUICKSTART.md](QUICKSTART.md)

## �🛠️ อุปกรณ์ที่ต้องใช้

### 💻 **Hardware Requirements**

| อุปกรณ์ | รายละเอียด | จำนวน | ราคาประมาณ |
|---------|-------------|---------|-------------|
| **ESP32 Dev Board** | ESP32-WROOM-32 หรือเทียบเท่า | 1 ตัว | ~300-500 บาท |
| **PIR Motion Sensor** | HC-SR501 หรือเทียบเท่า | 1 ตัว | ~50-100 บาท |
| **Jumper Wires** | Male-Female, 3 เส้น | 1 ชุด | ~30-50 บาท |
| **Breadboard** | Half-size (ไม่บังคับ) | 1 อัน | ~50-80 บาท |
| **Power Supply** | 5V USB หรือ 3.3V | 1 อัน | ~100-200 บาท |

**💰 งบประมาณรวม: ~530-930 บาท**

### 💾 **Software Requirements**

#### ตัวเลือกที่ 1: PlatformIO (แนะนำ)

- ✅ **VS Code** - Text editor หลัก
- ✅ **PlatformIO Extension** - Platform สำหรับ ESP32
- ✅ **ไม่ต้องติดตั้งเพิ่ม** - จัดการ library อัตโนมัติ

#### ตัวเลือกที่ 2: Arduino IDE

- ✅ **Arduino IDE 2.0+** - IDE หลัก
- ✅ **ESP32 Board Package** - รองรับ ESP32
- ✅ **ArduinoJson Library** - จัดการ JSON

### 📱 **การตั้งค่า LINE Bot**

**ขั้นตอนสำคัญ:**
1. 🔑 **LINE Developers Account** - สมัครฟรีที่ [developers.line.biz](https://developers.line.biz/)
2. 🤖 **สร้าง Messaging API Channel** - ได้รับ Channel Access Token
3. 🆔 **หา User ID** - เพื่อส่งข้อความหาตัวเอง

**⏰ เวลาที่ใช้:** ~5-10 นาที

## 📱 การติดตั้ง LINE Messaging API

### 1. สร้าง LINE Channel
1. เข้าไปที่ [LINE Developers Console](https://developers.line.biz/)
2. สร้าง Provider ใหม่ (ถ้ายังไม่มี)
3. สร้าง Messaging API Channel ใหม่
4. ไปที่แท็บ "Messaging API" และคัดลอก **Channel Access Token**

### 2. หา User ID หรือ Group ID
1. เพิ่มบอท LINE ที่สร้างขึ้นเป็นเพื่อน
2. ใช้เครื่องมือเช่น [LINE User ID Finder](https://developers.line.biz/en/docs/messaging-api/getting-user-ids/) เพื่อหา User ID
3. หรือใช้ Webhook URL เพื่อรับ User ID เมื่อมีการส่งข้อความไปยังบอท

## 🔌 การต่อสาย (Wiring Diagram)

```
ESP32        PIR Sensor (HC-SR501)
-----        --------------------
3.3V   <-->  VCC
GND    <-->  GND
GPIO4  <-->  OUT
```

### รายละเอียดการต่อสาย
| ESP32 Pin | PIR Sensor Pin | Description |
|-----------|----------------|-------------|
| 3.3V      | VCC           | แหล่งจ่ายไฟ |
| GND       | GND           | กราวด์ |
| GPIO4     | OUT           | สัญญาณเอาต์พุต |

## ⚙️ การติดตั้งและการใช้งาน

> **🔒 ข้อมูลสำคัญ:** ระบบได้รับการปรับปรุงด้านความปลอดภัยแล้ว! ข้อมูลส่วนบุคคลถูกแยกออกจาก source code

### 🚀 **การติดตั้งแบบเร็ว (แนะนำ)**

```bash
# 1. Clone และเข้าโฟลเดอร์
git clone https://github.com/Ohmies/ESP-Project-MotionAlert.git
cd ESP-Project-MotionAlert

# 2. รันสคริปต์ setup อัตโนมัติ (macOS/Linux)
chmod +x setup.sh
./setup.sh

# 3. แก้ไข credentials (สร้างไฟล์ใหม่จาก template)
cp include/credentials.h.example include/credentials.h
nano include/credentials.h  # แก้ไขใส่ข้อมูลจริง

# 4. Uncomment ใน main.cpp
# เปลี่ยน: // #include "credentials.h" 
# เป็น:    #include "credentials.h"

# 5. Upload ไปยัง ESP32
pio run --target upload && pio device monitor
```

### 📋 **การติดตั้งแบบละเอียด**

#### Step 1: เตรียมโปรเจค

```bash
# Clone repository
git clone https://github.com/Ohmies/ESP-Project-MotionAlert.git
cd ESP-Project-MotionAlert

# ตรวจสอบโครงสร้างไฟล์
ls -la
```

#### Step 2: ติดตั้ง Dependencies

**สำหรับ PlatformIO:**
```bash
# ติดตั้งและ build
pio lib install
pio run
```

**สำหรับ Arduino IDE:**
- เปิดไฟล์ `src/main.cpp`
- ติดตั้ง ArduinoJson library (v7.0.0)
- เลือก Board: ESP32 Dev Module

#### Step 3: ตั้งค่า Credentials (เลือก 1 วิธี)

**🔒 วิธีที่ 1: ใช้ไฟล์ credentials.h (ปลอดภัย - แนะนำ)**

```bash
# สร้างไฟล์ credentials.h จาก template
cp include/credentials.h.example include/credentials.h
```

แก้ไขใน `include/credentials.h`:
```cpp
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WiFi Configuration
const char* WIFI_SSID = "ชื่อWiFiของคุณ";
const char* WIFI_PASSWORD = "รหัสผ่านWiFi";

// LINE Messaging API Configuration  
const char* LINE_CHANNEL_ACCESS_TOKEN = "Channel_Access_Token_จาก_LINE";
const char* LINE_USER_ID = "User_ID_ของคุณ";

#endif // CREDENTIALS_H
```

จากนั้นใน `src/main.cpp` หาบรรทัด:
```cpp
// #include "credentials.h"  // ← ลบ // ออก
```

**⚠️ วิธีที่ 2: แก้ไขใน main.cpp โดยตรง (สำหรับทดสอบ)**

```cpp
// หาบรรทัดเหล่านี้ใน src/main.cpp และแก้ไข:
const char *ssid = "ชื่อWiFiของคุณ";
const char *password = "รหัสผ่านWiFi";
const char *channelAccessToken = "Channel_Access_Token";
const char *userID = "User_ID_ของคุณ";
```

#### Step 4: ต่อสาย Hardware

> **⚡ ระวัง:** ตัดไฟ ESP32 ก่อนต่อสายทุกครั้ง!

**การต่อสายแบบละเอียด:**

| ESP32 Pin | PIR Sensor | สายสี (แนะนำ) | หมายเหตุ |
|-----------|------------|----------------|----------|
| **3.3V** | VCC | 🔴 แดง | ไฟเลี้ยง (ไม่ใช้ 5V!) |
| **GND** | GND | ⚫ ดำ | กราวด์ |  
| **GPIO4** | OUT | 🟡 เหลือง | สัญญาณ (เปลี่ยนได้ใน config.h) |

**ขั้นตอนการต่อสาย:**
1. ตัดไฟ ESP32 (ถอด USB)
2. ต่อ GND ก่อน (สำคัญ!)
3. ต่อ VCC (3.3V)
4. ต่อ Signal (GPIO4) สุดท้าย
5. ตรวจสอบอีกครั้ง
6. เสียบ USB กลับ

#### Step 5: Upload และทดสอบ

**สำหรับ PlatformIO:**
```bash
# Build และ Upload
pio run --target upload

# เปิด Serial Monitor
pio device monitor
```

**สำหรับ Arduino IDE:**
1. เลือก Port ที่ถูกต้อง
2. คลิก Upload (Ctrl+U)
3. เปิด Serial Monitor (Ctrl+Shift+M)
4. ตั้ง Baud Rate: 115200

#### Step 6: ตรวจสอบผลลัพธ์

**Serial Monitor ควรแสดง:**
```text
🌐 Connecting to WiFi: [ชื่อ WiFi]
✅ WiFi connected!
🌐 IP Address: 192.168.1.xxx
⏰ Time synchronized.
✅ Connected to LINE API.
✅ Message sent successfully!
```

**ใน LINE ควรได้รับ:**
**ใน LINE ควรได้รับ:**
- ข้อความต้อนรับ: "🚀 ระบบตรวจจับความเคลื่อนไหว PIR พร้อมทำงานแล้ว! 🕵️"

### 📋 **ทดสอบการทำงาน**

1. **รอ PIR sensor warm-up** (1-2 นาที)
2. **เลื่อนมือหน้าเซ็นเซอร์** ช้าๆ ระยะ 1-3 เมตร
3. **ตรวจสอบ Serial Monitor และ LINE**

**ผลลัพธ์ที่ควรได้:**
```text
🚨 ตรวจพบการเคลื่อนไหว!
📩 Sending JSON: {...}
✅ Message sent successfully!
```

## 📁 โครงสร้างโปรเจค

```text
ESP-Project-MotionAlert/
├── 📄 README.md                    # คู่มือการใช้งานฉบับเต็ม
├── ⚡ QUICKSTART.md               # คู่มือเริ่มต้นใช้งานเร็ว (5 นาที)
├── 🔧 platformio.ini              # การตั้งค่า PlatformIO + Build environments
├── 🔒 SECURITY.md                 # นโยบายและแนวทางความปลอดภัย
├── 📊 PROJECT_REPORT.md           # รายงานความสมบูรณ์ของโปรเจค
├── 🤝 CONTRIBUTING.md             # คู่มือการมีส่วนร่วมในการพัฒนา
├── 📜 CHANGELOG.md                # บันทึกการเปลี่ยนแปลง
├── ⚖️ LICENSE                     # สัญญาอนุญาต MIT
├── 🔌 CIRCUIT.md                  # รายละเอียดการต่อสายและ Circuit diagram
├── 🛠️ setup.sh                   # สคริปต์ setup อัตโนมัติ (macOS/Linux)
├── 📂 src/
│   └── 💻 main.cpp                # โค้ดหลัก (พร้อม security updates)
├── 📂 include/
│   ├── ⚙️ config.h                # การตั้งค่าระบบ (Hardware, timing, etc.)
│   └── 🔐 credentials.h.example   # ตัวอย่างไฟล์ credentials (ปลอดภัย)
├── 📂 lib/                        # Libraries เพิ่มเติม (ว่าง - จัดการโดย PlatformIO)
├── 📂 test/                       # Test files (เตรียมไว้สำหรับอนาคต)
└── 🚫 .gitignore                  # ไฟล์ที่ไม่ต้องการใน Git (รวม credentials.h)
```

**📊 สถิติโปรเจค:**
- 📝 **เอกสาร:** 8+ ไฟล์ครบถ้วน
- 🔧 **Source code:** 1 ไฟล์หลัก + 2 config files  
- 🔒 **Security:** Enhanced credentials management
- 📱 **Platform:** PlatformIO + Arduino IDE support

## 🔧 การตั้งค่าขั้นสูง

> **🎛️ การปรับแต่ง:** สามารถปรับค่าต่างๆ ได้ใน `include/config.h`

### ⏰ **การปรับแต่งเวลา Cooldown**

```cpp
// ใน include/config.h
#define COOLDOWN_TIME_MS 10000  // 10 วินาที (ค่าเริ่มต้น)
#define COOLDOWN_TIME_MS 30000  // 30 วินาที (ลดการแจ้งเตือน)
#define COOLDOWN_TIME_MS 5000   // 5 วินาที (เพิ่มความไว)
```

### 🔌 **การเปลี่ยน GPIO Pin**

```cpp
// ใน include/config.h
#define PIR_PIN 4   // ค่าเริ่มต้น
#define PIR_PIN 2   // GPIO 2 (มี LED onboard)
#define PIR_PIN 5   // GPIO 5 (pin อื่น)
```

### 📊 **การปรับแต่งการตรวจจับ**

```cpp
// ใน include/config.h
#define PIR_TRIGGER_MODE CHANGE  // ค่าเริ่มต้น - ตรวจจับทั้งเริ่มและหยุด
#define PIR_TRIGGER_MODE RISING  // ตรวจจับเฉพาะเมื่อเริ่มเคลื่อนไหว
#define PIR_TRIGGER_MODE FALLING // ตรวจจับเฉพาะเมื่อหยุดเคลื่อนไหว
```

### 🔧 **การปรับแต่งระบบ**

```cpp
// ใน include/config.h

// การตั้งค่าเครือข่าย
#define MAX_RETRY_ATTEMPTS 3     // จำนวนครั้งที่ลองเชื่อมต่อ WiFi
#define WIFI_TIMEOUT_MS 30000    // Timeout การเชื่อมต่อ WiFi (30 วินาที)
#define HTTP_TIMEOUT_MS 10000    // Timeout HTTP request (10 วินาที)

// การตั้งค่า Debug
#define DEBUG_ENABLED true       // เปิดการแสดงข้อมูล debug
#define DEBUG_VERBOSE false      // เปิดการแสดงข้อมูลละเอียด

// การตั้งค่า LINE API
#define MAX_MESSAGE_LENGTH 1000  // ความยาวข้อความสูงสุด
#define API_RETRY_ATTEMPTS 2     // จำนวนครั้งที่ลอง API อีก
```

### 🎯 **ฟีเจอร์เพิ่มเติม (สำหรับผู้ใช้ขั้นสูง)**

```cpp
// ใน include/config.h

// เปิดใช้งาน LED แสดงสถานะ
#define ENABLE_LED_INDICATOR true
#define LED_PIN 2

// เปิดใช้งาน Buzzer
#define ENABLE_BUZZER true  
#define BUZZER_PIN 5

// Build Environments
// ใช้คำสั่ง: pio run -e esp32dev_debug
// หรือ:       pio run -e esp32dev_release
```

## 📚 Dependencies และ Libraries

### 📦 **การจัดการ Dependencies**

โปรเจคใช้ **PlatformIO** สำหรับจัดการ libraries อัตโนมัติ ไม่ต้องติดตั้งด้วยตนเอง

**Libraries ที่ใช้:**

| Library | Version | Purpose |
|---------|---------|---------|
| **WiFi.h** | Built-in | การเชื่อมต่อ WiFi และจัดการเครือข่าย |
| **HTTPClient.h** | Built-in | ส่ง HTTP/HTTPS requests |
| **WiFiClientSecure.h** | Built-in | การเชื่อมต่อ HTTPS แบบปลอดภัย |
| **ArduinoJson.h** | v7.0.0 | จัดการข้อมูล JSON สำหรับ LINE API |
| **Arduino.h** | Built-in | Core functions ของ Arduino/ESP32 |

### 🔧 **Build Environments**

โปรเจครองรับหลาย build environments:

```ini
# platformio.ini

[env:esp32dev]          # Environment ปกติ
[env:esp32dev_debug]    # Environment สำหรับ debugging  
[env:esp32dev_release]  # Environment สำหรับ production (optimized)
```

**วิธีใช้:**

```bash
# Build environment ปกติ
pio run

# Build สำหรับ debugging
pio run -e esp32dev_debug

# Build สำหรับ production
pio run -e esp32dev_release
```

## ⚠️ ข้อควรระวังและข้อแนะนำ

### 🔒 **ความปลอดภัย**

1. **🚫 ห้ามแชร์ Credentials:** ไม่แชร์ Channel Access Token ในที่สาธารณะ
2. **🔐 ใช้ไฟล์ credentials.h:** แยกข้อมูลส่วนบุคคลออกจาก source code
3. **🔄 เปลี่ยน Token เป็นประจำ:** เพื่อความปลอดภัยสูงสุด
4. **📋 ตรวจสอบ .gitignore:** ให้แน่ใจว่า `credentials.h` ไม่ถูก commit

### ⚡ **ประสิทธิภาพและเสถียรภาพ**

1. **🔌 แหล่งจ่ายไฟ:** ใช้ 3.3V แทน 5V เพื่อความเสถียร
2. **⏰ Warm-up Time:** PIR sensor ต้องการเวลา 1-2 นาที
3. **📶 สัญญาณ WiFi:** ESP32 รองรับเฉพาะ 2.4GHz (ไม่ใช่ 5GHz)
4. **🔋 การใช้พลังงาน:** พิจารณา Deep Sleep mode สำหรับการใช้งานแบบประหยัดพลังงาน

### 🎯 **การใช้งานจริง**

1. **📏 ระยะการตรวจจับ:** PIR sensor มีระยะ 3-7 เมตร
2. **🌡️ อุณหภูมิ:** ทำงานได้ดีที่ 15-40°C  
3. **💧 ความชื้น:** หลีกเลี่ยงสถานที่ชื้นจัด
4. **🔧 Maintenance:** ทำความสะอาดเลนส์ PIR sensor เป็นประจำ

### 🏠 **Production Deployment**

1. **📦 Enclosure:** ใส่ในกล่องกันน้ำสำหรับใช้กลางแจ้ง
2. **🔒 Certificate Pinning:** ใช้ SSL certificates แทน `setInsecure()`
3. **📊 Monitoring:** ติดตั้งระบบ monitoring สำหรับการใช้งานจริง
4. **🔄 OTA Updates:** พิจารณาระบบ Over-The-Air updates

## 🔧 การแก้ไขปัญหา (Troubleshooting)

### 🚫 **ปัญหาที่พบบ่อย**

| ปัญหา | สาเหตุ | วิธีแก้ไข |
|-------|--------|----------|
| **ESP32 เชื่อมต่อ WiFi ไม่ได้** | • รหัสผ่าน WiFi ผิด<br>• ใช้ 5GHz WiFi | • ตรวจสอบ credentials.h<br>• ใช้ WiFi 2.4GHz เท่านั้น |
| **LINE ไม่ได้รับแจ้งเตือน** | • Channel Access Token ผิด<br>• User ID ผิด | • ตรวจสอบข้อมูลใน LINE Developers<br>• ใช้ ngrok test |
| **PIR sensor ไม่ทำงาน** | • ขายังไม่เสถียร<br>• การต่อสาย GPIO ผิด | • รอ warm-up 1-2 นาทีก่อน<br>• ตรวจสอบขา GPIO 2 |
| **ESP32 รีสตาร์ตเอง** | • แหล่งจ่ายไฟไม่เพียงพอ<br>• การใช้ไฟเกิน | • ใช้ USB adapter ที่ดี<br>• เพิ่ม delay ในโค้ด |

### 🔍 **การ Debug แบบละเอียด**

**1. เปิด Serial Monitor:**

```bash
pio device monitor --baud 115200
```

**2. เปิด Debug Mode ใน config.h:**

```cpp
#define DEBUG_MODE true
#define SERIAL_BAUD_RATE 115200
```

**3. ตรวจสอบการเชื่อมต่อ WiFi:**

```cpp
// เพิ่มใน main.cpp สำหรับ debug
Serial.print("WiFi Status: ");
Serial.println(WiFi.status());
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
```

**4. ทดสอบ LINE API ด้วย curl:**

```bash
curl -X POST https://api.line.me/v2/bot/message/push \
  -H "Authorization: Bearer YOUR_CHANNEL_ACCESS_TOKEN" \
  -H "Content-Type: application/json" \
  -d '{
    "to": "YOUR_USER_ID",
    "messages": [{"type": "text", "text": "Test message"}]
  }'
```

### 📋 **เครื่องมือ Debug เพิ่มเติม**

1. **WiFi Scanner:** ตรวจสอบสัญญาณ WiFi ในพื้นที่
2. **LINE Messaging API Console:** ตรวจสอบ logs การส่งข้อความ  
3. **PlatformIO Debugger:** ใช้สำหรับ hardware debugging
4. **Wireshark:** ตรวจสอบ network traffic (advanced)

## 🤝 การมีส่วนร่วมในโปรเจค (Contributing)

ยินดีรับการมีส่วนร่วมจากทุกคน! โปรดอ่าน [CONTRIBUTING.md](CONTRIBUTING.md) สำหรับรายละเอียด

### 📋 **แนวทางการ Contribute**

1. **🍴 Fork** repository นี้
2. **🌿 สร้าง branch** ใหม่ (`git checkout -b feature/AmazingFeature`)
3. **💾 Commit** การเปลี่ยนแปลง (`git commit -m 'Add some AmazingFeature'`)
4. **📤 Push** ไปยัง branch (`git push origin feature/AmazingFeature`)
5. **🔀 เปิด Pull Request**

### 🎯 **ประเภทการ Contribute ที่ต้องการ**

- 🐛 **Bug fixes:** แก้ไขปัญหาที่พบ
- ✨ **New features:** เพิ่มฟีเจอร์ใหม่ (เช่น support sensors อื่น)
- 📖 **Documentation:** ปรับปรุงเอกสารและคู่มือ  
- 🧪 **Testing:** เพิ่ม unit tests และ integration tests
- 🌍 **Translations:** แปลเอกสารเป็นภาษาอื่น
- 🎨 **UI/UX:** ปรับปรุง LINE message templates

## 📄 License

โปรเจคนี้อยู่ภายใต้ **MIT License** - ดูรายละเอียดในไฟล์ [LICENSE](LICENSE)

### 📋 **สรุป MIT License**

✅ **อนุญาต:**
- ✅ การใช้งานเชิงพาณิชย์
- ✅ การแก้ไขและดัดแปลง  
- ✅ การแจกจ่าย
- ✅ การใช้งานส่วนบุคคล

⚠️ **เงื่อนไข:**
- 📄 ต้องรวม license และ copyright notice
- ⚖️ ผู้พัฒนาไม่รับผิดชอบต่อความเสียหาย

## 📞 การติดต่อและช่วยเหลือ

### 💬 **ช่องทางการติดต่อ**

- **🐛 Issues:** [GitHub Issues](https://github.com/yourusername/ESP-Project-MotionAlert/issues)
- **💬 Discussions:** [GitHub Discussions](https://github.com/yourusername/ESP-Project-MotionAlert/discussions)  
- **📧 Email:** your.email@example.com
- **🌐 Website:** [project-website.com](https://project-website.com)

### 🆘 **การขอความช่วยเหลือ**

1. **🔍 ค้นหาใน Issues ก่อน:** อาจมีคนเคยถามไปแล้ว
2. **📋 ให้ข้อมูลครบถ้วน:** 
   - เวอร์ชัน ESP32 และ PlatformIO
   - ข้อความ error ที่สมบูรณ์
   - ขั้นตอนการทำซ้ำปัญหา
3. **📷 แนบรูปภาพ:** circuit diagram, serial monitor output
4. **💻 แชร์โค้ด:** ใส่โค้ดที่เกี่ยวข้อง (ลบ credentials ออก)

---

### 🎉 **ขอบคุณที่ใช้ ESP-Project-MotionAlert!**

> 💝 **หากโปรเจคนี้มีประโยชน์ กรุณาให้ ⭐ Star ที่ GitHub เพื่อสนับสนุนการพัฒนาต่อไป**

**Happy Coding! 🚀**

---

<div align="center">

**📅 Last Updated:** January 2025  
**🔢 Version:** 2.0.0  
**👨‍💻 Maintainer:** [Your Name](https://github.com/yourusername)

</div>

## 🐛 การแก้ไขปัญหา

### ปัญหาที่พบบ่อย

1. **ไม่สามารถเชื่อมต่อ WiFi ได้**
   - ตรวจสอบ SSID และรหัสผ่าน
   - ตรวจสอบสัญญาณ WiFi

2. **ไม่ได้รับข้อความใน LINE**
   - ตรวจสอบ Channel Access Token
   - ตรวจสอบ User ID
   - ดูใน Serial Monitor เพื่อดู HTTP response code

3. **การตรวจจับไม่แม่นยำ**
   - ปรับระยะห่างของ PIR sensor
   - ตรวจสอบการต่อสาย
   - ปรับแต่งเวลา Cooldown

4. **ESP32 รีสตาร์ทบ่อย**
   - ตรวจสอบแหล่งจ่ายไฟ
   - อาจเป็นปัญหาจาก Watchdog timer

## 📞 การสนับสนุน

หากพบปัญหาหรือต้องการความช่วยเหลือ:

1. ตรวจสอบ Serial Monitor output
2. ดูใน Issues section ของ repository
3. สร้าง Issue ใหม่พร้อมรายละเอียดของปัญหา

## 📄 License

โปรเจคนี้เผยแพร่ภายใต้ MIT License - ดูรายละเอียดในไฟล์ [LICENSE](LICENSE)

## 🤝 การมีส่วนร่วม

การมีส่วนร่วมของคุณยินดีต้อนรับ! กรุณา:

1. Fork repository
2. สร้าง feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit การเปลี่ยนแปลง (`git commit -m 'Add some AmazingFeature'`)
4. Push ไปยัง branch (`git push origin feature/AmazingFeature`)
5. เปิด Pull Request

## 📈 แผนการพัฒนาต่อไป

- [ ] เพิ่ม Web Interface สำหรับการตั้งค่า
- [ ] รองรับการส่งรูปภาพผ่าน LINE
- [ ] เพิ่มระบบบันทึกข้อมูล (Logging)
- [ ] รองรับ Multiple Sensors
- [ ] เพิ่ม Battery Monitoring
- [ ] Deep Sleep Mode เพื่อประหยัดพลังงาน

## 👥 ผู้พัฒนา

- **Ohmies** - *Initial work* - [GitHub Profile](https://github.com/Ohmies)

## 🙏 กิตติกรรมประกาศ

- LINE Developers สำหรับ Messaging API
- PlatformIO Community
- Arduino Community
- ESP32 Community
