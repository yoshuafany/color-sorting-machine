#include <Servo.h>
#include <AntaresESP8266HTTP.h>

#define ACCESSKEY "9cbd3b8742d10603:3207c4ec3adddb85"
#define WIFISSID "WiWiN"
#define PASSWORD "08121974"
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
int red[5], green[5], blue[5];
int batas_red = 0, batas_green = 84, batas_blue = 73;
int batas_red1 = 0, batas_green1 = 37, batas_blue1 = 30;
int batas_red2 = 125, batas_green2 = 120, batas_blue2 = 0;
int batas_red3 = 65, batas_green3 = 65, batas_blue3 = 0;
unsigned long previousMillis1 = 0;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID, PASSWORD);

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  attachInterrupt(digitalPinToInterrupt(D1), kalibrasi_good, FALLING);
  attachInterrupt(digitalPinToInterrupt(D2), kalibrasi_bad, FALLING);
  myServo.attach(D8);
  Serial.begin(9600);
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
    Serial.print("Quantitas");
    Serial.print(quant);
    Serial.println("  ");
    previousMillis1 = millis();
  }
  color = 0;
  if ((unsigned long)(currentMillis - previousMillis) >= 180000) {
    antares.add("Quantity", quant);
    antares.add("Quality", count1);

    antares.send(projectName, deviceName);
    Serial.print("Quantitas");
    Serial.print(quant);
    Serial.print("  ");
    previousMillis = millis();
  }

}

void kalibrasi_good() {
  if ((millis() - previousMillis2) > 100) {
    for (int i = 0; i < 5; i++) {
      red[i] = read_R();
      green[i] = read_G();
      blue[i] = read_B();
    }
    for (int j = 0; j < 5; j++) {
      batas_red += red[j];
      batas_green += green[j];
      batas_blue += blue[j];
    }
    batas_red /= 5;
    batas_green /= 5;
    batas_blue /= 5;

    batas_red += 20;
    batas_red1 = batas_red - 40;
    batas_green += 20;
    batas_green1 = batas_green - 40;
    batas_blue += 20;
    batas_blue1 = batas_blue - 40;
    Serial.print(batas_red);
    Serial.print("\t");
    Serial.print(batas_red1);
    Serial.print("\t");
    Serial.print(batas_green);
    Serial.print("\t");
    Serial.print(batas_green1);
    Serial.print("\t");
    Serial.print(batas_blue);
    Serial.print("\t");
    Serial.println(batas_blue1);
    previousMillis2 = millis();
  }
}

void kalibrasi_bad() {
  if ((millis() - previousMillis3) > 100) {
    for (int i = 0; i < 5; i++) {
      red[i] = read_R();
      green[i] = read_G();
      blue[i] = read_B();
    }
    for (int j = 0; j < 5; j++) {
      batas_red2 += red[j];
      batas_green2 += green[j];
      batas_blue2 += blue[j];
    }
    batas_red2 /= 5;
    batas_green2 /= 5;
    batas_blue2 /= 5;

    batas_red2 += 20;
    batas_red3 = batas_red2 - 40;
    batas_green2 += 20;
    batas_green3 = batas_green2 - 40;
    batas_blue2 += 20;
    batas_blue3 = batas_blue2 - 40;
    Serial.print(batas_red2);
    Serial.print("\t");
    Serial.print(batas_red3);
    Serial.print("\t");
    Serial.print(batas_green2);
    Serial.print("\t");
    Serial.print(batas_green3);
    Serial.print("\t");
    Serial.print(batas_blue2);
    Serial.print("\t");
    Serial.println(batas_blue3);
    previousMillis3 = millis();
  }
}
