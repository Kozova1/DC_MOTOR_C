#include "DC_MOTOR_C.h"

#include <Arduino.h>

#define MAX_INDEX 64 // I don't know how big this can be

struct motors {
    unsigned int motor_pins[MAX_INDEX][8];
    unsigned int free_motor_space;
};

static struct motors MOTORS;

int create_motor (
        unsigned int pwm,
        unsigned int en,
        unsigned int d0,
        unsigned int d1
        ) {
    /* Here we assign the motor pins to their corresponding places.
     * Each row in the table stores a motor group.
     * A motor group is all the data required for a motor to function.
     * We have a free space "pointer" that points to the first free space.
     * This is a terrible way to do it.
     */
            unsigned int _firstfreespace = 0;
            MOTORS.free_motor_space= 0;

            while (_firstfreespace <= MOTORS.free_motor_space) {
                if (check_motor (_firstfreespace)) {
                    break;
                }
                _firstfreespace++;
            }

            int temp[8];
            temp[0] = pwm;
            temp[1] = en;
            temp[2] = d0;
            temp[3] = d1;
            temp[4] = 0;
            temp[5] = 0;
            temp[6] = 0;
            temp[7] = 1;
            int _1i;
            for (_1i=0; _1i < 8; _1i++) {
                MOTORS.motor_pins[_firstfreespace][_1i] = temp[_1i];
                MOTORS.free_motor_space++;
            }
}

int setup_motor (unsigned int index) {
    /* Here we set the modes of the pins.
     * It's important to note that the PWM pin has to be connected to
     * a PWM compatible pin.
     */
    if (check_motor (index) == false) {
        pinMode (MOTORS.motor_pins[index][0], OUTPUT);
        pinMode (MOTORS.motor_pins[index][1], OUTPUT);
        pinMode (MOTORS.motor_pins[index][2], OUTPUT);
        pinMode (MOTORS.motor_pins[index][3], OUTPUT);

        return 0;
    } else {
        return 1;
    }
}
int delete_motor (unsigned int index) {
    /* Here we free the space of the motor by overwriting it with zeros.
     * This works because we have a cell that is used for determining
     * whether the motor is used or free. If we overwrite it the motor
     * counts as unused or free.
     */
    int _i;
    for (_i=0; _i<8; _i++) {
        MOTORS.motor_pins[index][_i] = 0;
    }
}

static int clamp(int x, int upper, int lower) {
    /* Clamp arg to limits
     */
    return min (upper, max (x, lower));
}

int set_motor_speed (unsigned int speed, unsigned int index) {
    unsigned int spd = clamp (speed, 255.0, 0.0);
    if (check_motor(index) == false) {
        MOTORS.motor_pins[index][0] = spd;
        return 0;
    } else {
        return 1;
    }
}

int set_motor_direction(bool D0, bool D1, unsigned int index) {
    if (check_motor(index) == false) {
        MOTORS.motor_pins[index][6] = D0 == true ? HIGH : LOW;
        MOTORS.motor_pins[index][7] = D1 == true ? HIGH : LOW;
        return 0;
    } else {
        return 1;
    }
}

int submit_motor(unsigned int index) {
    if (check_motor(index) == false) {
        analogWrite (
                MOTORS.motor_pins[index][0],
                MOTORS.motor_pins[index][4]
        );

        digitalWrite (MOTORS.motor_pins[index][1], HIGH);

        digitalWrite (
                MOTORS.motor_pins[index][2],
                MOTORS.motor_pins[index][5]
        );

        digitalWrite (
                MOTORS.motor_pins[index][3],
                MOTORS.motor_pins[index][6]
        );

        return 0;
    } else {
        return 1;
    }
}

bool check_motor(unsigned int index) {
	return MOTORS.motor_pins[index][7] == 0;
}
