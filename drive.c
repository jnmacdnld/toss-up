#ifndef DRIVE
#define DRIVE

#include "motor.c"

void setLeftDrive(int setting);
void setRightDrive(int setting);

void driveSetPower(int power);

void driveSetPowerUnadjusted(int power) {
  motor[frontLeftDrive] = power;
  motor[backLeftDrive] = power;
  motor[frontRightDrive] = power;
  motor[backRightDrive] = power;
}

void driveSetPower(int power) {
  setLeftDrive(power);
  setRightDrive(power);
}

void setRightDrive(int setting) {
  // setMotorAdjusted(frontRightDrive, setting);
  motor[frontRightDrive] = setting;
  setMotorAdjusted(backRightDrive, setting);
}

void setLeftDrive(int setting) {
  // setMotorAdjusted(frontLeftDrive, setting);
  motor[frontLeftDrive] = setting;
  setMotorAdjusted(backLeftDrive, setting);
}

#endif
