
#ifndef LED_H_
#define LED_H_

#include "std_types.h"
#include "pico/stdlib.h"

/* MY DEFINITIONS */

#define RED_LED_PIN    16


#define RED_LED_LOGIC_MODE               POSITIVE_LOGIC
#define GREEN_LED_LOGIC_MODE             POSITIVE_LOGIC
#define BLUE_LED_LOGIC_MODE              NEGATIVE_LOGIC

#define POSITIVE_LOGIC               0
#define NEGATIVE_LOGIC               1
/****************** */

/*Functions Prototypes*/
void Leds_init();

void Led_on(uint8 pin_number);

void Led_off(uint8 pin_number);

void Led_toggle(uint8 pin_number);
/***********************/

#endif /* LED_H_ */