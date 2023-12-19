#include <Servo.h>

int ledPin = 3;
int servoPin = 9;
int analogPinA0 = A0;
// int bzPin = 6;

Servo servo;

void setup() {
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(bzPin, OUTPUT);
}
  int playTime = 50;

void loop() {

  // int analogInput = analogRead(analogPinA0);

  // {
  //   int analogInput = analogRead(analogPinA0);
  //   int speed = map(analogInput, 0, 1023, 1, 5);

  //   for(int i = 0; i < 180; i+=speed)
  //   {
  //     servo.write(i);
  //     delay(10);
  //   }

  //   for(int i = 180; i > 0; i-=speed)
  //   {
  //     servo.write(i);
  //     delay(10);
  //   }
  // }


  // 아날로그 입력을 받아서 밝기와 모터를 조절
  {



    
    int analogVal = analogRead(analogPinA0);
    int deg = map(analogVal, 0, 1023, 0, 180);
    servo.write(deg);

    int brightness = map(analogVal, 0, 1023, 0, 255);
    analogWrite(ledPin, brightness);
  }

}
