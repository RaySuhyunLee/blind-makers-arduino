#include "HX711.h"

/*----- 로드셀 -----*/
#define DOUT  53
#define CLK  51
#define TRUE 49

float zero;

HX711 scale(DOUT, CLK);

/* */

void setup() {
  // put your setup code here, to run once
  Serial.begin(9600);

  initWeight();
}

void loop() {
  Serial.print(getWeight());
  Serial.print(',');
  Serial.print(getBattery());
  Serial.println(';');

  delay(10);
}

boolean isAuto() {
  // TODO check distance sensor value
}

void initWeight() {

  pinMode(TRUE, OUTPUT);
  digitalWrite(TRUE, 1);

  scale.set_scale(-14000);
  scale.tare();  //Reset the scale to 0
  zero = scale.get_units();
}

float getWeight() {
  return scale.get_units() - zero;
}

float getBattery() {
  return 0;
}
