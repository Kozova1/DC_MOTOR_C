#include <DC_MOTOR_C.h>

static struct motors _motors_list;

int create_motor (unsigned int pwm, unsigned int en, unsigned int d0, unsigned int d1) {
    int _firstfreespace = 0;
    _motors_list.free_motor_space = 0;
    while (_firstfreespace <= _motors_list.free_motor_space) {
        if (check_motor (_firstfreespace)) {
            break;
        }
        _firstfreespace++;
    }

    int _temp[8] = {pwm, en, d0, d1, 0, 0, 0, 1};
    for (int i=0; i < 8; i++) {
        _motors_list.motor_pins[_firstfreespace][i] = _temp[i];
    _motors_list.free_motor_space++;
    }
}

int setup_motor (unsigned int index) {
    if (check_motor (index) == false) {
        pinMode (_motors_list.motor_pins[index][0], OUTPUT);
        pinMode (_motors_list.motor_pins[index][1], OUTPUT);
        pinMode (_motors_list.motor_pins[index][2], OUTPUT);
        pinMode (_motors_list.motor_pins[index][3], OUTPUT);

        return 0;
    } else {
        return 1;
    }
}
int delete_motor (unsigned int index) {
    for (int i=0; i<8; i++) {
        _motors_list.motor_pins[index][i] = 0;
    }
}

int set_motor_speed (unsigned int speed, unsigned int index) {
    unsigned int spd = _clamp (speed, 255.0, 0.0);
    if (check_motor(index) == false) {
        _motors_list.motor_pins[index][0] = speed;
        return 0;
    } else {
        return 1;
    }
}

int _clamp (int x, int upper, int lower) {
    return min (upper, max (x, lower));
}

int set_motor_direction (bool D0, bool D1, unsigned int index) {
    if (check_motor(index) == false) {
        _motors_list.motor_pins[index][6] = D0 == true ? HIGH : LOW;
        _motors_list.motor_pins[index][7] = D1 == true ? HIGH : LOW;
        return 0;
    } else {
        return 1;
    }
}

int submit_motor (unsigned int index) {
    if (check_motor(index) == false) {
        analogWrite (_motors_list.motor_pins[index][0], _motors_list.motor_pins[index][4]);
        digitalWrite (_motors_list.motor_pins[index][1], HIGH);
        digitalWrite (_motors_list.motor_pins[index][2], _motors_list.motor_pins[index][5]);
        digitalWrite (_motors_list.motor_pins[index][3], _motors_list.motor_pins[index][6]);
        return 0;
    } else {
        return 1;
    }
}

bool check_motor(unsigned int index) {
    if (_motors_list.motor_pins[index][7] != 0) {
        return false;
    } else {
        return true;
    }
}
