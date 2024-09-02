#include <TimerOne.h>

#define Green_LED 12
#define Red_LED 11

volatile bool state = false;

void setup(){
  pinMode(Green_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);

  digitalWrite(Green_LED, LOW);
  digitalWrite(Red_LED, LOW);

  Timer1.initialize(250000);
  Timer1.attachInterrupt(Doraemon);
}

void Doraemon(){
  state = !state;
  digitalWrite(Green_LED, state);
}

void loop(){
  digitalWrite(Red_LED, HIGH);
  delay(1000);
  digitalWrite(Red_LED, LOW);
  delay(1000);
}
