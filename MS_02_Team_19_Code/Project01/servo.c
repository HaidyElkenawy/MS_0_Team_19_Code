#include "servo.h"
#include "hardware/pwm.h"

// Function to initialize the servo PWM
void servo_init(uint pin) {
    // Set the GPIO pin as PWM
    gpio_set_function(pin, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Configure the PWM frequency to 50 Hz (20 ms period)
    pwm_set_clkdiv(slice_num, 64.0f);           // Clock divider
    pwm_set_wrap(slice_num, 20000);            // PWM period (50 Hz -> 20 ms)
    pwm_set_enabled(slice_num, true);          // Enable PWM output
}

// Function to set the servo angle (0° to 180°)
void servo_set_angle(uint pin, float angle) {
    uint slice_num = pwm_gpio_to_slice_num(pin);

    // Convert angle to pulse width
    // 1ms (5% duty cycle) -> 0°, 1.5ms (7.5%) -> 90°, 2ms (10%) -> 180°
    uint pulse_width = 1000 + (angle / 180.0) * 1000;

    // Set the PWM duty cycle (pulse width in microseconds)
    pwm_set_gpio_level(pin, pulse_width);
}

// Function to toggle the LED
void toggle_led(uint pin, bool *state) {
    *state = !*state; // Toggle the state
    gpio_put(pin, *state);
}
