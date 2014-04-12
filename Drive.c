#ifndef DRIVE
#define DRIVE

#include "Motors.c"
#include "GyroLib.c"
#include "PidLib.c"

// #include "UserControl.c"

#define kHighSpeedImeTicksPerInch 31.19
#define kHighSpeedImeTicksPerRev 392.0

#define kNumLeftDriveMotors 3
#define kNumRightDriveMotors 3

void DriveSetLeft(int setting);
void DriveSetRight(int setting);

void DriveSetPower(int power);
void DriveMoveTicks(int ticks, float percent = 0.7);
void DriveTurnTicks(int ticks, float percent = 0.7);

void DriveSetDeltaSettingLimits(short min_delta_setting, short max_delta_setting);

bool driveMirrorTurning = false;

pidController* driveMovePid;
pidController* driveTurnToPid;

int driveGyroVal;

float DriveGetGyro();

tMotor drive_motors_left[kNumLeftDriveMotors] =
{
  backLeftDrive, middleLeftDrive, frontLeftDrive,
};

tMotor drive_motors_right[kNumRightDriveMotors] =
{
  backRightDrive, middleRightDrive, frontRightDrive
};

void DriveSetPower(int power) {
  DriveSetLeft(power);
  DriveSetRight(power);
}

void DriveSetRight(int setting) {
  for (short i = 0; i < kNumRightDriveMotors; i++)
    MotorsSetAdjusted(drive_motors_right[i], setting);
}

void DriveSetLeft(int setting) {
  for (short i = 0; i < kNumLeftDriveMotors; i++)
    MotorsSetAdjusted(drive_motors_left[i], setting);
}

void DriveInit() {
  //float drive_kp = 1.0 / (kHighSpeedImeTicksPerInch * 5.0);
  float drive_kp = 1.0;

  driveMovePid = PidControllerInit(drive_kp, 0.0, 0.0, backLeftDriveEncoder);

  driveTurnToPid = PidControllerInit(1.0, 0.0, 0.0, in1);
  driveTurnToPid->error_threshold = 50;
}

void DriveMoveTicks(int ticks, float percent) {
  writeDebugStreamLine("Call to DriveMoveTicks, distance %d", ticks);

  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);
  driveMovePid->target_value = target;

  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    int cmd = PidControllerUpdate(driveMovePid);
    DriveSetPower(cmd * percent);
    wait1Msec(25);
  }

  DriveSetPower(sgn(ticks) * -kFullPower);
  wait1Msec(30);
  DriveSetPower(0);

  // Calculate the error
  int error = nMotorEncoder[backLeftDrive] - target;

  // Print the error to the debug stream
  writeDebugStreamLine("Error: %d\n", error);
}

void DriveMoveInches(float inches) {
  int ticks = (int) (inches * kHighSpeedImeTicksPerInch);
  DriveMoveTicks(ticks);
}

/*void DriveTurnGyro(short gyro_val)
{
  // Clockwise is negative, counter-clockwise is positive
  while ( abs(driveTurnToPid->error) > 0 )
  {
    

    DriveSetLeft(-1 * power);
    DriveSetRight(power);
  }
}*/

void DriveReflectRight() {
  bMotorReflected[backRightDrive] = false;
  bMotorReflected[middleRightDrive] = false;
  bMotorReflected[frontRightDrive] = false;
}

void DriveReflectLeft() {
  bMotorReflected[backLeftDrive] = true;
  bMotorReflected[middleLeftDrive] = true;
  bMotorReflected[frontLeftDrive] = true;
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

void DriveTurnTicks(int ticks, float percent) {
  DriveReflectRight();
  DriveMoveTicks(ticks + 30, percent);
  DriveUnreflectRight();
}

void DriveSetDeltaSettingLimits(short min_delta_setting, short max_delta_setting) {
  short drive_motors[6] =
  {
    backRightDrive, middleRightDrive, frontRightDrive,
    backLeftDrive, middleLeftDrive, frontLeftDrive
  };

  for (short i = 0; i < 6; i++) {
    Motor* m = &motors[drive_motors[i]];
    m->max_delta_setting = max_delta_setting;
    m->min_delta_setting = min_delta_setting;
  }
}

#endif
