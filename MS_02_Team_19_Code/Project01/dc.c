#include "dc.h"
#include "hardware/pwm.h"

// Function to initialize GPIO and PWM
void dc_init() {
    // Set direction pins as output
    gpio_init(DC_DIR_PIN1);
    gpio_set_dir(DC_DIR_PIN1, GPIO_OUT);
    gpio_init(DC_DIR_PIN2);
    gpio_set_dir(DC_DIR_PIN2, GPIO_OUT);

    // Set PWM function for speed control
    gpio_set_function(DC_PWM_PIN, GPIO_FUNC_PWM);

    // Get PWM slice number for the PWM pin
    uint slice_num = pwm_gpio_to_slice_num(DC_PWM_PIN);

    // Set PWM configuration: wrap value and clock divider
    pwm_set_wrap(slice_num, 255);   // 8-bit resolution (0-255)
    pwm_set_clkdiv(slice_num, 4.0f); // Set clock divider
    pwm_set_enabled(slice_num, true); // Enable PWM output
}

// Function to set motor speed and direction
void dc_control(uint16_t speed, bool forward) {
    // Constrain speed to 8-bit range (0-255)
    if (speed > 255) speed = 255;

    // Set motor direction
    if (forward) {
        gpio_put(DC_DIR_PIN1, 1);
        gpio_put(DC_DIR_PIN2, 0);
    } else {
        gpio_put(DC_DIR_PIN1, 0);
        gpio_put(DC_DIR_PIN2, 1);
    }

    // Set PWM duty cycle to control speed
    pwm_set_gpio_level(DC_PWM_PIN, speed);
}
