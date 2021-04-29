#include <Arduino.h>
#define BLINKER_WIFI
#include <Blinker.h>
#define ssid "TP-LINK_06CE"
#define pswd "88888888" 
void setup() {
  // put your setup code here, to run once:
  Blinker.begin(ssid,pswd);
}

void loop() {
  // put your main code here, to run repeatedly:
}