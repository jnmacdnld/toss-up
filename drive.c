#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"

#define HIGH_SPEED_IME_TICKS_PER_INCH 31.19

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

void driveMoveTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);

  while (sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target) {
    driveSetPower(sgn(ticks) * HALF_POWER);
  }

  driveSetPower(sgn(ticks) * -FULL_POWER);
  wait1Msec(50);
  driveSetPower(0);
}

void driveMoveInches(float inches) {
  int ticks = (int) (inches * HIGH_SPEED_IME_TICKS_PER_INCH);
  driveDistanceTicks(ticks);
}

void driveTurnToDegrees(float degrees) {
  int target = (int) (degrees * 10);

  while (true) {
    int error = target - GyroGetAngle();

    if ( abs(error) < 10 )
      break;

    setLeftDrive( sgn(error) * HALF_POWER);
    setRightDrive( -sgn(error) * HALF_POWER);
  }
}

#endif
