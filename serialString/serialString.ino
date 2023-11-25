const int bufferNum = 20;
char data1[bufferNum];
char data2[bufferNum];

void setup() {

  Serial.begin(9600);

}

void loop() {
  // 123, 456, 789
  if(Serial.available()){
    String str = Serial.readStringUntil('\n');

    int commaLength = str.indexOf(','); // 3
    if (commaLength != -1)
    {
      //콤마 기준으로 데이터를 분류
      //복사될 버퍼, 어디까지 복사할지, 시작인덱스
      str.toCharArray(data1, commaLength + 1, 0);
      str.toCharArray(data2, str.length() - commaLength, commaLength + 1);
    }
  }

  // Serial.print(data1);
  Serial.print(atoi(data1));
  Serial.print('\t');
  // Serial.println(data2);
  Serial.println(atoi(data2));

  delay(10);
}
