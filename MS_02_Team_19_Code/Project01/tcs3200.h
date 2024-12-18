#ifndef TCS3200_H_
#define TCS3200_H_

#include "stdint.h"
#include "pico/stdlib.h"

// GPIO pins connected to the TCS3200 sensor
#define TCS3200_S0_PIN   21
#define TCS3200_S1_PIN   17
#define TCS3200_S2_PIN   6
#define TCS3200_S3_PIN   0
#define TCS3200_OUT_PIN  28

#define TCS3200_LED_PIN  18 // GPIO pin connected to the LED

// Frequency scaling options
typedef enum {
    TCS3200_SCALE_OFF = 0,
    TCS3200_SCALE_2_PERCENT,
    TCS3200_SCALE_20_PERCENT,
    TCS3200_SCALE_100_PERCENT
} TCS3200_Scale;

// Color modes
typedef enum {
    TCS3200_COLOR_RED = 0,
    TCS3200_COLOR_GREEN,
    TCS3200_COLOR_BLUE
} TCS3200_Color;

// Function prototypes
void TCS3200_Init(void);
void TCS3200_SetScale(TCS3200_Scale scale);
uint32_t TCS3200_ReadColor(TCS3200_Color color);
void TCS3200_ControlLED(bool state);

#endif // TCS3200_H_
