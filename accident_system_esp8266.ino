#include <SoftwareSerial.h>

#define BUTTON_PIN D2 // GPIO4 on ESP8266
SoftwareSerial sim800(D7, D8); // RX, TX → D7=GPIO13, D8=GPIO15

void setup() {
  Serial.begin(115200);
  sim800.begin(9600); // Baud rate of GSM module

  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button with pull-up

  Serial.println("ESP8266 Accident Alert System Initialized");
  sim800.println("AT"); // Wake up GSM
  delay(1000);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Accident Detected!");
    sendSMS();
    delay(2000);
    makeCall();
    delay(15000); // avoid repeat
  }
}

void sendSMS() {
  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println("AT+CMGS=\"+911234567890\""); // Replace with actual number
  delay(1000);
  sim800.print("Accident detected! Respond quickly.");
  delay(500);
  sim800.write(26); // CTRL+Z
  Serial.println("SMS sent.");
}

void makeCall() {
  sim800.println("ATD+911234567890;"); // Replace with actual number
  delay(10000); // Let it ring
  sim800.println("ATH"); // Hang up
  Serial.println("Call ended.");
}
