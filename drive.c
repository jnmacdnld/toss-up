#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"
#include "PidLib.c"

// #include "user_control.c"

#define HIGH_SPEED_IME_TICKS_PER_INCH 31.19
#define HIGH_SPEED_IME_TICKS_PER_REV 392.0

#define TURN_DIAMETER 15.25
#define WHEEL_DIAMETER 4.0

#define TICKS_PER_PIVOT_DEGREE (HIGH_SPEED_IME_TICKS_PER_REV * TURN_DIAMETER) / (WHEEL_DIAMETER * 360.0)
#define TICKS_PER_PIVOT_90 431
#define TICKS_PER_PIVOT_MINUS_90 -369

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
  setting = (int) ( (float) setting * 0.95);

  // setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(backLeftDrive, setting);
  setMotorAdjusted(middleLeftDrive, setting);
}

void initDrive() {
  driveMovePid = PidControllerInit(1.0, 0.0, 0.0, backLeftDriveEncoder);
  driveTurnToPid = PidControllerInit(1.0, 0.0, 0.0, in1);
  driveTurnToPid->error_threshold = 50;
}

void driveMoveTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    driveSetPower(cmd * 0.5);
   wait1Msec(25);
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
  int gyroval = 0;

  int degrees10 = (int) (degrees * 10);
  int first_error = degrees10 - SensorValue[gyro];

  //While the absolute value of the gyro is less than the desired rotation...
 while( sgn(first_error) * SensorValue[gyro] < degrees10 * sgn(first_error) )
 {
  writeDebugStreamLine("%d", SensorValue[gyro]);
  int setting = 40;
 //...continue turning
 motor[backRightDrive] = -setting;
 motor[middleRightDrive] = -setting;
 motor[frontRightDrive] = -setting;

 motor[backLeftDrive] = setting;
 motor[middleLeftDrive] = setting;
 motor[frontLeftDrive] = setting;
 }

 int setting = 0;

 motor[backRightDrive] = setting;
 motor[middleRightDrive] = setting;
 motor[frontRightDrive] = setting;

 motor[backLeftDrive] = -setting;
 motor[middleLeftDrive] = -setting;
 motor[frontLeftDrive] = -setting;
}

void driveReflectRight() {
  bMotorReflected[backRightDrive] = false;
  bMotorReflected[middleRightDrive] = false;
  bMotorReflected[frontRightDrive] = false;
}

void driveUnreflectRight() {
  bMotorReflected[backRightDrive] = true;
  bMotorReflected[middleRightDrive] = true;
  bMotorReflected[frontRightDrive] = true;
}


void driveTurnDegrees(float degrees) {
  driveReflectRight();

  int ticks = degrees * TICKS_PER_PIVOT_DEGREE;

  if (degrees == 90.0)
    ticks = TICKS_PER_PIVOT_90;
  if (degrees == -90.0)
    ticks = TICKS_PER_PIVOT_MINUS_90;

  driveMoveTicks(ticks + 30);

  driveUnreflectRight();
}


#endif
