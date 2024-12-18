#include "pico/stdlib.h"
#include "ultrasonic.h"
#include "dc.h"
#include "stdio.h"
#include "lcd.h"
#include "ir_sensor.h"
#include "hardware/i2c.h"
#include "servo.h"
#include "tcs3200.h"


int map(int x, int in_min, int in_max, int out_min, int out_max);

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void roboticArm(){
    //GRIPPER YFTAH W Y2FEL
        servo_set_angle(SERVO_PIN_1, 0);
        sleep_ms(2000);

        servo_set_angle(SERVO_PIN_1, 180);



        sleep_ms(10000);
         // servo_set_angle(SERVO_PIN, 0);
              // sleep_ms(1000);
              //     servo_set_angle(SERVO_PIN_5, 740);
              //   sleep_ms(2000);
              // servo_set_angle(SERVO_PIN_4, 150);
              // //////pick
              // sleep_ms(2000);
              
            
              // servo_set_angle(SERVO_PIN_5, 500);
              //   sleep_ms(2000);
              // servo_set_angle(SERVO_PIN_4, 330);
              //   sleep_ms(1000);
              // servo_set_angle(SERVO_PIN, 700);

}
void move_servo_smoothly(uint pin, int start_angle, int end_angle, int step_delay_ms) {
    if (start_angle < end_angle) {
        for (int angle = start_angle; angle <= end_angle; angle++) {
            servo_set_angle(pin, angle);
            sleep_ms(step_delay_ms);
        }
    } else {
        for (int angle = start_angle; angle >= end_angle; angle--) {
            servo_set_angle(pin, angle);
            sleep_ms(step_delay_ms);
        }
    }
}
void initializeruby(){

 servo_set_angle(SERVO_PIN, 45);
sleep_ms(2000);
 servo_set_angle(SERVO_PIN_5, 500);
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 330);
sleep_ms(2000);
servo_set_angle(SERVO_PIN_2, 700);
sleep_ms(2000);
servo_set_angle(SERVO_PIN_1, 280);
sleep_ms(2000);

}
void pick(){
 servo_set_angle(SERVO_PIN, 45);
sleep_ms(2000);
move_servo_smoothly(SERVO_PIN_5, 500, 740, 10);  // Smoothly move 
 sleep_ms(2000);
 
servo_set_angle(SERVO_PIN_1, 40);
sleep_ms(3000);
move_servo_smoothly(SERVO_PIN_5, 740, 500, 10); 
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 330);
sleep_ms(2000);
}
void throw(){
 move_servo_smoothly(SERVO_PIN, 45, 700, 10);
  sleep_ms(2000);
servo_set_angle(SERVO_PIN_5, 550);
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 250);
 sleep_ms(2000);
  servo_set_angle(SERVO_PIN_2, 270);
sleep_ms(2000);
 servo_set_angle(SERVO_PIN_1, 280);
sleep_ms(2000);
servo_set_angle(SERVO_PIN_5, 500);
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 330);
sleep_ms(2000);
servo_set_angle(SERVO_PIN, 45);
sleep_ms(2000);

}

void left(){
 move_servo_smoothly(SERVO_PIN, 45, 400, 10);
  sleep_ms(2000);
servo_set_angle(SERVO_PIN_5, 550);
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 250);
 sleep_ms(2000);
  servo_set_angle(SERVO_PIN_2, 270);
sleep_ms(2000);
 servo_set_angle(SERVO_PIN_1, 280);
sleep_ms(2000);
servo_set_angle(SERVO_PIN_5, 500);
 sleep_ms(2000);
 servo_set_angle(SERVO_PIN_4, 330);
sleep_ms(2000);
servo_set_angle(SERVO_PIN, 45);
sleep_ms(2000);

}

