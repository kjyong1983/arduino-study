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

  if (btValA == HIGH)
  {
    Serial.println("a");
    count += 1;
  }

  if (btValB == HIGH)
  {
    Serial.print("b");
    count -= 1;
  }


}
