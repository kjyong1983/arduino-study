#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <DHT11.h> // dht11 by dhruba saha
#include "RTClib.h" // rtclib by adafruit
 
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
//#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW
 
#define MAX_DEVICES 4
#define CS_PIN 10
// clk 13
// din 11
 
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

bool useClock = true;
bool useLm35 = false;
bool useDht11 = true;
bool useSound = false;

// ds3231
RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

// temperature
float fTemperature;
int iTemperature;
int humidity;
int reading;
int temperaturePin = A0;
DHT11 dht11(2);

int soundSensorPin = A1;
int soundThreshold = 500;

// display
const int showDisplayDurationMillis = 5000; // 5 sec
int showDisplayTimer = 0;
const int BufferSize = 50;
byte buffer[BufferSize];
byte bufferClock[BufferSize];
byte bufferTemp[BufferSize];
bool displayOn = true;

// timer
int totalTime = 0;
int deltaTime = 0;
int prevTotalTime = 0;

long lastSoundTimeStamp = 0;
int changeModeTimeIntervalMills = 1000;
// TODO: 1초 안에 소리 두 번 받으면 모드 변환(시계 - 온도)

bool debug = false;

enum ShowMode
{
  clock,
  temperature,
};

ShowMode currentMode;

void setup() { 

  Serial.begin(9600);

  myDisplay.begin();
  myDisplay.setIntensity(1);
  myDisplay.displayClear();

  if (useClock)
  {
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      Serial.flush();
      while (1) delay(10);
    }

    if (rtc.lostPower()) {
      Serial.println("RTC lost power, let's set the time!");
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
  }

  // temperature
  analogReference(INTERNAL);

  pinMode(soundSensorPin, INPUT);

  currentMode = ShowMode::clock;
}

String date;
String time;

void loop() {

  totalTime = millis();
  deltaTime = totalTime - prevTotalTime;

  if (useSound)
  {
    if (showDisplayTimer > 0)
    {
      if (debug)
      {
        showDisplayTimer -= deltaTime;
        // Serial.print("showTimer: ");
        // Serial.print(showDisplayTimer);
        // Serial.print(", deltaTime: ");
        // Serial.println(deltaTime);
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
  }
  else
  {
    // always on
    switch(currentMode)
    {
      case ShowMode::clock:
        memcpy(buffer, bufferClock, BufferSize);
        break;
      case ShowMode::temperature:
        memcpy(buffer, bufferTemp, BufferSize);
        break;
      default:
        break;
    }

    // myDisplay.displayText(buffer, PA_CENTER, 25, 1000, PA_PRINT);
    myDisplay.displayText(buffer, PA_LEFT, 25, 1000, PA_PRINT);

    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
    }
  }  

  if (useClock)
  {
    DateTime now = rtc.now();
    // TODO: show date
    date = String(now.year()) + "/" +  String(now.month()) + "/" +  String(now.day());

    int hour = now.hour();
    if (hour >= 12)
    {
      time = "P" + String(hour - 12) + ":" +  String(now.minute());
    }
    else
    {
      time = "A" + String(hour) + ":" +  String(now.minute());
    }

    time.toCharArray(bufferClock, BufferSize);
  }

  if (useSound)
  {
    int soundLevel = analogRead(soundSensorPin);

    if (soundLevel > soundThreshold)
    {
      Serial.println(soundLevel);
      Serial.println("display on!");

      showDisplayTimer = showDisplayDurationMillis;

      switch(currentMode)
      {
        case ShowMode::clock:
          // buffer = &bufferClock;
          memcpy(buffer, bufferClock, BufferSize);
          break;
        case ShowMode::temperature:
          // buffer = &bufferTemp;
          memcpy(buffer, bufferTemp, BufferSize);
          break;
        default:
          break;
      }

      // myDisplay.displayText(buffer, PA_CENTER, 25, 1000, PA_PRINT);
      myDisplay.displayText(buffer, PA_LEFT, 25, 1000, PA_PRINT);
      displayOn = true;

      long currentTime =  millis();
      if (lastSoundTimeStamp > 0 && currentTime - lastSoundTimeStamp >= changeModeTimeIntervalMills)
      {
        if (currentMode == ShowMode::clock)
        {
          currentMode = ShowMode::temperature;
        }
        else
        {
          currentMode = ShowMode::clock;
        }
      }

      lastSoundTimeStamp = currentTime;
    }
  }
  else
  {
    displayOn = true;
  }

  if (useLm35)
  {
    reading = analogRead(temperaturePin);
    fTemperature = reading / 9.31;

    String str = String(fTemperature);
    str.toCharArray(buffer, BufferSize);
  }
  else if (useDht11)
  {
    iTemperature = dht11.readTemperature();
    humidity = dht11.readHumidity();

    if (iTemperature != DHT11::ERROR_CHECKSUM && iTemperature != DHT11::ERROR_TIMEOUT &&
            humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT)
    {
        String str = String(iTemperature) + "C" + String(humidity) + "%";
        str.toCharArray(bufferTemp, BufferSize);
    }
    else
    {
      if (iTemperature == DHT11::ERROR_TIMEOUT || iTemperature == DHT11::ERROR_CHECKSUM)
      {
          Serial.print("Temperature Reading Error: ");
          Serial.println(DHT11::getErrorString(iTemperature));
      }
      if (humidity == DHT11::ERROR_TIMEOUT || humidity == DHT11::ERROR_CHECKSUM)
      {
          Serial.print("Humidity Reading Error: ");
          Serial.println(DHT11::getErrorString(humidity));
      }
    }
  }
  else
  {
    // ds3231 temperature sensor
    fTemperature = rtc.getTemperature();
    String str = String(fTemperature) + "C";
    str.toCharArray(bufferTemp, BufferSize);
  }

  // delay(1000);
  prevTotalTime = totalTime;

}


