#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd.h"

// Low-level function to send data to the LCD
void lcd_send_byte(uint8_t data, uint8_t mode) {
    uint8_t high_nibble = (data & 0xF0) | mode | 0x08; // High nibble
    uint8_t low_nibble = ((data << 4) & 0xF0) | mode | 0x08; // Low nibble

    uint8_t sequence[] = {
        high_nibble | 0x04, high_nibble,  // High nibble with Enable
        low_nibble | 0x04, low_nibble    // Low nibble with Enable
    };

    i2c_write_blocking(I2C_PORT, LCD_ADDR, sequence, 4, false);
}

// Initialize the LCD
void lcd_init() {
    sleep_ms(50);  // Wait for the LCD to power up

    // Initialize in 4-bit mode
    lcd_send_byte(0x03, 0);
    sleep_ms(5);
    lcd_send_byte(0x03, 0);
    sleep_us(150);
    lcd_send_byte(0x03, 0);
    lcd_send_byte(0x02, 0);  // Switch to 4-bit mode

    // Configure LCD
    lcd_send_byte(0x28, 0);  // 4-bit, 2 lines, 5x8 dots
    lcd_send_byte(0x0C, 0);  // Display on, cursor off
    lcd_send_byte(0x06, 0);  // Entry mode set
    lcd_clear();
}

// Clear the LCD display
void lcd_clear() {
    lcd_send_byte(0x01, 0);  // Clear display
    sleep_ms(2);
}

// Set the cursor position
void lcd_set_cursor(uint8_t row, uint8_t col) {
    uint8_t row_offsets[] = {0x00, 0x40}; // Row addresses for 16x2 LCD
    lcd_send_byte(0x80 | (col + row_offsets[row]), 0);
}

// Write a string to the LCD
void lcd_write_string(const char *str) {
    while (*str) {
        lcd_send_byte(*str++, 1);  // Send characters
    }
}