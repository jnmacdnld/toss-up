#ifndef MOTOR_C
#define MOTOR_C

#include "motor_luts.c"

#define FULL_POWER 127
#define FULL_PWR FULL_POWER
#define HALF_POWER FULL_POWER / 2

#define NO_MOTOR 1000

void SetMotor(tMotor _motor, int power) {
	motor[_motor] = power;
}

void setMotorAdjusted(tMotor _motor, int power) {
	if (abs(power) > FULL_POWER)
    power = FULL_POWER * sgn(power);

  SetMotor(_motor, sgn(power) * motorLuts[_motor][sgn(power) * power]);
}

/*float getEncoderTicksPerRev(tMotor _motor) {
  tSensors encoder = getEncoderForMotor(_motor);
  TSensorTypes encoder_type = SensorType[encoder];
  word motor_type = motorType[_motor];

  if (encoder_type == sensorQuadEncoder)
    return 360.0;
  else if (encoder_type == sensorQuadEncoderOnI2CPort)
    if (motor_type == tmotorVex393)
      return 627.2;
    else if (motor_type == tmotorVex393HighSpeed)
      return 392.0;

  writeDebugStream("getEncoderTicksPerRev: Invalid encoder or motor");
  return 0.0;
}*/

/*void setMotors(tMotor motors[10], int power) {
  for (int i = 0; i < 10 && motors[i] != NO_MOTOR; i++) {
    motor[motors[i]] = power;
  }
}*/

#endif /* MOTOR_H */
