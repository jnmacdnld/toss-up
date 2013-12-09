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

void driveSetLeft(int setting);
void driveSetRight(int setting);

void driveSetPower(int power);

bool driveMirrorTurning = false;

pidController* driveMovePid;
pidController* driveTurnToPid;

float driveGetGyro();

void driveSetPowerUnadjusted(int power) {
  setMotor(frontLeftDrive, power);
  setMotor(backLeftDrive, power);
  setMotor(frontRightDrive, power);
  setMotor(backRightDrive, power);
}

void driveSetPower(int power) {
  driveSetLeft(power);
  driveSetRight(power);
}

void driveSetRight(int setting) {
  // setMotorAdjusted(frontRightDrive, setting);
  setMotorAdjusted(frontRightDrive, setting);
  setMotorAdjusted(backRightDrive, setting);
  setMotorAdjusted(middleRightDrive, setting);
}

void driveSetLeft(int setting) {
  // setting = (int) ( (float) setting * 0.95);

  // setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(frontLeftDrive, setting);
  setMotorAdjusted(backLeftDrive, setting);
  setMotorAdjusted(middleLeftDrive, setting);
}

void initDrive() {
  float drive_kp = 1.0 / (HIGH_SPEED_IME_TICKS_PER_INCH * 5.0);

  driveMovePid = PidControllerInit(drive_kp, 0.0, 0.0, backLeftDriveEncoder);

  driveTurnToPid = PidControllerInit(1.0, 0.0, 0.0, in1);
  driveTurnToPid->error_threshold = 50;
}

void driveMoveTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    driveSetPower(cmd * 0.7);
    wait1Msec(25);
  }

  driveSetPower(0);
}

void driveMoveInches(float inches) {
  int ticks = (int) (inches * HIGH_SPEED_IME_TICKS_PER_INCH);
  driveMoveTicks(ticks);
}

void driveTurnToDegrees(float degrees) {
  if (driveMirrorTurning)
    degrees *= -1;

  int sgn_first_error = sgn( degrees - driveGetGyro() );

  while( sgn_first_error * driveGetGyro() < degrees * sgn_first_error ) {
    writeDebugStreamLine("%f", driveGetGyro() );

    driveSetLeft(FULL_POWER * .5 * sgn_first_error);
    driveSetRight(-FULL_POWER * .5 * sgn_first_error);
  }

 driveSetPower(0);
}

float driveGetGyro() {
  return ( (float) -SensorValue[gyro] ) / 10.0;
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

void initGyro() {
  //Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[gyro] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[gyro] = sensorGyro;
 wait1Msec(2000);
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
