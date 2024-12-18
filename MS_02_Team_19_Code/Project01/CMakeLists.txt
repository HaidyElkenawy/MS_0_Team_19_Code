cmake_minimum_required(VERSION 3.28)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Set the project name
set(projname "main")

project(${projname} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add the source files for the project
add_executable(${projname}
    "main.c"
    "ultrasonic.c"
    "servo.c"
    "led.c"
    "dc.c"
    "lcd.c"
    "tcs3200.c"
    "ir_sensor.c"
)

# Enable the USB Virtual COM Port (for printf debugging)
pico_enable_stdio_usb(${projname} 1)
pico_enable_stdio_uart(${projname} 0)

# Link necessary libraries
target_link_libraries(${projname}
    pico_stdlib          # Standard Pico library
    hardware_spi         # SPI library (if needed)
    hardware_i2c         # I2C library (if needed)
    hardware_pwm         # PWM library for servo motor
    pico_binary_info     # Binary info library
)

# Generate output files (UF2, ELF, etc.)
pico_add_extra_outputs(${projname})
