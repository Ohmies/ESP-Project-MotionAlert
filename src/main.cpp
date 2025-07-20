// main.cpp for PlatformIO (PIR Sensor + LINE Notify)

// Include necessary libraries
// These libraries are automatically managed by PlatformIO based on platformio.ini
#include <WiFi.h>             // For WiFi connectivity
#include <HTTPClient.h>       // For making HTTP requests
#include <WiFiClientSecure.h> // For secure HTTPS connections (needed for LINE API)
#include <ArduinoJson.h>      // For JSON serialization/deserialization (needed for LINE API payload)
#include <Arduino.h>          // Standard Arduino core functions (e.g., pinMode, digitalWrite, millis)

// --- Your WiFi Credentials (Change these values!) ---
const char *ssid = "OHMies";       // Your WiFi network name
const char *password = "26022519"; // Your WiFi password

// --- LINE Messaging API Key (VERY IMPORTANT! Keep this secret!) ---
// Get this from LINE Developers Console
const char *channelAccessToken = "TFX4fuJvIg+K++CEW8/A093rpsmfwAVoWWY3e2ycTNC/FXJ5CDUdWdsnyzJ79R+O4jtdT79EHdorFDEODreNybjWcW10ZLE2qYQJ7PBDd2SPEUCIG5yFrUg+vCSDZNmJvWDHvJ4uNZxUv7pkNCydcQdB04t89/1O/w1cDnyilFU=";
// User ID or Group ID to send messages to
const char *userID = "U4ea2911ce226e8e0063d0ffd3980ef89";

// --- PIR Sensor Configuration ---
const int PIR_PIN = 4;                        // GPIO pin connected to the PIR Sensor (e.g., GPIO 4)
volatile bool motionDetected = false;         // Status variable for motion detection
volatile unsigned long lastDetectionTime = 0; // Last detection time (to prevent rapid re-sending)
const unsigned long COOLDOWN_TIME_MS = 10000; // Cooldown Time: 10 seconds (to prevent excessive notifications)

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
  Serial.begin(115200); // Initialize serial communication for debugging
  delay(100);

  // Configure PIR pin as INPUT_PULLUP (to prevent floating signals)
  pinMode(PIR_PIN, INPUT_PULLUP);
  // Attach interrupt to the PIR pin, triggering on CHANGE (LOW to HIGH or HIGH to LOW)
  // You could use RISING if you only want to trigger when motion starts
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), detectMotion, CHANGE);

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Synchronize time for HTTPS (crucial for SSL/TLS certificate validation)
  configTime(0, 0, "pool.ntp.org");
  delay(1000); // Give some time for time synchronization
  Serial.println("Time synchronized.");

  // Send a welcome message to LINE
  sendMessageToLine("🚀 ระบบตรวจจับความเคลื่อนไหว PIR พร้อมทำงานแล้ว! 🕵️");
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
    sendMessageToLine("🚨 แจ้งเตือน: ตรวจพบการเคลื่อนไหว!");
  }

  // You can add other code here if you don't want the ESP32 to just wait for motion
  delay(50); // Small delay to reduce CPU load
}

// --- Function to send message to LINE ---
void sendMessageToLine(String message)
{
  if (WiFi.status() == WL_CONNECTED)
  {
    WiFiClientSecure client;
    // client.setInsecure() is for testing only! For production, use certificates!
    client.setInsecure();

    // Attempt to connect to LINE API host
    if (!client.connect(lineApiHost, lineApiPort))
    {
      Serial.println("❌ Connection to Line API failed!");
      return;
    }
    Serial.println("✅ Connected to Line API.");

    HTTPClient http;
    // Begin HTTP POST request to LINE Messaging API push message endpoint
    http.begin(client, String("https://") + lineApiHost + "/v2/bot/message/push");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", "Bearer " + String(channelAccessToken));

    // Create JSON payload for the message using ArduinoJson
    StaticJsonDocument<200> doc;                          // Allocate a JSON document on the stack
    doc["to"] = userID;                                   // Recipient User ID or Group ID
    JsonArray messages = doc["messages"].to<JsonArray>(); // Create a JSON array for messages
    JsonObject msg1 = messages.add<JsonObject>();         // Add a message object to the array
    msg1["type"] = "text";                                // Message type: text
    msg1["text"] = message;                               // The actual text message

    String requestBody;
    serializeJson(doc, requestBody); // Serialize JSON document to a string

    Serial.println("📩 Sending JSON: " + requestBody);
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
      Serial.println(http.errorToString(httpResponseCode)); // Print error description
      String responsePayload = http.getString();            // Get response body from LINE API
      Serial.println("Response from LINE: " + responsePayload);
    }

    http.end(); // Close the HTTP connection
  }
  else
  {
    Serial.println("❌ WiFi not connected. Cannot send message.");
  }
}
