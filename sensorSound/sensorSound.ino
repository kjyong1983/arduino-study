int soundSensorPin = A1;
int threshold = 500;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int level = analogRead(soundSensorPin);
  Serial.println(level);

  delay(10);
}
