#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

#define FULL_POWER 127
#define FULL_PWR FULL_POWER
#define HALF_POWER FULL_POWER / 2

#define NO_MOTOR 1000

void setMotor(tMotor _motor, int power) {
	motor[_motor] = power;
}

void setMotorAdjusted(tMotor _motor, int power) {
	if (abs(power) > FULL_POWER)
    power = FULL_POWER * sgn(power);

  setMotor(_motor, sgn(power) * motorLuts[_motor][sgn(power) * power]);
}

#endif /* MOTOR_H */
