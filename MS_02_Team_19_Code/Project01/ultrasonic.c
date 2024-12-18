#include "pico/stdlib.h"
#include "ultrasonic.h"



void Ultrasonic_init(){
    gpio_init(ECHO);
    gpio_init(TRIGGER);

    gpio_set_dir(ECHO,GPIO_IN);
    gpio_set_dir(TRIGGER,GPIO_OUT);

}

unsigned short Ultrasonic_readDistance(){
    unsigned long long signal_off, signal_on;
    gpio_put(TRIGGER,false);
    sleep_us(2);
    gpio_put(TRIGGER,true);
    sleep_us(10);
    gpio_put(TRIGGER,false);
    while(gpio_get(ECHO)==0){
        signal_off = time_us_64(); 
    }

    while(gpio_get(ECHO)==1){
        signal_on = time_us_64(); 
    }

     unsigned long long pulse_duration = signal_on - signal_off;


    unsigned short distance = pulse_duration * 0.0343 / 2;

    return distance;
        
}