#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "SmartMotorLib.c"

void setLeftDrive(int setting);
void setRightDrive(int setting);

void driveSetPower(int power);

void driveSetPowerUnadjusted(int power) {
  SetMotor(frontLeftDrive, power);
  SetMotor(backLeftDrive, power);
  SetMotor(frontRightDrive, power);
  SetMotor(backRightDrive, power);
}

void driveSetPower(int power) {
  setLeftDrive(power);
  setRightDrive(power);
}

void setRightDrive(int setting) {
  // setMotorAdjusted(frontRightDrive, setting);
  SetMotor(frontRightDrive, setting);
  setMotorAdjusted(backRightDrive, setting);
}

void setLeftDrive(int setting) {
  // setMotorAdjusted(frontLeftDrive, setting);
  SetMotor(frontLeftDrive, setting);
  setMotorAdjusted(backLeftDrive, setting);
}

#endif
