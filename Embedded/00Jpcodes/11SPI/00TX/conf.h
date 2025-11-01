#ifndef CONF_H
#define CONF_H
/*PROTOTIPADO*/
#define LED_ON 0x3A
#define LED_OFF 0xA3
extern void confRCC(void);
extern void confGPIO(void);
extern void confSPI(void);
extern void config(void);
#endif