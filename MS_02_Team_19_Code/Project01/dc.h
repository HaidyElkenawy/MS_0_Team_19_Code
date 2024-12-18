#ifndef DC_H_
#define DC_H_

#include "pico/stdlib.h"

// GPIO Pins for Motor Control
#define DC_PWM_PIN 16       // GPIO 8 for PWM (speed control)
#define DC_DIR_PIN1 15      // GPIO 6 for motor direction
#define DC_DIR_PIN2 25      // GPIO 7 for motor direction

// Function Declarations
void dc_init(void);
void dc_control(uint16_t speed, bool forward);

#endif // DC_H_
