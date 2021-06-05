/* Created and Documented by Kozova1
 */

#ifndef DC_MOTOR_h
#define DC_MOTOR_h

#include <stdbool.h>

struct motor_t {
    unsigned int pins[4];
    unsigned char queued_pins[4];
};

enum motor_dir_t {
    STOP_00 = 0,
    STOP_11 = 3,
    DIR_1 = 1,
    DIR_2 = 2
};

struct motor_t motor_create(unsigned int pwm, unsigned int en, unsigned int d0, unsigned int d1);

void motor_setup(struct motor_t* motor);

void motor_speed(struct motor_t* motor, unsigned char speed);

void motor_direction(struct motor_t* motor, enum motor_dir_t direction);

void motor_write(struct motor_t* motor);

#endif
