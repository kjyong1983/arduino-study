void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.write('a');
  delay(1000);

  Serial.write('b');
  delay(1000);

}
