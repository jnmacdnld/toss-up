#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"
#include "arcade_drive.c"
#include "GyroLib.c"
#include "tank_drive.c"

int armPotVal;
int _backLeftDriveEncoder;
int _backRightDriveEncoder;
float gyroValue;
int gyroValueRaw;
int sonarValue;
int leftFrontLineValue;

bool seeLine;
int lineNumber;

task UserControl() {
  ArmControlReset();
          
  while (true) {
    IntakeUpdate();
    ArcadeDriveUpdate();
    ArmUpdate();

    /*// Prevent tipping
    if ( armPos > (kArmUpPos - 300) )
      DriveSetDeltaSettingLimits(-256, 30);
    else
      DriveSetDeltaSettingLimits(-256, 256);*/

    // For debugging
    armPotVal = SensorValue[armPot];
    _backLeftDriveEncoder = nMotorEncoder[backLeftDrive];
    _backRightDriveEncoder = nMotorEncoder[backRightDrive];
    gyroValue = GyroGetAngle();
    gyroValueRaw = SensorValue[gyro];
    sonarValue = SensorValue[stashSonar];
    leftFrontLineValue = SensorValue[leftFrontLine];

    seeLine = SensorValue[leftFrontLine] < 2300;

    if (seeLine)
      lineNumber++;

    wait1Msec(10);
  }
}

#endif
