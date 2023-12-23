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

// ************* config
bool useClock = true;
bool useLm35 = false;
bool useDht11 = true;

bool useSound = true;
bool alwaysOn = false;
bool useSwitch = true;

bool debug = true;
bool debugShowTimer = false;
// ************* end of config

int manualSwitchPin = 5;

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
int soundThreshold = 500; // 소리가 클수록 수치가 낮아짐(0~1023)

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

long lastSwitchOnTimeStamp = 0;
int changeModeTimeIntervalMills = 1000;
// TODO: 1초 안에 소리 두 번 받으면 모드 변환(시계 - 온도)

enum ShowMode
{
  clock,
  temperature,
};

ShowMode currentMode;

String date;
String time;

void setup() { 

  Serial.begin(9600);

  pinMode(manualSwitchPin, INPUT_PULLUP);

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

  if (useSound || useSwitch)
  {
    GetTime();

    memcpy(buffer, bufferClock, BufferSize);

    myDisplay.displayText(buffer, PA_LEFT, 25, 1000, PA_PRINT);

    if (myDisplay.displayAnimate()) {
      myDisplay.displayReset();
    }

    showDisplayTimer = showDisplayDurationMillis;
    displayOn = true;    
  }
}

void loop() {

  totalTime = millis();
  deltaTime = totalTime - prevTotalTime;

  if (useSound || useSwitch)
  {
    if (showDisplayTimer > 0)
    {
      showDisplayTimer -= deltaTime;

      if (debugShowTimer)
      {
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
  }
  else if (alwaysOn)
  {
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
    GetTime();
  }

  if (alwaysOn)
  {
    displayOn = true;
  }
  else if (useSwitch || useSound)
  {
    // 사운드 센서가 작동하지 않을 때 수동으로 처리 가능
    bool manualSwitchPressed = digitalRead(manualSwitchPin) == LOW;
    // Serial.println(manualSwitchPressed);

    int soundLevel = analogRead(soundSensorPin);
    bool soundSwitchPressed = soundLevel < soundThreshold;

    bool switchOn = useSwitch && manualSwitchPressed;
    bool soundOn = useSound && soundSwitchPressed;

    if (useSound)
    {
      Serial.println("soundLevel: " + String(soundLevel));
    }

    if (switchOn || soundOn)
    {
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
      // Serial.println("on!");

      long currentTime =  millis();
      // 화면 켜져 있는 동안에 입력 받으면 모드 변환
      if (showDisplayTimer > 0)
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

      lastSwitchOnTimeStamp = currentTime;
    }
  }

  GetTemperature();

  prevTotalTime = totalTime;
}

void GetTime()
{
  DateTime now = rtc.now();
    // TODO: show date
    date = String(now.year()) + "/" +  String(now.month()) + "/" +  String(now.day());

    int hour = now.hour();
    if (hour >= 12)
    {
      if (hour != 12)
      {
        // 오후 12시가 0시가 되지 않게 처리.
        hour = hour - 12;
      }

      time = "P" + String(hour) + ":" +  String(now.minute());
    }
    else
    {
      time = "A" + String(hour) + ":" +  String(now.minute());
    }

    if (debug)
    {
      // Serial.print(now.year(), DEC);
      // Serial.print('/');
      // Serial.print(now.month(), DEC);
      // Serial.print('/');
      // Serial.print(now.day(), DEC);
      // Serial.print(" (");
      // Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
      // Serial.print(") ");
      // Serial.print(now.hour(), DEC);
      // Serial.print(':');
      // Serial.print(now.minute(), DEC);
      // Serial.print(':');
      // Serial.print(now.second(), DEC);
      // Serial.println();

      // Serial.println(date);
      // Serial.println(time);
      // Serial.println("");
    }

    time.toCharArray(bufferClock, BufferSize);
}

void GetTemperature()
{
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
}


