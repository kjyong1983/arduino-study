int soundSensorPin = A1;
int threshold = 500;

void setup() {
  Serial.begin(9600);
  pinMode(soundSensorPin, INPUT);
}

void loop() {
  int level = analogRead(soundSensorPin);

  if (level > threshold)
  {
    Serial.println(level);
  }

  delay(100);
}
