

#include<Keyboard.h>

int keyPin1 = 8;
int keyPin2 = 9;


void setup() {
 Serial.begin(9600);

 pinMode(keyPin1, INPUT_PULLUP);
 pinMode(keyPin2, INPUT_PULLUP);
}

int prevKey1Pressed = 0;
int prevKey2Pressed = 0;

void loop()  {
  int key1Pressed = 0;
  int key2Pressed = 0;
  
  key1Pressed = digitalRead(keyPin1);
  key2Pressed = digitalRead(keyPin2);

  if (key1Pressed == LOW && prevKey1Pressed != key1Pressed)
  {
    Serial.println("1 pressed");
  }

  if (key2Pressed == LOW && prevKey2Pressed != key2Pressed)
  {
    Serial.println("2 pressed");
  }

  prevKey1Pressed = key1Pressed;
  prevKey2Pressed = key2Pressed;
 
  delay(50);
}
