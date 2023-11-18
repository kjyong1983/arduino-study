int btPinA = 2;
int ledPinA = 9;

int btPinB = 4;
int ledPinB = 12;

int count = 0;

int btValA_p = 0;

void setup() {
  Serial.begin(9600);

  pinMode(btPinA, INPUT);
  pinMode(btPinB, INPUT);

  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}

void loop() {

  int btValA = digitalRead(btPinA);
  int btValB = digitalRead(btPinB);

  // Serial.print("A: " + String(btValA) + ", B: " + String(btValB) + "\n");


  if (btValA == HIGH && btValA_p == LOW)
  {
    Serial.println("a");
    count += 30;

    if (count >= 255) count= 0;
  }

  if (btValB == HIGH)
  {
    Serial.println("b");
    // count -= 1;
  }

  // Serial.println(count);

  analogWrite(ledPinA, count);
  btValA_p = btValA;

}
