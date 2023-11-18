#define RED 4
#define YELLOW 3
#define GREEN 2

unsigned long pTimer1 = 0;
unsigned long pTimer2 = 0;

int ledState1 = 0;
int ledState2 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long cTime = millis();

  if (cTime - pTimer1 > 200)
  {
    pTimer1 = cTime;
    ledState1 = !ledState1;
    digitalWrite(RED, ledState1);
  }

  if (cTime - pTimer2 > 300)
  {
    pTimer2 = cTime;
    ledState2 = !ledState2;
    digitalWrite(GREEN, ledState2);
  }

  long r = random(0, 1000);
  Serial.print(String(r) + "\n");
  int rndLedState = (r > 950)? 1 : 0;
  digitalWrite(YELLOW, rndLedState);
}