int main() {
    // Initialize standard I/O, ultrasonic sensor, and DC motor
    stdio_init_all();
    servo_init(SERVO_PIN);
    servo_init(SERVO_PIN_5);
    servo_init(SERVO_PIN_4);
    servo_init(SERVO_PIN_1);
    // dc_init();

       // Read the raw sensor state
        // uint8_t sensor_state = gpio_get(IR_SENSOR_PIN);
        // printf("Raw sensor state: %d\n", sensor_state);
        
      //  //INITAL
      //   servo_set_angle(SERVO_PIN_5, 500);
      //   sleep_ms(2000);
      
      //   servo_set_angle(SERVO_PIN_4, 330);
      //   sleep_ms(2000);

      //    servo_set_angle(SERVO_PIN, 0);
      //   sleep_ms(2000);
      //   //MESEK EL HAGA
      //   servo_set_angle(SERVO_PIN_5, 740);
      //   sleep_ms(2000);
      
      //   servo_set_angle(SERVO_PIN_4, 150);
      //   sleep_ms(2000);
      initializeruby();



    Ultrasonic_init();
    dc_init();
     uint16_t speed = 170;
      // Initialize I2C on Nano RP2040
    i2c_init(I2C_PORT, 100 * 1000);  // 100 kHz I2C frequency
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

 
    lcd_init();
    lcd_set_cursor(0, 0);
    lcd_write_string("Hello, Nano RP2040!");
    lcd_set_cursor(1, 0);
    lcd_write_string("I2C LCD Connected!");


   // Initialize the TCS3200 sensor
    TCS3200_Init();
 // Variables to store color values
    uint32_t redFrequency, greenFrequency, blueFrequency;
    int redColor, greenColor, blueColor;



    while (1) {

        // Read distance from the ultrasonic sensor
        unsigned short distance = Ultrasonic_readDistance();
        printf("Distance: %d cm\n", distance);


        if (distance <= 40) {
            // Stop the car if the distance is less than or equal to 5 cm
            dc_control(speed, true);
            printf("Obstacle detected! Stopping the car.\n");
                  
              // lcd_clear();
              // lcd_write_string("Obstacle detected US!");

            if (IR_Sensor_DetectObstacle()) {
               // Run the motor at 75% speed forward if no obstacle is detected
            // lcd_clear();
            // lcd_write_string("Obstacle Reached ir");
            

      

            gpio_put(DC_DIR_PIN1, 0);
            gpio_put(DC_DIR_PIN2, 0);

            
            sleep_ms(3000);

             // Read red color frequency
  redFrequency = TCS3200_ReadColor(TCS3200_COLOR_RED);
        redColor = map(redFrequency, 25, 90, 255, 0); // Map to 0-255
  // Read green color frequency
        greenFrequency = TCS3200_ReadColor(TCS3200_COLOR_GREEN);
        greenColor = map(greenFrequency, 40, 80, 255, 0); // Map to 0-255
        // Read blue color frequency
        blueFrequency = TCS3200_ReadColor(TCS3200_COLOR_BLUE);
        blueColor = map(blueFrequency, 30, 70, 255, 0); // Map to 0-255
            if (greenColor > redColor && greenColor > blueColor) {
            printf("- GREEN detected!\n");
             lcd_clear();
            lcd_write_string(" RED detected!");
            sleep_ms(1000);
            pick();
            throw();
            
       
            }
             else if (redColor > greenColor && redColor > blueColor) {
            printf("- RED detected!\n");
            lcd_clear();
            lcd_write_string("NO RED detected!");
            sleep_ms(1000);
            pick();
            left();
        } else if (blueColor > redColor && blueColor > greenColor) {
            printf("- BLUE detected!\n");
            lcd_clear();
            lcd_write_string("NO RED detected!");
            sleep_ms(1000);
            pick();
            left();
        }

            
        sleep_ms(2000);
        // roboticArm();
            

          
        } 

        } else {
            // Continue driving the car at a moderate speed
            printf("No obstacle, moving forward.\n");
            gpio_put(DC_DIR_PIN1, 0);
            gpio_put(DC_DIR_PIN2, 0);
              // lcd_clear();
              // lcd_write_string("No Obstacle!");
        //    dc_control(speed, true);
        }

        // Delay for a short time to prevent rapid toggling
        sleep_ms(100);
        lcd_clear();
    }

    return 0;
}