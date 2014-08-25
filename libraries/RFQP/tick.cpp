
#include "qp_port.h"
#include "arduino.h"
#include "bsp.h"
#include "tick.h"

using namespace QP;

void RTC1_IRQHandler()
{
  static bool ledOn = false;

  if(NRF_RTC1->EVENTS_TICK != 0)
  {
      NRF_RTC1->EVENTS_TICK = 0; // Reset event
      RFDuinoTick::tick();
  }
}

void RFDuinoTick::startTick()
{
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

void RFDuinoTick::stopTick()
{
    NRF_RTC1->TASKS_STOP = 1;
}

void RFDuinoTick::tick()
{
    QF::TICK((void *)0); // process all armed time events
}
