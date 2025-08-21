// main.cpp for PlatformIO (PIR Sensor + LINE Notify)
// 🔒 SECURE VERSION - Credentials are protected and separated

// Include necessary libraries
// These libraries are automatically managed by PlatformIO based on platformio.ini
#include <WiFi.h>             // For WiFi connectivity
#include <HTTPClient.h>       // For making HTTP requests
#include <WiFiClientSecure.h> // For secure HTTPS connections (needed for LINE API)
#include <ArduinoJson.h>      // For JSON serialization/deserialization (needed for LINE API payload)
#include <Arduino.h>          // Standard Arduino core functions (e.g., pinMode, digitalWrite, millis)

// Include configuration files
#include "config.h" // Hardware and system configuration

// ⚠️ SECURITY INSTRUCTIONS:
// Before using this code in production:
// 1. Copy include/credentials.h.example to include/credentials.h
// 2. Update credentials.h with your actual WiFi and LINE API credentials
// 3. Uncomment the line below to include your credentials
// 4. Never commit credentials.h to version control (it's already in .gitignore)

// Uncomment this line after creating credentials.h:
// #include "credentials.h"

// 🔒 PLACEHOLDER CREDENTIALS (Replace these with your actual values!)
// คำอธิบาย: ข้อมูลเหล่านี้เป็นตัวอย่างเท่านั้น ไม่สามารถใช้งานได้จริง
// โปรดแทนที่ด้วยข้อมูลจริงของคุณใน credentials.h หรือในไฟล์นี้โดยตรง
#ifndef WIFI_SSID
const char *ssid = "YOUR_WIFI_SSID_HERE";                          // 📝 แทนที่ด้วยชื่อ WiFi ของคุณ
const char *password = "YOUR_WIFI_PASSWORD_HERE";                  // 📝 แทนที่ด้วยรหัสผ่าน WiFi ของคุณ
const char *channelAccessToken = "YOUR_CHANNEL_ACCESS_TOKEN_HERE"; // 📝 ได้จาก LINE Developers Console
const char *userID = "YOUR_USER_ID_OR_GROUP_ID_HERE";              // 📝 User ID หรือ Group ID ของคุณ
#else
//  ✅ ใช้ข้อมูลจากไฟล์ credentials.h (วิธีที่แนะนำ)
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *channelAccessToken = LINE_CHANNEL_ACCESS_TOKEN;
const char *userID = LINE_USER_ID;
#endif

// --- PIR Sensor Configuration ---
// ใช้การตั้งค่าจาก config.h เพื่อความยืดหยุ่นในการจัดการ
volatile bool motionDetected = false;         // Status variable for motion detection
volatile unsigned long lastDetectionTime = 0; // Last detection time (to prevent rapid re-sending)

// --- LINE Messaging API Server Details (Do not change) ---
const char *lineApiHost = "api.line.me";
const int lineApiPort = 443;

// --- Function for sending LINE messages (forward declaration) ---
// This is needed because sendMessageToLine is called before its full definition
void sendMessageToLine(String message);

// --- Interrupt Service Routine (ISR) for PIR Sensor ---
// This function is automatically called when the PIR Sensor detects motion
void IRAM_ATTR detectMotion()
{
  // Check PIR sensor state (HIGH means motion detected)
  if (digitalRead(PIR_PIN) == HIGH)
  {
    // If no motion was previously detected OR if the cooldown period has passed
    if (!motionDetected || (millis() - lastDetectionTime > COOLDOWN_TIME_MS))
    {
      motionDetected = true;        // Set motion detected status
      lastDetectionTime = millis(); // Record the time of detection
    }
  }
}

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE); // Initialize serial communication for debugging
  delay(100);

  // 🔒 Security check - warn if using default placeholder values
  if (String(ssid) == "YOUR_WIFI_SSID_HERE" || String(channelAccessToken) == "YOUR_CHANNEL_ACCESS_TOKEN_HERE")
  {
    Serial.println("⚠️ WARNING: Using placeholder credentials!");
    Serial.println("🔧 Please update your credentials:");
    Serial.println("   1. Copy include/credentials.h.example to include/credentials.h");
    Serial.println("   2. Edit credentials.h with your actual values");
    Serial.println("   3. Uncomment #include \"credentials.h\" in main.cpp");
    Serial.println("📚 See README.md for detailed setup instructions");
    delay(5000); // Give time to read the warning
  }

  // Configure PIR pin as INPUT_PULLUP (to prevent floating signals)
  pinMode(PIR_PIN, INPUT_PULLUP);
  // Attach interrupt to the PIR pin, triggering on mode defined in config.h
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), detectMotion, PIR_TRIGGER_MODE);

  Serial.print("🌐 Connecting to WiFi: ");
  Serial.println(ssid);

  // Connect to WiFi network with retry mechanism
  WiFi.begin(ssid, password);
  int wifiAttempts = 0;
  while (WiFi.status() != WL_CONNECTED && wifiAttempts < MAX_RETRY_ATTEMPTS)
  {
    delay(RETRY_DELAY_MS);
    Serial.print(".");
    wifiAttempts++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("\n✅ WiFi connected!");
    Serial.print("🌐 IP Address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    Serial.println("\n❌ WiFi connection failed!");
    Serial.println("🔧 Please check your WiFi credentials in credentials.h");
    Serial.println("📚 See README.md for troubleshooting guide");
    return;
  }

  // Synchronize time for HTTPS (crucial for SSL/TLS certificate validation)
  configTime(0, 0, "pool.ntp.org");
  delay(1000); // Give some time for time synchronization
  Serial.println("⏰ Time synchronized.");

  // Send a welcome message to LINE (only if not using placeholder values)
  if (String(channelAccessToken) != "YOUR_CHANNEL_ACCESS_TOKEN_HERE")
  {
    sendMessageToLine("🚀 ระบบตรวจจับความเคลื่อนไหว PIR พร้อมทำงานแล้ว! 🕵️");
  }
  else
  {
    Serial.println("⚠️ Skipping LINE test message - using placeholder token");
    Serial.println("🔧 Please configure your LINE API credentials");
  }
}

