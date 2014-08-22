#include "bsp.h"
#include "arduino.h"

//............................................................................
void BSP_init(void) {
  //DDRB  = 0xFF; // All PORTB pins are outputs (user LED)
  //PORTB = 0x00; // drive all pins low
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
}
//............................................................................
void BSP_ledOff(RDFDUINO_LEDS led) {
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
}
//............................................................................
void BSP_ledOn(RDFDUINO_LEDS led) {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
}
//............................................................................

