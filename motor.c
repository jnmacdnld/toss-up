#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

#define FULL_POWER 127
#define FULL_PWR FULL_POWER
#define HALF_POWER FULL_POWER / 2

#define DEFAULT_MAX_SETTING_CHANGE 10

typedef struct {
  int setting;
  int request;
  int max_setting_change;
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
    m->max_setting_change = DEFAULT_MAX_SETTING_CHANGE;
  }
}

task updateMotors() {
  while (true) {
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      if ( abs(m->setting - m->request) > m->max_setting_change )
        m->setting += m->max_setting_change * sgn(m->request);
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
