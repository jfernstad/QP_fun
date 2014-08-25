/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

#include <qp_port.h>
#include "Arduino.h"  // always include in your sketch
#include "Blink.h"
#include "rfqp.h"

using namespace QP;

//............................................................................
void QF::onStartup(void) {
    RFDuinoTick::startTick();
}
//............................................................................
void QF::onCleanup(void) {
    RFDuinoTick::stopTick();
}
//............................................................................
void QF::onIdle() {
  QF_INT_ENABLE(); // re-enable interrupts
}
//............................................................................
void Q_onAssert(char const Q_ROM * const Q_ROM_VAR file, int line) {
  RFDuinoTick::stopTick();
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


