/*
* Tick.h
*
* Let's see if I can get a class to receive the RTC timer interrupt
*
*/

#include "qp_port.h"

using namespace QP;

#define BSP_TICKS_PER_SEC 100
#define TRIGGER_INTERVAL 10      // ms

#define STRINGIFY(name) #name
#define CLASS_IRQ(name, vector) \
    static void name(void) asm(STRINGIFY(vector)) \
    __attribute__ ((signal, __INTR_ATTRS))


class RTCTick {
  public:
    RTCTick();
  private:
    CLASS_IRQ(tick, TIMER1_IRQn);
};


