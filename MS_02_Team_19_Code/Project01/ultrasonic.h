#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



#define TRIGGER 4    
#define ECHO  7 

void Ultrasonic_init(void);


unsigned short Ultrasonic_readDistance(void);



#endif