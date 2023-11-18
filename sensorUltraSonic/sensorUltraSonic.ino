#include <Servo.h>

int trigPin = 7;
int echoPin = 8;

Servo servo;
int servoPin = 9;

void setup() {
  Serial.begin(9600);

  servo.attach(servoPin);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int cm = (duration/2)/29.1;
  Serial.println(cm);

  int deg = map(cm, 2, 50, 0, 180);
  deg = constrain(deg, 0, 180);

  servo.write(deg);
  delay(20);
}
