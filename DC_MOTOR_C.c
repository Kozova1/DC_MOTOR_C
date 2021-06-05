#include "DC_MOTOR_C.h"

#include <Arduino.h>

struct motor_t motor_create(unsigned int pwm, unsigned int en, unsigned int d0, unsigned int d1) {
    return {
        .pins = { pwm, en, d0, d1 },
        .queued_pins = { 0, 0, 0, 0 }
    };
}

void motor_setup(struct motor_t* motor) {
    pinMode(motor->pins[0], OUTPUT);
    pinMode(motor->pins[1], OUTPUT);
    pinMode(motor->pins[2], OUTPUT);
    pinMode(motor->pins[3], OUTPUT);
}

void motor_speed(struct motor_t* motor, unsigned char speed) {
    motor->queued_pins[0] = speed;
}

void motor_direction(struct motor_t* motor, enum motor_dir_t direction) {
    bool d0 = direction & 0x1;
    bool d1 = direction & 0x2;
    motor->queued_pins[2] = d0;
    motor->queued_pins[3] = d1;
}

void motor_write(struct motor_t* motor) {
    analogWrite(motor->pins[0], motor->queued_pins[0]);
    digitalWrite(motor->pins[1], motor->queued_pins[1]);
    digitalWrite(motor->pins[2], motor->queued_pins[2]);
    digitalWrite(motor->pins[3], motor->queued_pins[3]);
}
