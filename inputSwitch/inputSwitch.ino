int btPinA = 2;
int ledPinA = 9;

int btPinB = 4;
int ledPinB = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(btPinA, INPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(btPinB, INPUT);
  pinMode(ledPinB, OUTPUT);
}

void loop() {

  int btValA = digitalRead(btPinA);
  int btValB = digitalRead(btPinB);

  // if (btValA == HIGH)
  // {
  //   digitalWrite(ledPinA, HIGH);
  // }
  // else
  // {
  //   digitalWrite(ledPinA, LOW);
  // }

  if (btValA == HIGH && btValB == HIGH)
  {
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, HIGH);
  }
  else if (btValA == HIGH && btValB == LOW) {
    digitalWrite(ledPinA, HIGH);
    digitalWrite(ledPinB, LOW);

  }
  else if (btValA == LOW && btValB == HIGH) {
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, HIGH);

  }
  else {
    digitalWrite(ledPinA, LOW);
    digitalWrite(ledPinB, LOW);
  }

}
