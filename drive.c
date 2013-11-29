#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"

#define HIGH_SPEED_IME_TICKS_TO_INCHES 31.19

void setLeftDrive(int setting);
void setRightDrive(int setting);

void driveSetPower(int power);

void driveSetPowerUnadjusted(int power) {
  setMotor(frontLeftDrive, power);
  setMotor(backLeftDrive, power);
  setMotor(frontRightDrive, power);
  setMotor(backRightDrive, power);
}

void driveSetPower(int power) {
  setLeftDrive(power);
  setRightDrive(power);
}

void setRightDrive(int setting) {
  // setMotorAdjusted(frontRightDrive, setting);
  setMotorAdjusted(frontRightDrive, setting);
  setMotorAdjusted(backRightDrive, setting);
  setMotorAdjusted(middleRightDrive, setting);
}

void setLeftDrive(int setting) {
  // setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(backLeftDrive, setting);
  setMotorAdjusted(middleLeftDrive, setting);
}

void driveDistanceTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);

  while (sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target) {
    driveSetPower(sgn(ticks) * HALF_POWER);
  }

  driveSetPower(sgn(ticks) * -FULL_POWER);
  wait1Msec(50);
  driveSetPower(0);
}

void driveDistanceInches(int inches) {
  driveDistanceTicks(HIGH_SPEED_IME_TICKS_TO_INCHES * inches);
}

void turnToDegrees(int target) {
  while (true) {
    int error = target - GyroGetAngle();

    if ( abs(error) < 1 )
      break;

    setLeftDrive( sgn(error) * HALF_POWER);
    setRightDrive( -sgn(error) * HALF_POWER);
  }
}

#endif
