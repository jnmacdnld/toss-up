#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"
#include "arcade_drive.c"
#include "GyroLib.c"

int armPotVal;
int _backLeftDriveEncoder;
int _backRightDriveEncoder;
int gyroValue;

task userControl() {
  armControlReset();

  while (true) {
    updateIntake();
    updateDriveArcadeDrive();
    armUpdate();

    // For debugging
    armPotVal = SensorValue[armPot];
    _backLeftDriveEncoder = nMotorEncoder[backLeftDrive];
    _backRightDriveEncoder = nMotorEncoder[backRightDrive];
    gyroValue = driveGetGyro();

    wait1Msec(25);
  }
}

#endif
