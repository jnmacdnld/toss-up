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
int gyroValue;

task UserControl() {
  ArmControlReset();

  while (true) {
    IntakeUpdate();
    ArcadeDriveUpdate();
    ArmUpdate();

    // For debugging
    armPotVal = SensorValue[armPot];
    _backLeftDriveEncoder = nMotorEncoder[backLeftDrive];
    _backRightDriveEncoder = nMotorEncoder[backRightDrive];
    gyroValue = GyroGetAngle();

    wait1Msec(25);
  }
}

#endif
