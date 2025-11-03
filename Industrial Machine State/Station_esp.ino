// ==========================
//   ESP32 STA Node (Blynk IoT)
//   ADS1115 + INA219 Sensor Node
//   Uses given conversions for sensor data
// ==========================

#define BLYNK_TEMPLATE_ID "TMPL3fTAsFAn_"
#define BLYNK_TEMPLATE_NAME "MACHINE"
#define BLYNK_AUTH_TOKEN "1jWFZGZAAk7nsEdscQ81KP527BTVDFWb"

#include <Wire.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_ADS1X15.h>
#include <Adafruit_INA219.h>

// ---- Hardware Objects ----
Adafruit_ADS1115 ads;      // ADC for analog sensors
Adafruit_INA219 ina219;    // Current sensor

// ---- WiFi + Blynk ----
char ssid[] = "Siva";       
char pass[] = "siva1234";   
char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// ---- Pin Setup ----
#define START_PIN 13     
#define AUTO_PIN 12      
#define STATUS_PIN 14    

bool startState = false;
bool autoState = false;

// ---- Setup ----
void setup() {
  Serial.begin(115200);
  delay(100);

  Wire.begin(21, 22);

  // Initialize ADS1115
  if (!ads.begin()) {
    Serial.println("ADS1115 not found! Check wiring.");
  }

  // Initialize INA219
  if (!ina219.begin()) {
    Serial.println("INA219 not found! Check wiring.");
  } else {
    ina219.setCalibration_32V_2A();
  }

  // Pin modes
  pinMode(START_PIN, OUTPUT);
  pinMode(AUTO_PIN, OUTPUT);
  pinMode(STATUS_PIN, INPUT_PULLUP);

  digitalWrite(START_PIN, LOW);
  digitalWrite(AUTO_PIN, LOW);

  // Connect to Wi-Fi and Blynk
  Serial.printf("Connecting to Wi-Fi SSID: %s\n", ssid);
  Blynk.begin(auth, ssid, pass);

  // Run sendData() every 2 seconds
  timer.setInterval(2000L, sendData);
}

// ---- Loop ----
void loop() {
  Blynk.run();
  timer.run();
}

// ---- Blynk Input Handlers ----
BLYNK_WRITE(V5) {
  int v = param.asInt();
  startState = (v != 0);
  digitalWrite(START_PIN, startState);
  Serial.print("Start Button: ");
  Serial.println(startState ? "ON" : "OFF");
}

BLYNK_WRITE(V8) {
  int v = param.asInt();
  autoState = (v != 0);
  digitalWrite(AUTO_PIN, autoState);
  Serial.print("Auto Mode: ");
  Serial.println(autoState ? "ON" : "OFF");
}

// ---- Send Sensor Data to Blynk ----
void sendData() {
  int16_t raw0 = ads.readADC_SingleEnded(0);
  int16_t raw1 = ads.readADC_SingleEnded(1);
  int16_t raw2 = ads.readADC_SingleEnded(2);
  int16_t raw3 = ads.readADC_SingleEnded(3);

  float volts0 = raw0 * 0.0001875F;
  float volts1 = raw1 * 0.0001875F;
  float volts2 = raw2 * 0.0001875F;
  float volts3 = raw3 * 0.0001875F;

  // --- Using your scaling ---
  float pressure = volts0 * 50.0;    
  float temperature = volts1 * 100.0;
  float humidity = volts2 * 100.0;
  float current = volts3 * 10.0;
  float voltage = 230.0;             
  float flow = 12.5;                 

  // INA219 readings (optional)
  float busVoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float loadVoltage = busVoltage + (ina219.getShuntVoltage_mV() / 1000.0F);

  int statusValue = digitalRead(STATUS_PIN);

  Serial.printf("P:%.2f | T:%.2f | H:%.2f | I:%.2f | V:%.2f | Flow:%.2f | Stat:%d\n",
                pressure, temperature, humidity, current, voltage, flow, statusValue);

  // --- Send data to Blynk ---
  Blynk.virtualWrite(V0, pressure);
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, current);
  Blynk.virtualWrite(V6, voltage);
  Blynk.virtualWrite(V7, flow);
  Blynk.virtualWrite(V9, statusValue);
}
