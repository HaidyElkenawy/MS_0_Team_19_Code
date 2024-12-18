#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

#include "pico/stdlib.h"

/* Define the GPIO pin connected to the IR sensor */
#define IR_SENSOR_PIN 19 // Replace with your actual GPIO pin

/* Function prototypes */
void IR_Sensor_Init(void);
bool IR_Sensor_DetectObstacle(void);

#endif // IR_SENSOR_H_
