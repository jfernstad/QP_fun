
#ifndef __bsp_h_
#define __bsp_h_

#define BSP_RTC_FREQ         (32768)
#define BSP_TICKS_PER_SEC    (100)
#define BSP_TICK_DURATION_MS (1000/BSP_TICKS_PER_SEC)
#define TIMER_RESOLUTION_MS  BSP_TICK_DURATION_MS

extern int led_green;

#ifdef __cplusplus
extern "C"{
#endif

typedef enum _RDFDUINO_LEDS{
  LED_RED = 2,
  LED_GREEN = 3, 
  LED_BLUE = 4, 
  LED_YELLOW = 5 
} RDFDUINO_LEDS;

void BSP_init(void);
void BSP_ledOff(RDFDUINO_LEDS led);
void BSP_ledOn(RDFDUINO_LEDS led);

#ifdef __cplusplus
}
#endif

#endif
