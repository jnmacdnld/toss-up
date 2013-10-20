#ifndef DRIVE_C
#define DRIVE_C

#include "motor.c"
#include "PidLib.c"
#include "arcade_drive.c"

void updateDriveTankDrive();
void setDrivePwr(int pwr);
//void driveDistanceInches(int d);

void updateDriveTankDrive() {
  setMotorLinear(leftDrive,  vexRT[Ch3]);
  setMotorLinear(rightDrive, vexRT[Ch2]);
}

void setDrivePwr(int pwr) {
  motor[leftDrive]  = pwr;
  motor[rightDrive] = pwr;
}

#endif
