int cdsPin = A0;
const int readCount = 20;
int avgVal = 0;
int sensorReading[readCount];
int index = 0;
int totalVal = 0;
int fadeVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for(int i = 0; i < readCount; i++)
  {
    sensorReading[i] = 0;
  }

  pinMode(3, OUTPUT);
}

void loop() {
  // 기본적인 값 읽기
  int aVal = analogRead(A0);
  // Serial.println(aVal);

  totalVal = totalVal - sensorReading[index];

  sensorReading[index] = analogRead(cdsPin);
  totalVal = totalVal + sensorReading[index];
  index = index + 1;

  if (index >= readCount) index = 0;

  avgVal = totalVal / readCount;

  fadeVal = map(avgVal, 100, 500, 0, 255);
  // 값이 정해진 값을 벗어나는 경우 클램프를 건다
  constrain(fadeVal, 0, 255);

  analogWrite(3, fadeVal);

  Serial.print("original Val: ");
  Serial.print(aVal);
  Serial.print('\t');
  Serial.print("avg Val: ");
  Serial.print(avgVal);
  Serial.print('\t');
  Serial.print("fadeVal: ");
  Serial.println(fadeVal);

  delay(20);
}
