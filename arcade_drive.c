#ifndef ARCADE_DRIVE
#define ARCADE_DRIVE

#define MAX_TURN 127.0

#include "drive.c"
#include "joystick.c"

int left, right;

void slowDrive(int& drive, int turn);

void updateDriveArcadeDrive() {
	int speed_axis = joystickGetAxis(LEFT_Y);
	int turn_axis = joystickGetAxis(RIGHT_X);

	// If the speed joystick has not been moved,
	// pivot according to the turn joystick
	if (speed_axis == 0) {
		left = turn_axis;
		right = -turn_axis;
		driveSetLeft(left);
		driveSetRight(right);

	// If the speed joystick has been moved, curve accoring to the turn joystick
	} else {
		left = speed_axis;
		right = speed_axis;

		if (turn_axis > 0)
      if (speed_axis > 0)
			 slowDrive(right, turn_axis);
      else
        slowDrive(left, turn_axis);
		else if (turn_axis < 0)
      if (speed_axis > 0)
			 slowDrive(left, turn_axis);
      else
        slowDrive(right, turn_axis);

		driveSetLeft(left);
		driveSetRight(right);
	}
}

void slowDrive(int& drive, int turn) {
	float drive_f = drive;
	float turn_f = abs(turn);

	drive_f *= 1.0 - (turn_f  / MAX_TURN);

	drive = (int) drive_f;
}

#endif
