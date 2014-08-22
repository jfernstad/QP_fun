
#ifndef __bsp_h_
#define __bsp_h_

#define BSP_TICKS_PER_SEC 100
#define TRIGGER_INTERVAL 10      // ms

extern int led_green;

#ifdef __cplusplus
extern "C"{
#endif

void BSP_init(void);
void BSP_ledOff(void);
void BSP_ledOn(void);

#ifdef __cplusplus
}
#endif

#endif
