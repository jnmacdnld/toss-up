#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

#define kFullPower 127
#define kFullPower kFullPower
#define kHalfPower kFullPower / 2

#define kDefaultAccelLimit 256

typedef struct {
  int setting;
  int request;
  int accel_limit;
} Motor;

Motor motors[10];

void SetMotor(tMotor port, int power) {
	motors[port].request = power;
}

void InitMotors() {
  for (int i = 0; i < 10; i++) {
    Motor* m = &motors[i];

    m->setting = 0;
    m->request = 0;
    m->accel_limit = kDefaultAccelLimit;
  }
}

task UpdateMotors() {
  while (true) {
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      // Enforce acceleration limit
      if ( abs(m->request - m->setting) > m->accel_limit )
        m->setting += m->accel_limit * sgn(m->request - m->setting);
      else
        m->setting = m->request;

      motor[i] = m->setting;
    }

    wait1Msec(25);
  }
}

void SetMotorAdjusted(tMotor _motor, int power) {
	if (abs(power) > kFullPower)
    power = kFullPower * sgn(power);

  SetMotor(_motor, sgn(power) * motorLuts[_motor][sgn(power) * power]);
}

#endif /* MOTOR_H */
