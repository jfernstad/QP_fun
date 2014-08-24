/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

#include <qp_port.h>
#include "Arduino.h"  // always include in your sketch
#include "Blink.h"
#include "bsp.h"

using namespace QP;

void RTC1_IRQHandler()
{
  static bool ledOn = false;

  if(NRF_RTC1->EVENTS_TICK != 0)
  {
    NRF_RTC1->EVENTS_TICK = 0;
    QF::TICK((void *)0); // process all armed time events
  }
}

//............................................................................
void QF::onStartup(void) {

  NRF_CLOCK->LFCLKSRC = (CLOCK_LFCLKSRC_SRC_RC << CLOCK_LFCLKSRC_SRC_Pos);
  NRF_CLOCK->EVENTS_LFCLKSTARTED = 0; 
  NRF_CLOCK->TASKS_LFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0) {}
  
  NRF_RTC1->TASKS_STOP = 1;
  NRF_RTC1->PRESCALER = BSP_RTC_FREQ/BSP_TICKS_PER_SEC;

  NRF_RTC1->EVTENSET = (RTC_EVTENSET_TICK_Enabled << RTC_EVTENSET_TICK_Pos);
  NRF_RTC1->INTENSET = (RTC_INTENSET_TICK_Enabled << RTC_INTENSET_TICK_Pos);

  NVIC_EnableIRQ(RTC1_IRQn);
  NRF_RTC1->TASKS_START = 1;
}
//............................................................................
void QF::onCleanup(void) {
  // TODO
}
//............................................................................
void QF::onIdle() {
  QF_INT_ENABLE(); // re-enable interrupts
}
//............................................................................
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
  QF_INT_DISABLE(); // disable all interrupts
  BSP_ledOn(LED_RED); // User LED permanently ON
HALT:
  goto HALT;
}

static Blinky l_blinky;                            // the Blinky active object
static QEvt const *l_blinkyQSto[10];         // Event queue storage for Blinky

//............................................................................
void setup() {
  BSP_init(); // initialize the BSP
  QF::init(); // initialize the framework and the underlying RT kernel

  l_blinky.start(1U,
                 l_blinkyQSto, Q_DIM(l_blinkyQSto),
                 (void *)0, 1024);

  QF::run();
}


