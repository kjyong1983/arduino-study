#include <Servo.h>

// int ledPin = 3;
int servoPin = 9;
// int analogPinA0 = A0;
// int bzPin = 6;

Servo servo;

enum ServoActionType
{
  None = -1,
  Push,
  Pull,
  PushHold,
  PushRepeat
};

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  // pinMode(ledPin, OUTPUT);
  // pinMode(bzPin, OUTPUT);

  servo.write(0);

}

int prevDeg = 0;

void ServeTest()
{
  int speed = 5;
  for(int i = 0; i < 180; i+=speed)
  {
    servo.write(i);
    delay(50);
  }

  for(int i = 180; i > 0; i-=speed)
  {
    servo.write(i);
    delay(50);
  }
}

void loop() {
  // ServoTest();

  // 아날로그 입력을 받아서 밝기와 모터를 조절
  {
    char data = -1;

    if(Serial.available())
    {
      data = Serial.read();
      // Serial.print("data: \'");
      // Serial.print(data);
      // Serial.println("\'");
    }

    int deg = -1;

    // ServoActionType actionType = ServoActionType::None;
    ServoActionType actionType = static_cast<ServoActionType>((int)data);

    // switch(actionType)
    // {
    //   case ServoActionType::Push:
    //     Serial.println("Push");
    //     deg = 180;
    //     break;
    //   case ServoActionType::Pull:
    //     Serial.println("Pull");
    //     deg = 0;
    //     break;
    //   default:
    //     break;
    // }

    switch(data)
    {
      case '1':
        Serial.println("Push");
        deg = 180;
        break;
      case '0':
        Serial.println("Pull");
        deg = 0;
        break;
      default:
        break;
    }

    if (deg >= 0 && prevDeg != deg)
    {
      Serial.print("moving deg to: ");
      Serial.println(deg);
      servo.write(deg);
      delay(500);

      prevDeg = deg;
    }

    delay(50);

  }

}
