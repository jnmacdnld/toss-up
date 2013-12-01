#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"
#include "PidLib.c"

#define HIGH_SPEED_IME_TICKS_PER_INCH 31.19

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

  int first_error = target - GyroGetAngle();

  while ( sgn(first_error) * GyroGetAngle() < sgn(first_error) * target ) {
    int gyro_value = GyroGetAngle();
    int cmd = PidControllerUpdate(driveTurnToPid, gyro_value);

    setLeftDrive( cmd * 0.5 );
    setRightDrive( cmd * 0.5 );
  }
}

#endif
