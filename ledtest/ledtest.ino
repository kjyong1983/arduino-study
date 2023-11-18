#define RED 4
#define YELLOW 3
#define GREEN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int fade = 0; fade <= 255; fade += 50)
  {
    analogWrite(9, fade);
    delay(100);
  }

  for (int fade = 255; fade >= 0; fade -= 50)
  {
    analogWrite(9, fade);
    delay(100);
  }

  digitalWrite(RED, HIGH);
  delay(1000);
  digitalWrite(RED, LOW);

  digitalWrite(YELLOW, HIGH);
  delay(1000);
  digitalWrite(YELLOW, LOW);

  digitalWrite(GREEN, HIGH);
  delay(1000);
  digitalWrite(GREEN, LOW);


}
