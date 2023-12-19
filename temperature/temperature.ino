float temperature;
int reading;
int lm35Pin = A0;

void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  reading = analogRead(lm35Pin);
  temperature = reading / 9.31;
    
  Serial.println(temperature);
  delay(1000);
}
