/* Created and Documented by Kozova1
 */

#ifndef DC_MOTOR_h
#define DC_MOTOR_h

#include <Arduino.h>

/*
 * Creating a motor -> storing its pins in the table
 * PWM pin, EN pin, D0 pin, D1 pin.
 * PWM pin has to be connected to a PWM capable port
 * Valid Values: 
 * PWM: pin number
 * EN: pin number
 * D0 and D1: pin numbers
 */
int create_motor (unsigned int pwm, unsigned int en, unsigned int d0, unsigned int d1);

/*
 * Required to run after creating the motor
 * this sets correct modes for all the pins of the motor
 * index: number of the motor to set up (Numbers start at zero)
 * Valid Values: 
 * index >= 0
 */
int setup_motor (unsigned int index);

/* Set speed of the motor
 * Valid Values
 * speed: 0-255, index >= 0
 */
int set_motor_speed (unsigned int speed, unsigned int index);

/* Set direction of the motor
 * index: number of motor
 * D0, D1 -> control pins.
 * D0           D1         result
 * * * * * * * * * * * * * * * * * *
 * false        false      STOP
 * false        true       DIRECTION 1
 * true         false      DIRECTION 2
 * true         true       STOP
 * * * * * * * * * * * * * * * * * */
int set_motor_direction (bool D0, bool D1, unsigned int index);

/* Send all settings to the motor
 * index: number of motor
 * index >= 0
 */
int submit_motor (unsigned int index);
struct motors {
    static unsigned int motor_pins[][8];
    static unsigned int free_motor_space;
};

bool check_motor (unsigned int index);

int delete_motor (unsigned int index);

int _clamp (int x, int upper, int lower);
#endif
