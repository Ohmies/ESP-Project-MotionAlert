# Quick Start Guide 🚀

## เริ่มต้นใช้งานแบบเร็ว (5 นาที)

> **📋 สำคัญ:** คู่มือนี้จะช่วยให้คุณติดตั้งและใช้งานระบบตรวจจับการเคลื่อนไหวได้ภายใน 5 นาที!

### 1. การเตรียมความพร้อม

#### 💻 ติดตั้ง Software

**ตัวเลือกที่ 1: PlatformIO (แนะนำ)**
- ติดตั้ง [VS Code](https://code.visualstudio.com/)
- ติดตั้ง [PlatformIO Extension](https://platformio.org/install/ide) ใน VS Code

**ตัวเลือกที่ 2: Arduino IDE**
- ดาวน์โหลด [Arduino IDE](https://www.arduino.cc/en/software)
- ติดตั้ง ESP32 Board Package

#### ⚡ เตรียม Hardware

**อุปกรณ์ที่จำเป็น:**
- ESP32 Development Board (1 ตัว)
- PIR Motion Sensor HC-SR501 (1 ตัว)
- Jumper wires ตัวผู้-ตัวเมีย (3 เส้น)
- สาย USB สำหรับ ESP32

**อุปกรณ์เสริม (ไม่บังคับ):**
- Breadboard สำหรับการต่อสาย
- LED และ Resistor สำหรับแสดงสถานะ

### 2. ติดตั้งโปรเจค

#### วิธีที่ 1: ใช้ Setup Script (macOS/Linux)

```bash
# Clone repository
git clone https://github.com/Ohmies/ESP-Project-MotionAlert.git
cd ESP-Project-MotionAlert

# รันสคริปต์ setup อัตโนมัติ
chmod +x setup.sh
./setup.sh
```

#### วิธีที่ 2: Setup ด้วยตนเอง

```bash
# Clone repository
git clone https://github.com/Ohmies/ESP-Project-MotionAlert.git
cd ESP-Project-MotionAlert

# ติดตั้ง dependencies (ถ้าใช้ PlatformIO)
pio lib install
pio run

# หรือถ้าใช้ Arduino IDE ให้เปิดไฟล์ src/main.cpp
```

### 3. ตั้งค่า LINE Bot 🤖

> **🔑 สำคัญมาก:** ขั้นตอนนี้จำเป็นสำหรับการรับแจ้งเตือนผ่าน LINE

#### Step 1: สร้าง LINE Channel
1. เข้าสู่ [LINE Developers Console](https://developers.line.biz/)
2. Login ด้วย LINE Account ของคุณ
3. คลิก **"Create"** → **"Create a new provider"**
4. ใส่ชื่อ Provider (เช่น "MyHomeAlert")
5. คลิก **"Create"** → **"Create a Messaging API channel"**
6. กรอกข้อมูล Channel:
   - **Channel name:** ESP Motion Alert
   - **Channel description:** ระบบแจ้งเตือนการเคลื่อนไหว
   - **Category:** ใส่ตามความเหมาะสม
   - **Subcategory:** ใส่ตามความเหมาะสม

#### Step 2: ได้รับ Channel Access Token
1. ไปที่แท็บ **"Messaging API"**
2. ใน **"Channel access token"** คลิก **"Issue"**
3. **คัดลอก Token ที่ได้** (เก็บไว้ใช้ในขั้นตอนถัดไป)

#### Step 3: หา User ID ของคุณ
1. เพิ่ม LINE Bot เป็นเพื่อนโดยสแกน QR Code ในหน้า Messaging API
2. ส่งข้อความอะไรก็ได้ไปยัง Bot
3. ใช้เครื่องมือหา User ID:
   - [LINE User ID Finder](https://developers.line.biz/en/docs/messaging-api/getting-user-ids/)
   - หรือดูจาก Webhook events

### 4. แก้ไขการตั้งค่า 🔧

> **⚠️ ความปลอดภัย:** เราได้ปรับปรุงระบบให้ปลอดภัยขึ้นแล้ว!

#### วิธีที่ 1: ใช้ไฟล์ credentials.h (แนะนำ)

```bash
# สร้างไฟล์ credentials.h จากตัวอย่าง
cp include/credentials.h.example include/credentials.h

# แก้ไขไฟล์ credentials.h
nano include/credentials.h
# หรือใช้ text editor ตัวอื่นที่คุณชอบ
```

แก้ไขใน `include/credentials.h`:

```cpp
#ifndef CREDENTIALS_H
#define CREDENTIALS_H

// WiFi Configuration
const char* WIFI_SSID = "ชื่อWiFiของคุณ";
const char* WIFI_PASSWORD = "รหัสผ่านWiFi";

// LINE Messaging API Configuration  
const char* LINE_CHANNEL_ACCESS_TOKEN = "ChannelAccessTokenที่คัดลอกมา";
const char* LINE_USER_ID = "UserIDของคุณ";

#endif // CREDENTIALS_H
```

**จากนั้นแก้ไขใน `src/main.cpp`:**

```cpp
// หาบรรทัดนี้:
// #include "credentials.h"

// เปลี่ยนเป็น (ลบ // ออก):
#include "credentials.h"
```

#### วิธีที่ 2: แก้ไขใน main.cpp โดยตรง (สำหรับการทดสอบ)

แก้ไขใน `src/main.cpp` หาบรรทัดเหล่านี้:

```cpp
const char *ssid = "YOUR_WIFI_SSID_HERE";                          // แทนที่ด้วยชื่อ WiFi
const char *password = "YOUR_WIFI_PASSWORD_HERE";                  // แทนที่ด้วยรหัสผ่าน WiFi  
const char *channelAccessToken = "YOUR_CHANNEL_ACCESS_TOKEN_HERE"; // แทนที่ด้วย Token
const char *userID = "YOUR_USER_ID_OR_GROUP_ID_HERE";              // แทนที่ด้วย User ID
```

### 5. ต่อสาย Hardware 🔌

> **⚡ ระวัง:** ตัดไฟ ESP32 ก่อนต่อสาย!

#### การต่อสายพื้นฐาน

```text
ESP32 Pin    →    PIR Sensor Pin    →    สายสี (แนะนำ)
─────────────────────────────────────────────────────
3.3V         →    VCC               →    แดง (Power)
GND          →    GND               →    ดำ (Ground)  
GPIO4        →    OUT               →    เหลือง (Signal)
```

#### ขั้นตอนการต่อสาย
1. **ตัดไฟ ESP32** (ถอดสาย USB)
2. ต่อสาย **GND** ก่อน (สำคัญ!)
3. ต่อสาย **VCC (3.3V)**
4. ต่อสาย **Signal (GPIO4)** ตัวสุดท้าย
5. ตรวจสอบการต่อสายอีกครั้ง
6. เสียบสาย USB กลับเข้า ESP32

#### หมายเหตุสำคัญ
- ใช้ **3.3V** ไม่ใช่ 5V เพื่อความปลอดภัย
- **GPIO4** สามารถเปลี่ยนได้ใน `include/config.h`
- PIR sensor ต้องการเวลา **warm-up 1-2 นาที**

### 6. Upload และทดสอบ ⬆️

> **🎯 เป้าหมาย:** Upload โค้ดและทดสอบการทำงาน

#### สำหรับ PlatformIO

```bash
# Build โปรเจค (ตรวจสอบ syntax)
pio run

# Upload โค้ดไปยัง ESP32
pio run --target upload

# เปิด Serial Monitor เพื่อดูผลลัพธ์
pio device monitor
```

#### สำหรับ Arduino IDE

1. เปิดไฟล์ `src/main.cpp` ใน Arduino IDE
2. เลือก Board: **ESP32 Dev Module**
3. เลือก Port ที่ถูกต้อง
4. คลิก **Upload** (หรือ Ctrl+U)
5. เปิด **Serial Monitor** (Ctrl+Shift+M)

#### ผลลัพธ์ที่ควรเห็นใน Serial Monitor

```text
🌐 Connecting to WiFi: [ชื่อ WiFi ของคุณ]
✅ WiFi connected!
🌐 IP Address: 192.168.1.xxx
⏰ Time synchronized.
✅ Connected to LINE API.
✅ Message sent successfully!
```

### 7. ทดสอบการทำงาน 🧪

> **📝 เคล็ดลับ:** PIR sensor ต้องการเวลา warm-up 1-2 นาที

#### ขั้นตอนการทดสอบ

1. **รอ PIR sensor warm-up** (1-2 นาที)
2. **เลื่อนมือหน้าเซ็นเซอร์** PIR ช้าๆ
3. **ดูข้อความใน Serial Monitor:**
   ```text
   🚨 ตรวจพบการเคลื่อนไหว!
   📩 Sending JSON: {...}
   ✅ Message sent successfully!
   ```
4. **ตรวจสอบข้อความใน LINE** ของคุณ

#### สิ่งที่ควรได้รับ

- ✅ ข้อความต้อนรับใน LINE: "🚀 ระบบตรวจจับความเคลื่อนไหว PIR พร้อมทำงานแล้ว! 🕵️"
- ✅ ข้อความแจ้งเตือน: "🚨 แจ้งเตือน: ตรวจพบการเคลื่อนไหว!"
- ✅ Serial Monitor แสดงสถานะการทำงาน

#### การปรับแต่งเซ็นเซอร์

**PIR Sensor มี 2 potentiometer:**
- **Sensitivity (Sx):** หมุนขวาเพิ่มความไว, หมุนซ้ายลดความไว
- **Time Delay (Tx):** หมุนขวาเพิ่มเวลาหน่วง, หมุนซ้ายลดเวลาหน่วง

## 🆘 แก้ไขปัญหาเร็ว

### ❌ ไม่ได้รับข้อความ LINE

**สาเหตุที่เป็นไปได้:**

- ❌ **Channel Access Token ผิด:** ตรวจสอบว่าคัดลอกถูกต้องและไม่มีช่องว่าง
- ❌ **User ID ผิด:** ใช้เครื่องมือหา User ID อีกครั้ง
- ❌ **WiFi ไม่เชื่อมต่อ:** ดู HTTP response code ใน Serial Monitor
- ❌ **Bot ไม่ได้เป็นเพื่อน:** ตรวจสอบว่าได้เพิ่มบอทเป็นเพื่อนแล้ว

**วิธีแก้ไข:**
```text
Serial Monitor จะแสดง:
❌ Error sending message. HTTP response code: 401
→ แปลว่า Token ผิด

❌ Error sending message. HTTP response code: 400  
→ แปลว่า User ID ผิดหรือ JSON format ผิด
```

### ⚡ เซ็นเซอร์ไม่ตอบสนอง

**ตรวจสอบตามลำดับ:**

- 🔍 **การต่อสาย:** VCC (แดง), GND (ดำ), Signal (เหลือง)
- 🔍 **พลังงาน:** LED บนเซ็นเซอร์ต้องติด
- 🔍 **เวลา warm-up:** รอ 1-2 นาที หลังเปิดเครื่อง
- 🔍 **ความไวเซ็นเซอร์:** ปรับ potentiometer Sx
- 🔍 **ระยะทำงาน:** เลื่อนมือห่างจากเซ็นเซอร์ 1-3 เมตร

### 📶 ESP32 เชื่อมต่อ WiFi ไม่ได้

**ปัญหาพบบ่อย:**

- 📡 **SSID/Password ผิด:** ตรวจสอบการพิมพ์และ case-sensitive
- 📡 **WiFi 5GHz:** ESP32 รองรับเฉพาะ 2.4GHz
- 📡 **สัญญาณอ่อน:** เอา ESP32 ใกล้ Router
- 📡 **Security Type:** ตรวจสอบว่า WiFi ใช้ WPA2/WPA3

**Serial Monitor จะแสดง:**
```text
🌐 Connecting to WiFi: [ชื่อ WiFi]
..........
❌ WiFi connection failed!
🔧 Please check your WiFi credentials
```

## 📋 Checklist การติดตั้ง

> **✨ เคล็ดลับ:** ใช้ checklist นี้เพื่อตรวจสอบว่าทำครบทุกขั้นตอนแล้ว

### 🛠️ การเตรียมการ

- [ ] **ติดตั้ง PlatformIO หรือ Arduino IDE แล้ว**
- [ ] **ได้อุปกรณ์ครบแล้ว** (ESP32 + PIR + สาย)
- [ ] **Clone repository แล้ว**
- [ ] **Build โปรเจคสำเร็จแล้ว**

### 🤖 LINE Bot Setup

- [ ] **สร้าง LINE Bot แล้ว**
- [ ] **ได้ Channel Access Token แล้ว**
- [ ] **ได้ User ID แล้ว**
- [ ] **เพิ่มบอทเป็นเพื่อนแล้ว**

### ⚙️ การตั้งค่า

- [ ] **สร้างไฟล์ credentials.h แล้ว** (หรือแก้ไข main.cpp)
- [ ] **ใส่ WiFi credentials แล้ว**
- [ ] **ใส่ LINE API credentials แล้ว**
- [ ] **Uncomment #include "credentials.h" แล้ว** (ถ้าใช้ไฟล์แยก)

### 🔌 Hardware Setup

- [ ] **ต่อสาย Hardware แล้ว** (3.3V, GND, GPIO4)
- [ ] **ตรวจสอบการต่อสายแล้ว**
- [ ] **PIR sensor มีไฟติดแล้ว**

### 🚀 การทดสอบ

- [ ] **Upload โค้ดสำเร็จแล้ว**
- [ ] **ESP32 เชื่อมต่อ WiFi ได้แล้ว**
- [ ] **ได้รับข้อความต้อนรับใน LINE แล้ว**
- [ ] **ทดสอบการตรวจจับการเคลื่อนไหวแล้ว**
- [ ] **ได้รับการแจ้งเตือนใน LINE แล้ว**

## 🎯 เคล็ดลับการใช้งาน

### ⚡ การปรับแต่งประสิทธิภาพ

**1. ปรับความไวเซ็นเซอร์:**
- ความไวต่ำ: ตรวจจับเฉพาะการเคลื่อนไหวใหญ่
- ความไวสูง: ตรวจจับการเคลื่อนไหวเล็กน้อย

**2. ปรับเวลา Cooldown:**
```cpp
// ใน include/config.h
#define COOLDOWN_TIME_MS 10000  // 10 วินาที (ค่าเริ่มต้น)
#define COOLDOWN_TIME_MS 30000  // 30 วินาที (ลดการแจ้งเตือน)
#define COOLDOWN_TIME_MS 5000   // 5 วินาที (เพิ่มความไว)
```

**3. เปลี่ยน GPIO Pin:**
```cpp
// ใน include/config.h
#define PIR_PIN 4   // ค่าเริ่มต้น
#define PIR_PIN 2   // หรือ pin อื่นที่ต้องการ
```

### 🔧 การ Debugging

**1. เปิด Debug Mode:**
```cpp
// ใน include/config.h
#define DEBUG_ENABLED true
#define DEBUG_VERBOSE true
```

**2. ดู Serial Monitor อย่างละเอียด:**
- ดูสถานะการเชื่อมต่อ WiFi
- ตรวจสอบ HTTP response codes
- ติดตามการทำงานของเซ็นเซอร์

### 🌟 การใช้งานขั้นสูง

**1. เพิ่ม LED แสดงสถานะ:**
```cpp
// เชื่อมต่อ LED กับ GPIO2
// เปิดใช้งานใน config.h:
#define ENABLE_LED_INDICATOR true
```

**2. เปลี่ยนข้อความแจ้งเตือน:**
```cpp
// ในฟังก์ชัน loop() ของ main.cpp
sendMessageToLine("🚨 มีผู้บุกรุก! 🏠 ตรวจสอบบ้านด่วน!");
```

## 📚 อ่านเพิ่มเติม

### 📖 เอกสารโปรเจค

- **[README.md](README.md)** - คู่มือฉบับเต็มและคำอธิบายโครงการ
- **[CIRCUIT.md](CIRCUIT.md)** - รายละเอียดการต่อสายและ circuit diagram
- **[SECURITY.md](SECURITY.md)** - นโยบายความปลอดภัยและแนวทางปฏิบัติ
- **[CONTRIBUTING.md](CONTRIBUTING.md)** - วิธีการมีส่วนร่วมในการพัฒนา

### 🔒 ความปลอดภัย

- **[SECURITY_UPDATE.md](SECURITY_UPDATE.md)** - รายงานการอัปเดตความปลอดภัย
- **[PROJECT_REPORT.md](PROJECT_REPORT.md)** - รายงานความสมบูรณ์ของโปรเจค

### 🆘 การขอความช่วยเหลือ

1. **ตรวจสอบ Serial Monitor output** เสมอ
2. **อ่าน Error messages** ที่แสดงใน Serial Monitor
3. **ดูใน Issues section** ของ GitHub repository
4. **สร้าง Issue ใหม่** พร้อมรายละเอียดปัญหาและ Serial Monitor output

---

**🎉 ยินดีด้วย!** คุณได้ติดตั้งระบบตรวจจับการเคลื่อนไหวเรียบร้อยแล้ว!

> **💡 เคล็ดลับสุดท้าย:** เก็บ Serial Monitor เปิดไว้ขณะใช้งานเพื่อติดตามสถานะการทำงาน
