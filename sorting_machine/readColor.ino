int read_R() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  delay(50);
  Serial.print(R);
  Serial.print("\t");
  return R;
}

int read_G() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  delay(50);
  Serial.print(G);
  Serial.print("\t");
  return G;
}

int read_B() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  delay(50);
  Serial.print(B);
  Serial.println("\t");
  return B;
}
