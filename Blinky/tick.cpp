/*
* Tick.h
*
* Let's see if I can get a class to receive the RTC timer interrupt
* From: http://www.mail-archive.com/avr-libc-dev@nongnu.org/msg02454.html
*/

#include "tick.h"

RTCTick::RTCTick()
{
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

// Interrupt callback
void RTCTick::tick()
{
  if (NRF_TIMER1->EVENTS_COMPARE[0] != 0)
  {
    //Serial.println("Timer interrupt called");
    QF::TICK((void *)0); // process all armed time events

    NRF_TIMER1->EVENTS_COMPARE[0] = 0;
  }
}

