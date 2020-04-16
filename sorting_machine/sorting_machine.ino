#include <Servo.h>
#include <AntaresESP8266HTTP.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#define ACCESSKEY "9cbd3b8742d10603:3207c4ec3adddb85"
#define WIFISSID "iPhone"
#define PASSWORD "skaskaska"
#define projectName "SortingMachine"
#define deviceName "Output"
#define S0 D3
#define S1 D4
#define S2 D6
#define S3 D7
#define sensorOut D5

AntaresESP8266HTTP antares(ACCESSKEY);
Servo myServo;
int frequency = 0;
int color = 0;
int count1;
int count2;
int quant;
int goodrate;
int red[5], green[5], blue[5];
int batas_red = 0, batas_green = 84, batas_blue = 73;
int batas_red1 = 0, batas_green1 = 37, batas_blue1 = 30;
int batas_red2 = 125, batas_green2 = 100, batas_blue2 = 0;
int batas_red3 = 65, batas_green3 = 65, batas_blue3 = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;

void setup() {
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Menunggu Koneksi");
    WiFiManager wifiManager;
    wifiManager.resetSettings();
    wifiManager.autoConnect("Wifi Manager");
  }
//  Serial.begin(115200);
  antares.setDebug(true);
//  antares.wifiConnection(WIFISSID, PASSWORD);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  myServo.attach(D8);
//  Serial.begin(9600);
}
void loop() {

  unsigned long currentMillis = millis();
  unsigned long currentMillis1 = millis();
  if ((unsigned long)(currentMillis1 - previousMillis1) >= 300) {
    myServo.write(90);
    delay(500);
    color = rgb();
    delay(50);
    switch (color) {
      case 1:
        myServo.write(60);
        count1 ++;
        Serial.print("Good Product=");
        Serial.print(count1);
        Serial.print("  ");
        break;
      case 2:
        myServo.write(120);
        count2 ++;
        Serial.print("Bad Product=");
        Serial.print(count2);
        Serial.print("  ");
        break;
      case 0:
        break;
    }
    quant = count1 + count2;
    goodrate = (quant / count1) * 100;
    Serial.print("Total Product");
    Serial.print(quant);
    Serial.println("  ");
    previousMillis1 = millis();
  }
  color = 0;
  if ((unsigned long)(currentMillis - previousMillis) >= 180000) {
    antares.add("Total Product", quant);
    antares.add("Good Product", count1);
    antares.add("Quality rate (%)", goodrate);
    antares.send(projectName, deviceName);
    Serial.print("Quantitas");
    Serial.print(quant);
    Serial.print("  ");
    previousMillis = millis();
  }

}
