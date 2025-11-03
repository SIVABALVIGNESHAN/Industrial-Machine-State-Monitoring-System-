// AP_Node.ino
// Sets up SoftAP for local diagnostics and also connects to the INTERNET WiFi SSID
// Note: This AP sketch does not forward internet to softAP clients automatically.

#include <WiFi.h>

const char* internetSSID = "Siva";      // Internet-capable router SSID
const char* internetPASS = "siva1234";

const char* softAP_SSID = "ESP32_LocalAP";
const char* softAP_PASS = "esp32pass";

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Starting AP node...");

  // Start Soft AP for local access
  WiFi.mode(WIFI_AP_STA); // both AP and STA
  bool apStarted = WiFi.softAP(softAP_SSID, softAP_PASS, 1, 0, 4); // channel 1, open=false, max 4 clients
  if (apStarted) {
    IPAddress AP_IP = WiFi.softAPIP();
    Serial.print("SoftAP started. IP: ");
    Serial.println(AP_IP);
  } else {
    Serial.println("SoftAP start failed.");
  }

  // Connect as STA to internet router (so other devices on same LAN can access internet)
  Serial.printf("Connecting STA to: %s\n", internetSSID);
  WiFi.begin(internetSSID, internetPASS);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Connected to internet WiFi. STA IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway: ");
    Serial.println(WiFi.gatewayIP());
  } else {
    Serial.println();
    Serial.println("Failed to connect STA to internet WiFi (check credentials).");
    // You may still use SoftAP locally
  }

  // You can add a small web server on this AP node for diagnostics if needed.
}

void loop() {
  // keep alive; add diagnostic webserver or mDNS here if desired
  delay(2000);
}
