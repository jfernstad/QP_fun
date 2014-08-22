
#ifndef __bsp_h_
#define __bsp_h_

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
