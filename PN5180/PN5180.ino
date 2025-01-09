#include <PN5180ISO15693.h>
#include <WiFi.h>
#include <HTTPClient.h>

// PN5180 pins
const byte nssPin = 5;
const byte busyPin = 16;
const byte resetPin = 17;

// Create PN5180 object
PN5180ISO15693 nfc(nssPin, busyPin, resetPin);

// Wi-Fi credentials
const char* ssid = "Chỉ chờ có thế";
const char* password = "23456789";

// Server URL
const char* serverURL = "http://192.168.112.222:3000/api/checkin";

void setup() {
  Serial.begin(115200);

  // Initialize NFC reader
  Serial.println("Initializing the NFC reader...");
  nfc.begin();
  nfc.reset();
  nfc.setupRF();

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Detect tag
  uint8_t uid[8];
  ISO15693ErrorCode rc = nfc.getInventory(uid);

  // If tag is detected
  if (rc == ISO15693_EC_OK) {
    // Convert UID to string
    String uidStr = "";
    for (int j = 0; j < sizeof(uid); j++) {
      if (uid[j] < 16) uidStr += "0"; // Add leading zero for single-digit hex values
      uidStr += String(uid[j], HEX);
    }
    uidStr.toUpperCase();

    Serial.print("Detected UID: ");
    Serial.println(uidStr);

    // Send UID to server
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(serverURL);

      // Prepare JSON payload
      String payload = "{\"uid\":\"" + uidStr + "\"}";
      http.addHeader("Content-Type", "application/json");

      // Send POST request
      int httpResponseCode = http.POST(payload);
      if (httpResponseCode > 0) {
        Serial.println("Data sent successfully!");
        Serial.println(http.getString()); // Print server response
      } else {
        Serial.print("Error sending data: ");
        Serial.println(http.errorToString(httpResponseCode).c_str());
      }
      http.end();
    } else {
      Serial.println("Wi-Fi not connected!");
    }
  }

  // Wait 2 seconds before the next scan
  delay(2000);
}



