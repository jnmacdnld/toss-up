#ifndef DRIVE_CONTROLLER
#define DRIVE_CONTROLLER

#include "Drive.c"

#define kDriveKp 0.0
#define kDriveKi 0.0
#define kDriveKd 0.0
#define kDriveKbias 0.0

typedef struct {
  pidController* pid;
  bool enabled
} DriveController;

DriveController drive_controller;

void DriveControllerMoveTicks(int ticks) {
  // Print to the console for debugging
  writeDebugStreamLine("Call to DriveMoveTicks");

  // Set the target encoder value
  int target = nMotorEncoder[backLeftDrive] + (ticks - 30);

  // Set the PID controller target
  driveMovePid->target_value = target;

  // Keep moving until the target is reached
  while ( sgn(ticks) * nMotorEncoder[backLeftDrive] < sgn(ticks) * target ) {
    // Update the PID controller and store the returned power value
    int power = PidControllerUpdate(driveMovePid);

    // Move slowly so the robot doesn't mess up
    DriveSetPower(power * 0.7);
  }

  // Brake
  DriveSetPower(sgn(ticks) * -kFullPower);
  wait1Msec(30);
  DriveSetPower(0);
}

void DriveControllerMoveInches(float inches) {
  // Convert encoder ticks to inches
  int ticks = (int) (inches * kHighSpeedImeTicksPerInch);

  DriveControllerMoveTicks(ticks);
}

void DriveControllerTurnToDegrees(float degrees) {
  if (driveMirrorTurning)
    degrees *= -1;

  int sgn_first_error = sgn( degrees - GyroGetAngle() );

  while ( sgn_first_error * GyroGetAngle() < degrees * sgn_first_error )
  {
    DriveSetLeft(kFullPower * 0.7 * sgn_first_error);
    DriveSetRight(-kFullPower * 0.7 * sgn_first_error);
  }
}

#endif