void loop()
{
  // Check if motion was detected by the ISR
  if (motionDetected)
  {
    // Reset motionDetected immediately to prepare for the next detection
    // (but the message will only be sent once per cooldown period)
    motionDetected = false;

    Serial.println("🚨 ตรวจพบการเคลื่อนไหว!");

    // Only send LINE message if not using placeholder values
    if (String(channelAccessToken) != "YOUR_CHANNEL_ACCESS_TOKEN_HERE")
    {
      sendMessageToLine("🚨 แจ้งเตือน: ตรวจพบการเคลื่อนไหว!");
    }
    else
    {
      Serial.println("⚠️ LINE notification skipped - using placeholder credentials");
      Serial.println("🔧 Please configure your LINE API credentials in credentials.h");
    }
  }

  // Small delay to reduce CPU load
  delay(50);
}

// --- Function to send message to LINE ---
void sendMessageToLine(String message)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    // ⚠️ client.setInsecure() is for testing only! For production, use proper certificates!
    client.setInsecure();
    client.setTimeout(HTTP_TIMEOUT_MS / 1000); // Set timeout from config.h

    // Attempt to connect to LINE API host
    if (!client.connect(lineApiHost, lineApiPort))
    {
      Serial.println("❌ Connection to LINE API failed!");
      return;
    }
    Serial.println("✅ Connected to LINE API.");

    HTTPClient http;
    // Begin HTTP POST request to LINE Messaging API push message endpoint
    http.begin(client, String("https://") + lineApiHost + "/v2/bot/message/push");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(channelAccessToken));
    http.setTimeout(HTTP_TIMEOUT_MS); // Set timeout from config.h

    // Create JSON payload for the message using ArduinoJson
    StaticJsonDocument<200> doc;                             // Allocate a JSON document on the stack
    doc["to"] = userID;                                      // Recipient User ID or Group ID
    JsonArray messages = doc["messages"].to<JsonArray>();    // Create a JSON array for messages
    JsonObject msg1 = messages.add<JsonObject>();            // Add a message object to the array
    msg1["type"] = "text";                                   // Message type: text
    msg1["text"] = message.substring(0, MAX_MESSAGE_LENGTH); // Limit message length from config.h

    String requestBody;
    serializeJson(doc, requestBody); // Serialize JSON document to a string

    if (DEBUG_ENABLED) // From config.h
    {
      Serial.println("📩 Sending JSON: " + requestBody);
    }

    int httpResponseCode = http.POST(requestBody); // Send the POST request

    // Check HTTP response code
    if (httpResponseCode == HTTP_CODE_OK)
    {
      Serial.println("✅ Message sent successfully!");
    }
    else
    {
      Serial.print("❌ Error sending message. HTTP response code: ");
      Serial.println(httpResponseCode);

      if (DEBUG_ENABLED) // From config.h
      {
        Serial.println(http.errorToString(httpResponseCode)); // Print error description
        String responsePayload = http.getString();            // Get response body from LINE API
        Serial.println("Response from LINE: " + responsePayload);
      }
    }

    http.end(); // Close the HTTP connection
  }
  else
  {
    Serial.println("❌ WiFi not connected. Cannot send message.");
    Serial.println("🔄 Attempting to reconnect...");

    // Attempt to reconnect to WiFi
    WiFi.begin(ssid, password);
  }
}