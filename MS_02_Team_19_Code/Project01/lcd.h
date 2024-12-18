#ifndef LCD_H_
#define LCD_H_

#include "pico/stdlib.h"
#include "hardware/i2c.h"

/* I2C Definitions */
// I2C Configuration for Nano RP2040
#define I2C_PORT i2c0
#define SDA_PIN 12   // A4 / GPIO12
#define SCL_PIN 13   // A5 / GPIO13
#define LCD_ADDR 0x27 // Default I2C address for the LCD module

void lcd_send_byte(uint8_t data, uint8_t mode);
void lcd_init();
void lcd_clear();
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_write_string(const char *str);


#endif /* LCD_H_ */