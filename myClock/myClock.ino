#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
 
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
 
#define MAX_DEVICES 4
#define CS_PIN 10
 
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int num = 0;




float temperature;
int reading;
int lm35Pin = A0;



int soundSensorPin = A1;
int soundThreshold = 500;


bool useClock = false;
bool useTemperature = true;
bool useSound = true;

const int showDisplayDurationMillis = 5000; // 5 sec
int showDisplayTimer = 0;

const int BufferSize = 50;
byte buffer[BufferSize];

void setup() { 

  Serial.begin(9600);

  myDisplay.begin();
  myDisplay.setIntensity(1);
  myDisplay.displayClear();

  if (useClock)
  {
    myDisplay.displayText("A88:88", PA_LEFT, 200, 200, PA_PRINT);
  }

  // temperature
  analogReference(INTERNAL);

  pinMode(soundSensorPin, INPUT);


}

// byte* string2Buf(String str)
// {
//   int bufferLen = str.length() + 1;
//   byte buffer[bufferLen];
//   str.toCharArray(buffer, bufferLen);

//   return buffer;
// }

bool displayOn = true;

int totalTime = 0;
int deltaTime = 0;
int prevTotalTime = 0;

bool debug = false;

// todo: mode: time, temperature

void loop() {

  totalTime = millis();
  deltaTime = totalTime - prevTotalTime;

  if (showDisplayTimer > 0)
  {
    if (debug)
    {
      showDisplayTimer -= deltaTime;
      Serial.print("showTimer: ");
      Serial.print(showDisplayTimer);
      Serial.print(", deltaTime: ");
      Serial.println(deltaTime);
    }

    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
  }

  }
  else
  {
    if (displayOn == true)
    {
      displayOn = false;
      myDisplay.displayClear();

      Serial.println("display off!");

    }
  }

  if (useClock)
  {
    // String str = String(num);
    // int bufferLen = str.length() + 1;
    // byte buffer[bufferLen];
    // str.toCharArray(buffer, bufferLen);

    // myDisplay.displayText(buffer, PA_LEFT, 200, 200, PA_PRINT);

    // if (myDisplay.displayAnimate()) {
    //   myDisplay.displayReset();
    // }

    num++;
  }

  if (useSound)
  {
    int soundLevel = analogRead(soundSensorPin);

    if (soundLevel > soundThreshold)
    {
      // Serial.println(soundLevel);

      Serial.println("display on!");

      showDisplayTimer = showDisplayDurationMillis;
      myDisplay.displayText(buffer, PA_CENTER, 25, 1000, PA_PRINT);
      displayOn = true;
    }

    // delay(100);

  }

  if (useTemperature)
  {
    reading = analogRead(lm35Pin);
    temperature = reading / 9.31;
      
    // Serial.println(temperature);


    // String str = String(temperature);
    // int bufferLen = str.length() + 1;
    // byte buffer[bufferLen];
    // str.toCharArray(buffer, bufferLen);

    String str = String(temperature);
    // int bufferLen = str.length() + 1;
    // byte buffer[bufferLen];
    str.toCharArray(buffer, BufferSize);


    // myDisplay.displayText(string2Buf(String(temperature)), PA_LEFT, 200, 200, PA_PRINT);
    // myDisplay.displayText(buffer, PA_LEFT, 200, 200, PA_PRINT);

    // if (myDisplay.displayAnimate()) {
    //   myDisplay.displayReset();
    // }



  }

  // if (myDisplay.displayAnimate()) {
  //   myDisplay.displayReset();
  // }

  // delay(1000);
  prevTotalTime = totalTime;

}


