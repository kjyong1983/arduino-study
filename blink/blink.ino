#define MYPIN 9
#define LED_SPEED 100

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(MYPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(MYPIN, HIGH);

  delay(LED_SPEED);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(MYPIN, LOW);

  delay(LED_SPEED);

}
