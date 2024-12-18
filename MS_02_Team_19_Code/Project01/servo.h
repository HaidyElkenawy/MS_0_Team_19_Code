#ifndef SERVO_H_
#define SERVO_H_

#include "pico/stdlib.h"

// Define GPIO pins
#define SERVO_PIN 26
#define SERVO_PIN_5 27
#define SERVO_PIN_4 5
#define SERVO_PIN_1 20
#define SERVO_PIN_2 18
// Function prototypes
void servo_init(uint pin);
void servo_set_angle(uint pin, float angle);
void toggle_led(uint pin, bool *state);

#endif // SERVO_H_
