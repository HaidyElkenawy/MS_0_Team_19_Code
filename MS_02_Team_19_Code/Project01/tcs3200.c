#include "tcs3200.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

/* Initialize the TCS3200 sensor */
void TCS3200_Init(void) {
    // Initialize S0, S1, S2, S3 as output pins
    gpio_init(TCS3200_S0_PIN);
    gpio_set_dir(TCS3200_S0_PIN, GPIO_OUT);

    gpio_init(TCS3200_S1_PIN);
    gpio_set_dir(TCS3200_S1_PIN, GPIO_OUT);

    gpio_init(TCS3200_S2_PIN);
    gpio_set_dir(TCS3200_S2_PIN, GPIO_OUT);

    gpio_init(TCS3200_S3_PIN);
    gpio_set_dir(TCS3200_S3_PIN, GPIO_OUT);

    // Initialize OUT_PIN as input
    gpio_init(TCS3200_OUT_PIN);
    gpio_set_dir(TCS3200_OUT_PIN, GPIO_IN);

    // Initialize LED_PIN as output
    gpio_init(TCS3200_LED_PIN);
    gpio_set_dir(TCS3200_LED_PIN, GPIO_OUT);
    TCS3200_ControlLED(true);  // Turn LED ON by default

    // Set default scaling to 20%
    TCS3200_SetScale(TCS3200_SCALE_20_PERCENT);
}

/* Set the frequency scaling of the TCS3200 */
void TCS3200_SetScale(TCS3200_Scale scale) {
    switch (scale) {
        case TCS3200_SCALE_OFF:
            gpio_put(TCS3200_S0_PIN, 0);
            gpio_put(TCS3200_S1_PIN, 0);
            break;
        case TCS3200_SCALE_2_PERCENT:
            gpio_put(TCS3200_S0_PIN, 0);
            gpio_put(TCS3200_S1_PIN, 1);
            break;
        case TCS3200_SCALE_20_PERCENT:
            gpio_put(TCS3200_S0_PIN, 1);
            gpio_put(TCS3200_S1_PIN, 0);
            break;
        case TCS3200_SCALE_100_PERCENT:
            gpio_put(TCS3200_S0_PIN, 1);
            gpio_put(TCS3200_S1_PIN, 1);
            break;
    }
}

/* Read the frequency corresponding to a specific color */
uint32_t TCS3200_ReadColor(TCS3200_Color color) {
    // Set the color filter
    switch (color) {
        case TCS3200_COLOR_RED:
            gpio_put(TCS3200_S2_PIN, 0);
            gpio_put(TCS3200_S3_PIN, 0);
            break;
        case TCS3200_COLOR_GREEN:
            gpio_put(TCS3200_S2_PIN, 1);
            gpio_put(TCS3200_S3_PIN, 1);
            break;
        case TCS3200_COLOR_BLUE:
            gpio_put(TCS3200_S2_PIN, 0);
            gpio_put(TCS3200_S3_PIN, 1);
            break;
    }

    // Measure frequency on OUT_PIN
    uint32_t pulse_count = 0;
    uint64_t start_time = time_us_64();
    uint64_t duration = 100000; // 100 ms measurement window

    while (time_us_64() - start_time < duration) {
        if (gpio_get(TCS3200_OUT_PIN)) {
            pulse_count++;
            while (gpio_get(TCS3200_OUT_PIN)); // Wait for the pulse to end
        }
    }

    return pulse_count; // Return the pulse count as a proxy for frequency
}

/* Control the LED state */
void TCS3200_ControlLED(bool state) {
    gpio_put(TCS3200_LED_PIN, state); // Turn LED ON or OFF
}
