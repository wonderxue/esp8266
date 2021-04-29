#include <Arduino.h>
#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
#include <Blinker.h>

#define LED_R 15
#define LED_G 13
#define LED_B 12
char auth[] = "b50f012694a5";
// char ssid[] = "401";
// char pswd[] = "123654789";
char ssid[] = "TP-LINK_06CE";
char pswd[] = "88888888";
bool colorful = false;
void powerState(const String &state)
{
  if (state == BLINKER_CMD_ON)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, HIGH);
    colorful = false;
    BlinkerMIOT.powerState("on");
  }
  else if (state == BLINKER_CMD_OFF)
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    colorful = false;
    BlinkerMIOT.powerState("off");
  }
  BlinkerMIOT.print();
}
void miotColor(int32_t color)
{
  if (color >> 16 & 0xFF == 0xFF)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    colorful = false;
  }
  if (color >> 8 & 0xFF == 0xFF)
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
    colorful = false;
  }
  if (color & 0xFF == 0xFF)
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
    colorful = false;
  }
  BlinkerMIOT.color(color);
  BlinkerMIOT.print();
}
void miMode(uint8_t mode)
{
  if (mode == BLINKER_CMD_MIOT_WARMTH)
  {
    // Your mode function
    colorful = true;
  }
  else if (mode == BLINKER_CMD_MIOT_DAY)
  {
    colorful = false;
  }
  BlinkerMIOT.mode(mode);
  BlinkerMIOT.print();
}

void miQuery(int32_t queryCode)
{
  switch (queryCode)
  {
  case BLINKER_CMD_QUERY_POWERSTATE_NUMBER:
    /* code */
    BlinkerMIOT.powerState(digitalRead(LED_R) ? "on" : "off");
    break;

  default:
    BlinkerMIOT.powerState(digitalRead(LED_R) ? "on" : "off");
    break;
  }
  BlinkerMIOT.print();
}

void setup()
{
  // 初始化串口
  Serial.begin(9600);

#if defined(BLINKER_PRINT)
  BLINKER_DEBUG.stream(BLINKER_PRINT);
#endif

  // 初始化有LED的IO
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
  // 初始化blinker
  Blinker.begin(auth, ssid, pswd);
  BlinkerMIOT.attachPowerState(powerState);
  BlinkerMIOT.attachQuery(miQuery);
  BlinkerMIOT.attachMode(miMode);
  BlinkerMIOT.attachColor(miotColor);
}
int num = 0;
void loop()
{
  Blinker.run();
  if (colorful && num == 0)
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, LOW);
    delay(100);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, HIGH);
    delay(100);
    num++;
  }
  else if (colorful && num == 1)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, LOW);
    delay(100);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, LOW);
    delay(100);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, HIGH);
    delay(100);
    num++;
  }
  else if (colorful && num == 2)
  {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, LOW);
    delay(100);
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_B, HIGH);
    digitalWrite(LED_G, HIGH);
    delay(100);
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_B, LOW);
    digitalWrite(LED_G, HIGH);
    delay(100);
    num = 0;
  }
}