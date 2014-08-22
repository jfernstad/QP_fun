/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

#include <qp_port.h>
#include "Arduino.h"  // always include in your sketch
#include "Blink.h"
#include "bsp.h"
#include "tick.h"

// Pin 3 has an green LED connected on the RGB LED shield
// give it a name:

using namespace QP;



//void TIMER1_Interrupt(void)
void TIMER1_IRQHandler(void)
{
  if (NRF_TIMER1->EVENTS_COMPARE[0] != 0)
  {
    //Serial.println("Timer interrupt called");
    QF::TICK((void *)0); // process all armed time events

    NRF_TIMER1->EVENTS_COMPARE[0] = 0;
  }
}
//............................................................................
void QF::onStartup(void) {
  NRF_TIMER1->TASKS_STOP = 1;   // Stop timer
  NRF_TIMER1->MODE = TIMER_MODE_MODE_Timer;  // taken from Nordic dev zone
  NRF_TIMER1->BITMODE = (TIMER_BITMODE_BITMODE_16Bit << TIMER_BITMODE_BITMODE_Pos);
  NRF_TIMER1->PRESCALER = 4;   // SysClk/2^PRESCALER) =  16,000,000/16 = 1us resolution
  NRF_TIMER1->TASKS_CLEAR = 1; // Clear timer
  NRF_TIMER1->CC[0] = TRIGGER_INTERVAL * 1000; // Cannot exceed 16bits
  NRF_TIMER1->INTENSET = TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;  // taken from Nordic dev zone
  NRF_TIMER1->SHORTS = (TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos);
  //attachInterrupt(TIMER1_IRQn, TIMER1_Interrupt);    // also used in variant.cpp to configure the RTC1
  NVIC_EnableIRQ(TIMER1_IRQn);
  NRF_TIMER1->TASKS_START = 1;   // Start TIMER
}
//............................................................................
void QF::onCleanup(void) {
}
//............................................................................
void QF::onIdle() {
  QF_INT_ENABLE(); // re-enable interrupts
}
//............................................................................
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
  QF_INT_DISABLE(); // disable all interrupts
  BSP_ledOn(LED_RED); // User LED permanently ON
  //asm volatile ("jmp 0x0000"); // perform a software reset of the Arduino

}

static Blinky l_blinky;                            // the Blinky active object
static QEvt const *l_blinkyQSto[10];         // Event queue storage for Blinky
//static RTCTick tick;

//............................................................................
void setup() {
  BSP_init(); // initialize the BSP
  QF::init(); // initialize the framework and the underlying RT kernel

  l_blinky.start(1U,
                 l_blinkyQSto, Q_DIM(l_blinkyQSto),
                 (void *)0, 1024);

  QF::run();
}

//////////////////////////////////////////////////////////////////////////////
// NOTE1: Do not define the loop() function, because this function is
// already defined in the QP port to Arduino


