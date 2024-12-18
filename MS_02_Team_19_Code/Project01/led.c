#include "led.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Leds_init(){
 
    gpio_init(RED_LED_PIN);

    gpio_set_dir(RED_LED_PIN, 1);

     #if(RED_LED_PIN==POSITIVE_LOGIC)
        gpio_put(RED_LED_PIN, 0);
    #else
        gpio_put(RED_LED_PIN, 1);
    #endif
   
}
void Led_on(uint8 pin_number){
  
     if (pin_number == RED_LED_PIN) {
        if (RED_LED_LOGIC_MODE == POSITIVE_LOGIC) {
            gpio_put(RED_LED_PIN, 1);
        } else {
            gpio_put(RED_LED_PIN, 0);
        }
    }

}
void Led_off(uint8 pin_number){

    if (pin_number == RED_LED_PIN) {
        if (RED_LED_LOGIC_MODE == POSITIVE_LOGIC) {
            gpio_put(RED_LED_PIN, 0);
        } else {
            gpio_put(RED_LED_PIN, 1);
        }
    }

}

void Led_toggle(uint8 pin_number){

    if (pin_number == RED_LED_PIN) {
      
            gpio_put(RED_LED_PIN, !(gpio_get(RED_LED_PIN)));
       
    }

}