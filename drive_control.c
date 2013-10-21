#ifndef DRIVE_CONTROL
#define DRIVE_CONTROL
 
#define ENCODER_TICKS_PER_INCH 49.94
#include "drive.c"
#include "PidLib.c"

pidController* drivePid;

task DriveControl() {
  while (true) {
    int motor_cmd = PidControllerUpdate(drivePid);
    setDrivePwr(motor_cmd);

    wait1Msec(25);
  }
}

void startDriveControl() {
  drivePid = PidControllerInit(0.0025, 0.0, 0.02, I2C_2);
  StartTask(DriveControl);
}

void driveControlMoveDistanceInches(int d) {
  int initial = nMotorEncoder[leftDrive];
  int ticks = d * ENCODER_TICKS_PER_INCH;

  drivePid->target_value = initial + ticks;
}
 
#endif /* DRIVE_CONTROL */

