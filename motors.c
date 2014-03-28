#ifndef MOTOR_C
#define MOTOR_C

#include "MotorLuts.c"

#define kFullPower 127
#define kHalfPower kFullPower / 2

#define kDefaultAccelLimit 256

typedef struct {
  short setting;
  short request;
  short min_delta_setting;
  short max_delta_setting;
} Motor;

Motor motors[10];

void MotorsSet(tMotor port, int power) {
	motors[port].request = power;
}

void MotorsInit() {
  // Initialize the motor data structure
  for (int i = 0; i < 10; i++) {
    Motor* m = &motors[i];

    m->setting = 0;
    m->request = 0;
    m->max_delta_setting = kDefaultAccelLimit;
    m->min_delta_setting = -kDefaultAccelLimit;
  }

}

task MotorsUpdate() {
  while (true) {
    // Update each motor
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      short delta_setting = m->request - m->setting;

      // Enforce acceleration limit
      if ( delta_setting > m->max_delta_setting )
        m->setting += m->max_delta_setting;
      else if ( delta_setting < m->min_delta_setting )
        m->setting += m->min_delta_setting;
      else
        m->setting = m->request;

      // Finally, set the motor
      motor[i] = m->setting;
    }

    wait1Msec(25);
  }
}

void MotorsSetAdjusted(tMotor _motor, int power) {
	if (abs(power) > kFullPower)
    power = kFullPower * sgn(power);

  if (power > 0)
    MotorsSet(_motor, motorLutsForward[_motor][power]);
  else
    MotorsSet(_motor, -motorLutsBackward[_motor][abs(power)]);
}

#endif /* MOTOR_H */
