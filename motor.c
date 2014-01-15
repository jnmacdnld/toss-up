#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

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

void MotorSet(tMotor port, int power) {
	motors[port].request = power;
}

void MotorInitMotors() {
  short drive_motors[6] =
  {
    backRightDrive, middleRightDrive, frontRightDrive,
    backLeftDrive, middleLeftDrive, frontLeftDrive
  };

  // Initialize the motor data structure
  for (int i = 0; i < 10; i++) {
    Motor* m = &motors[i];

    m->setting = 0;
    m->request = 0;
    m->max_delta_setting = kDefaultAccelLimit;
    m->min_delta_setting = -kDefaultAccelLimit;
  }


}

task UpdateMotors() {
  while (true) {
    // Update each motor
    for (int i = 0; i < 10; i++) {
      Motor* m = &motors[i];

      short delta_setting = m->request - m->setting;

      // Enforce acceleration limit
      if ( delta_setting > max_delta_setting )
        m->setting += max_delta_setting
      else if ( delta_setting < min_delta_setting )
        m->setting -= min_delta_setting
      else
        m->setting = m->request;

      // Finally, set the motor
      motor[i] = m->setting;
    }

    wait1Msec(25);
  }
}

void MotorSetAdjusted(tMotor _motor, int power) {
	if (abs(power) > kFullPower)
    power = kFullPower * sgn(power);

  MotorSet(_motor, sgn(power) * motorLuts[_motor][sgn(power) * power]);
}

#endif /* MOTOR_H */
