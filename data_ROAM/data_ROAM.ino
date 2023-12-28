#include <HTTPClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Arduino.h>

#define LED1 2      // Assign LED1 to pin GPIO2 (D2)
#define PIR 5       // Assign PIR to pin GPIO5 (D1)
#define IR_Outdoor 12 // Outdoor IR to pin GPIO12 (D6)
#define IR_Indoor 14 // Outdoor IR to pin GPIO14 (D5)
#define Mic A0 // Mic to pin ADC0
StaticJsonDocument<500> doc
RTC_DATA_ATTR int bootCount = 0;

const char* ssid = "Imperial-WPA";     
const char* password = "XXXX"; //to replace with personal password
const char* server = "https://eu-west-2.aws.data.mongodb-api.com/app/data-hozcj/endpoint/data/v1";
 
WiFiClient client;

void setup() {
  ++bootCount;

  int incomer = 0;
  int outgoer = 0;
  int current_ppl = 0;

  pinMode(LED1, OUTPUT); // initialize LED D2
  pinMode(PIR, INPUT); // initialize sensor output D5
  pinMode(IR_Outdoor, INPUT);
  pinMode(IR_Indoor, INPUT);
  pinMode(Mic, INPUT);
  Serial.begin(9600);

  Serial.print("Connecting: ");
  Serial.print(ssid);
  Serial.print("| Password: ");
  Serial.println(password);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting...");
  }
  Serial.println("Connected!");
  Serial.print(" WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

}

void POSTData()
{

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    String json;
    serializeJson(doc, json);

    Serial.println(json);
    int httpResponseCode = http.POST(json);
    Serial.println(httpResponseCode);
  }
}

void getDevice()
{

  uint64_t chipid = ESP.getEfuseMac();
  Serial.printf("***ESP8266 Chip ID = 78:e3:6d:09:40:5d00", (uint16_t)(chipid >> 32), (uint32_t)chipid); 
  char buffer[200];
  sprintf(buffer, "78:e3:6d:09:40:5d00", (uint16_t)(chipid >> 32), (uint32_t)chipid);

  doc["device"]["IP"] = WiFi.localIP().toString();
  doc["device"]["RSSI"] = String(WiFi.RSSI());
  doc["device"]["type"] = "ESP8266";
  doc["device"]["chipid"] = buffer;
  doc["device"]["bootCount"] = bootCount;


}

int volume() {
  unsigned long startMillis= millis();                   // Start of sample window
  float peak2peak = 0;                                  // peak-to-peak level

  unsigned int sigMax = 0;                            //minimum value
  unsigned int sigMin = 1024;                         //maximum value

  while (millis() - startMillis < sampleWindow)         // collect data for 50 mS
  {
    sample = analogRead(Mic);                           //get reading from microphone
    if (sample < 1024)                                  // remove irrelevant readings
    {
        if (sample > sigMax)
        {
          sigMax = sample;                           // save just the max levels
        }
        else if (sample < sigMin)
        {
          sigMin = sample;                           // save just the min levels
        }
    }
  }

  peak2peak = sigMax - sigMin;                        // max - min = peak-peak amplitude
  int db = map(peak2peak,20,900,49.5,90);             //calibrate for deciBels
  doc["mic"]["volume"] = db;
  return db;
}

void PIR() {
  int PIRval = digitalRead(PIR);
  Serial.println(PIRval);
  
  doc["PIR"]["motion"] = PIRval;
  }
  return PIRval;
}

int IO() {
  int comein = digitalRead(IR_Outdoor);
  int goout = digitalRead(IR_Indoor);

  if (comein == 0) {
    delay(100)
    if (goout == 0) {
      incomer = incomer++;
    }
  }

  if (goout == 0) {
    delay(100)
    if (comein == 0) {
      outgoer = outgoer++;
    }
  }

  current_ppl = incomer - outgoer;

  doc["IO"]["visitors"] = incomer;
  doc["IO"]["leavers"] = outgoer;
  doc["IO"]["current"] = current_ppl;

  return current_ppl;
}

void loop() {
  getDevice();
  int ppl = IO();
  int motion = PIR();
  int volume = volume();
  Serial.println("Sending...");
  POSTData();
  serializeJsonPretty(doc, Serial);
}