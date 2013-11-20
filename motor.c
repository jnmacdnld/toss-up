#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

#define FULL_POWER 127
#define FULL_PWR FULL_POWER
#define HALF_POWER FULL_POWER / 2

#define DEFAULT_ACCEL_LIMIT 10

typedef struct {
  int setting;
  int request;
  int accel_limit;
} Motor;

Motor motors[10];

void setMotor(tMotor port, int power) {
	motors[port].request = power;
}

void initMotors() {
  for (int i = 0; i < 10; i++) {
    Motor* m = &motors[i];

    m->setting = 0;
    m->request = 0;
    m->accel_limit = DEFAULT_ACCEL_LIMIT;
  }
}

task updateMotors() {
  while (true) {
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      // Enforce acceleration limit
      if ( abs(m->setting - m->request) > m->accel_limit )
        m->setting += m->accel_limit * sgn(m->request);
      else
        m->setting = m->request;

      motor[i] = m->setting;
    }

    wait1Msec(25);
  }
}

void setMotorAdjusted(tMotor _motor, int power) {
	if (abs(power) > FULL_POWER)
    power = FULL_POWER * sgn(power);

  setMotor(_motor, sgn(power) * motorLuts[_motor][sgn(power) * power]);
}

#endif /* MOTOR_H */
