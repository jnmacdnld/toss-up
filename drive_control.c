#ifndef DRIVE_CONTROL
#define DRIVE_CONTROL
 
#define ENCODER_TICKS_PER_INCH 49.94
#include "drive.c"
#include "PidLib.c"

#define PID 1
#define CONST 0

pidController* drivePid;
pidController* driveSonarPid;
pidController* driveEncoderPid;

bool driveControlEnabled = false;

bool driveControlErrorStable = false;
short driveControlErrorStableTimeout = 500;

void updatePid();

bool waiting = false;

void driveControlEnable();
void driveControlDisable();

task DriveControl() {
  while (true) {
    updatePid();

    wait1Msec(25);
  }
}

void updatePid() {
  int motor_cmd = PidControllerUpdate(drivePid);

      /* Deciding whether the error is stable */
      // If the error just became stable, start a timer
      if (drivePid->derivative == 0 && !waiting) {
        ClearTimer(T1);
        waiting = true;
      }

      if (drivePid->derivative != 0) {
        ClearTimer(T1);
        waiting = false;
      }

      // If the error has not changed for a duration of time, it is stable
      if (time1[T1] > driveControlErrorStableTimeout &&
          driveControlErrorStable == false) {
        driveControlErrorStable = true;
      }

      /* Setting the motors based on the pid controller */
      
      driveSetPowerUnadjusted(motor_cmd);
      // setDrivePwr(drivePid->drive_raw);
}

void driveControlStart() {
  driveEncoderPid = PidControllerInit(0.0025, 0.0, 0.021, I2C_2);
  driveSonarPid = PidControllerInit(.005, 0.0, 0.018, chassisSonar);

  driveSonarPid->error_threshold = 10;

  driveControlErrorStableTimeout = 250;
  driveControlErrorStable = false;

  driveControlDisable();
  StartTask(DriveControl);
}

void driveControlMoveDistanceInches(int d) {
  int initial = nMotorEncoder[leftDrive];
  int ticks = d * ENCODER_TICKS_PER_INCH;

  driveEncoderPid->target_value = initial + ticks;

  drivePid = driveEncoderPid;
  driveControlErrorStable = false;

  driveControlEnable();
}

bool driveControlMovedDistance() {
  return drivePid->error == 0;
}
 
void driveControlDisable() {
  driveControlEnabled = false;
}

void driveControlEnable() {
  driveControlEnabled = true;
}

void driveControlMoveIntoBuckyScoringPosition() {
  driveSonarPid->target_value = 160;
  drivePid = driveSonarPid;

  driveControlEnable();
}

#endif /* DRIVE_CONTROL */

