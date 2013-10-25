#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"
#include "arcade_drive.c"

int armPotVal;
int leftDriveEncoder;
int rightDriveEncoder;

void userControlLoop() {
  while (true) {
    updateIntake();
    updateDriveArcadeDrive();
    updateArm();

    armPotVal = SensorValue[armPot];                // For debugging
    leftDriveEncoder = nMotorEncoder[leftDrive];    //
    rightDriveEncoder = nMotorEncoder[rightDrive];  //
  }
}

#endif
