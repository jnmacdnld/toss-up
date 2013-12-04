#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"
#include "PidLib.c"

#define HIGH_SPEED_IME_TICKS_PER_INCH 31.19
#define HIGH_SPEED_IME_TICKS_PER_REV 392.0

#define TURN_DIAMETER 15.25
#define WHEEL_DIAMETER 4.0

#define TICKS_PER_PIVOT_DEGREE (HIGH_SPEED_IME_TICKS_PER_REV * TURN_DIAMETER) / (WHEEL_DIAMETER * 360.0)

void setLeftDrive(int setting);
void setRightDrive(int setting);

void driveSetPower(int power);

pidController* driveMovePid;
pidController* driveTurnToPid;

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

void initDrive() {
  driveMovePid = PidControllerInit(1.0, 0.0, 0.0, backLeftDriveEncoder);
  driveTurnToPid = PidControllerInit(1.0, 0.0, 0.0, in1);
  driveTurnToPid->error_threshold = 10;
}

void driveMoveTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    driveSetPower(cmd * 0.5);
  }

  driveSetPower(sgn(ticks) * -FULL_POWER);
  wait1Msec(50);
  driveSetPower(0);
}

void driveMoveInches(float inches) {
  int ticks = (int) (inches * HIGH_SPEED_IME_TICKS_PER_INCH);
  driveMoveTicks(ticks);
}

void driveTurnToDegrees(float degrees) {
  int target = (int) (degrees * 10);
  driveTurnToPid->target_value = target;

  int angle = (int) (GyroGetAngle() * 10);
  int first_error = target - angle;

  while ( sgn(first_error) * GyroGetAngle() < sgn(first_error) * target ) {
    int angle = (int) (GyroGetAngle() * 10);
    int cmd = PidControllerUpdate(driveTurnToPid, angle);

    setLeftDrive( cmd * 0.5 );
    setRightDrive( cmd * -0.5 );
  }
}

void driveTurnDegrees(float degrees) {
  degrees * TICKS_PER_PIVOT_DEGREE

  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    driveSetPower(cmd * 0.5);
  }

  // driveSetPower(sgn(ticks) * -FULL_POWER);
  // wait1Msec(50);
  driveSetPower(0);
}

void driveReflectRight() {
  int value;

  if (bMotorReflected[backRightDrive] == 0)
    value = 1;
  else
    value = 0;

  bMotorReflected[backRightDrive] = value;
  bMotorReflected[middleRightDrive] = value;
  bMotorReflected[frontRightDrive] = value;
}

#endif
