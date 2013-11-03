#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"
#include "arcade_drive.c"

int armPotVal;
int _backLeftDriveEncoder;
int _backRightDriveEncoder;

void userControlLoop() {
  while (true) {
    updateIntake();
    updateDriveArcadeDrive();
    updateArm();

    // For debugging
    armPotVal = SensorValue[armPot];
    _backLeftDriveEncoder = nMotorEncoder[backLeftDrive];
    _backRightDriveEncoder = nMotorEncoder[backRightDrive];
  }
}

#endif
