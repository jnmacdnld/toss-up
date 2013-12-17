#ifndef DRIVE
#define DRIVE

#include "motor.c"
#include "GyroLib.c"
#include "PidLib.c"

// #include "user_control.c"

#define kHighSpeedImeTicksPerInch 31.19
#define kHighSpeedImeTicksPerRev 392.0

void DriveSetLeft(int setting);
void DriveSetRight(int setting);

void DriveSetPower(int power);
void DriveMoveTicks(int ticks);

bool driveMirrorTurning = false;

pidController* driveMovePid;
pidController* driveTurnToPid;

int driveGyroVal;

float DriveGetGyro();

void DriveSetPowerUnadjusted(int power) {
  MotorSet(frontLeftDrive, power);
  MotorSet(backLeftDrive, power);
  MotorSet(frontRightDrive, power);
  MotorSet(backRightDrive, power);
}

void DriveSetPower(int power) {
  DriveSetLeft(power);
  DriveSetRight(power);
}

void DriveSetRight(int setting) {
  MotorSetAdjusted(frontRightDrive, setting);
  MotorSetAdjusted(backRightDrive, setting);
  MotorSetAdjusted(middleRightDrive, setting);
}

void DriveSetLeft(int setting) {
  MotorSetAdjusted(frontLeftDrive, setting);
  MotorSetAdjusted(backLeftDrive, setting);
  MotorSetAdjusted(middleLeftDrive, setting);
}

void DriveInit() {
  //float drive_kp = 1.0 / (kHighSpeedImeTicksPerInch * 5.0);
  float drive_kp = 1.0;

  driveMovePid = PidControllerInit(drive_kp, 0.0, 0.0, backLeftDriveEncoder);

  driveTurnToPid = PidControllerInit(1.0, 0.0, 0.0, in1);
  driveTurnToPid->error_threshold = 50;
}

void DriveMoveTicks(int ticks) {
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    DriveSetPower(cmd * 0.5);
    wait1Msec(25);
  }

  DriveSetPower(sgn(ticks) * -kFullPower);
  wait1Msec(30);
  DriveSetPower(0);
}

void DriveMoveInches(float inches) {
  int ticks = (int) (inches * kHighSpeedImeTicksPerInch);
  DriveMoveTicks(ticks);
}

void DriveTurnToDegrees(float degrees) {
  if (driveMirrorTurning)
    degrees *= -1;

  int sgn_first_error = sgn( degrees - GyroGetAngle() );

  while ( sgn_first_error * GyroGetAngle() < degrees * sgn_first_error ) {
    driveGyroVal = GyroGetAngle();

    DriveSetLeft(kFullPower * .5 * sgn_first_error);
    DriveSetRight(-kFullPower * .5 * sgn_first_error);
  }
}

void DriveReflectRight() {
  bMotorReflected[backRightDrive] = false;
  bMotorReflected[middleRightDrive] = false;
  bMotorReflected[frontRightDrive] = false;
}

void DriveUnreflectRight() {
  bMotorReflected[backRightDrive] = true;
  bMotorReflected[middleRightDrive] = true;
  bMotorReflected[frontRightDrive] = true;
}

float DriveGetGyro() {
  return ( (float) -SensorValue[gyro] ) / 10.0;
}

void DriveInitGyro() {
  //Completely clear out any previous sensor readings by setting the port to "sensorNone"
 SensorType[gyro] = sensorNone;
 wait1Msec(1000);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[gyro] = sensorGyro;
 wait1Msec(2000);
}

void DriveTurnTicks(int ticks) {
  DriveReflectRight();
  DriveMoveTicks(ticks + 30);
  DriveUnreflectRight();
}

#endif
