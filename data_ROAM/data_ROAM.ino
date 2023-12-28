#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#define LED1 2      // Assign LED1 to pin GPIO2 (D2)
#define PIR 5       // Assign PIR to pin GPIO5 (D1)
#define IR_Outdoor 12 // Outdoor IR to pin GPIO12 (D6)
#define IR_Indoor 14 // Outdoor IR to pin GPIO14 (D5)
#define Mic A0 // Mic to pin ADC0

void setup() {

  pinMode(LED1, OUTPUT); // initialize LED D2
  pinMode(PIR, INPUT); // initialize sensor output D5
  Serial.begin(9600);

}

// the loop function runs forever

void loop() {

  int PIRval = digitalRead(PIR);
  Serial.println(PIRval);

  if (PIRval == HIGH) {
    digitalWrite(LED1,HIGH);
    delay(1000);
  }
  else {
    digitalWrite(LED1,LOW);
  }
}