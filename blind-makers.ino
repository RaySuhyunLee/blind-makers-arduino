#include "HX711.h"
#include <elapsedMillis.h>

/*------ 로드셀 ------*/
#define DOUT  53
#define CLK  51
#define TRUE 49

float zero;

/*------ 시리얼 통신 ------*/
elapsedMillis timerSerial;
#define interval 500;

HX711 scale(DOUT, CLK);

/*------ 제어 ------*/
boolean isAuto = false;

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  initWeight();
}

void loop() {
  if (timerSerial > interval) {
    timerSerial -= interval;
    sendSerial();
  }
}

void checkIsAuto() {
  while (Serial.available()) {
    char buf = Serial.read();
    if (buf == 'a') {
      isAuto = true;
    } else if (buf == 's') {
      isAuto = false;
    }
  }
}

void sendSerial() {
    Serial.print("s");
    Serial.print(getWeight());
    Serial.print(',');
    Serial.print(getBattery());
    Serial.println(';');
}

void initWeight() {

  pinMode(TRUE, OUTPUT);
  digitalWrite(TRUE, 1);

  scale.set_scale(-14000);
  scale.tare();  //Reset the scale to 0
}

float getWeight() {
  scale.power_up();
  float value = scale.get_units(10);
  scale.power_down();
}

float getBattery() {
  return 0;
}
