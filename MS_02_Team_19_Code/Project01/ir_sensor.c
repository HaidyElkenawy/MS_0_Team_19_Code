#include "ir_sensor.h"

/* Initialize the IR sensor */
void IR_Sensor_Init(void) {
    gpio_init(IR_SENSOR_PIN);           // Initialize the GPIO pin
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN); // Set the pin as input
}

/* Detect obstacle using the IR sensor */
bool IR_Sensor_DetectObstacle(void) {
    return !gpio_get(IR_SENSOR_PIN); // Active LOW: Returns true if an obstacle is detected
}
