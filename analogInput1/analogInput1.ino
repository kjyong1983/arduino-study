int ledPin9 = 9;
int analogPin = A0;

int varRes = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin9, OUTPUT);
  // 아날로그 입력은 핀모드를 지정하지 않는다(이미 INPUT이기 때문)
}

void loop() {
  int analogInput = analogRead(analogPin);
  // Serial.println(analogInput);

  int analogInputMap = map(analogInput, 0, 1023, 0, 255);
  // Serial.print("A0 val: ");
  // Serial.print(analogInput);
  // Serial.print('\t');
  // Serial.print("mapped as: ");
  // Serial.println(analogInputMap);

  Serial.println("A0 val: " + String(analogInput) + '\t' + "mapped as: " + String(analogInputMap));

  // 딜레이 시간 조정
  if (false)
  {
    digitalWrite(ledPin9, HIGH);
    delay(analogInput);
    digitalWrite(ledPin9, LOW);
    delay(analogInput);
  }

  // 밝기 조절
  {
    // 아날로그 입력은 0~1023
    // 아날로그 출력은 0~255
    analogWrite(ledPin9, analogInput / 4);
  }

}
