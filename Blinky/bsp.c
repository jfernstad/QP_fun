#include "bsp.h"
#include "arduino.h"

int led_green = 3;

//............................................................................
void BSP_init(void) {
  //DDRB  = 0xFF; // All PORTB pins are outputs (user LED)
  //PORTB = 0x00; // drive all pins low
  pinMode(led_green, OUTPUT);
}
//............................................................................
void BSP_ledOff(void) {
  digitalWrite(led_green, LOW);    // turn the LED off by making the voltage LOW
//  analogWrite(led_green, 0);
}
//............................................................................
void BSP_ledOn(void) {
  digitalWrite(led_green, HIGH);   // turn the LED on (HIGH is the voltage level)
//  analogWrite(led_green, 200);
}
//............................................................................

