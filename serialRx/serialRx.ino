char data;
int ledPin = 13;

void setup() {
  put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    data = Serial.read();
  }

  if(data == 'a')
  {
    digitalWrite(ledPin, HIGH);
  }
  else if(data == 'b')
  {
    digitalWrite(ledPin, LOW);
  }
}
