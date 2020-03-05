#include <Servo.h>
#include <AntaresESP8266HTTP.h>

#define ACCESSKEY "9cbd3b8742d10603:3207c4ec3adddb85"
#define WIFISSID "Salon Asri"
#define PASSWORD "hasanudin5b"
#define projectName "SortingMachine"
#define deviceName "Output"
#define S0 D4
#define S1 D5
#define S2 D6
#define S3 D7
#define sensorOut D8

AntaresESP8266HTTP antares(ACCESSKEY);
Servo myServo;
int frequency = 0;
int color=0;
int count1;
int count2;
unsigned long interval=300000;
unsigned long previousMillis=0;
void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  myServo.attach(D3);
  Serial.begin(9600);
}
void loop() {
  myServo.write(90);
  delay(500);

  color = readColor();
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
   int quant=count1+count2;
  Serial.print("Quantitas");
  Serial.print(quant);
      Serial.print("  ");
  delay(300);
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval) {
 antares.add("Quality",count1);
 antares.add("Quantity",quant);
 antares.send(projectName, deviceName);
  }
  color=0;
}
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("  ");
  delay(50);
  if(R<105 & R>65 & G<95 & G>65){
    color = 2; // biru
  }
  if(G<53 & G>37 & B<44 & B>30){
    color = 1; // putih
  }
 
  return color;  
}
