#ifndef ARCADE_DRIVE
#define ARCADE_DRIVE

#define kMaxTurn 127.0

#include "drive.c"
#include "joystick.c"

int left, right;

void ArcadeDriveSlowDrive(int& drive, int turn);

void ArcadeDriveUpdate() {
	int speed_axis = JoystickGet(kLeftStickYAxis);
	int turn_axis = JoystickGet(kRightStickXAxis);

	// If the speed joystick has not been moved,
	// pivot according to the turn joystick
	if (speed_axis == 0) {
		left = turn_axis;
		right = -turn_axis;
		DriveSetLeft(left);
		DriveSetRight(right);

	// If the speed joystick has been moved, curve accoring to the turn joystick
	} else {
		left = speed_axis;
		right = speed_axis;

		if (turn_axis > 0)
      if (speed_axis > 0)
			 ArcadeDriveSlowDrive(right, turn_axis);
      else
        ArcadeDriveSlowDrive(left, turn_axis);
		else if (turn_axis < 0)
      if (speed_axis > 0)
			 ArcadeDriveSlowDrive(left, turn_axis);
      else
        ArcadeDriveSlowDrive(right, turn_axis);

		DriveSetLeft(left);
		DriveSetRight(right);
	}
}

void ArcadeDriveSlowDrive(int& drive, int turn) {
	float drive_f = drive;
	float turn_f = abs(turn);

	drive_f *= 1.0 - (turn_f  / kMaxTurn);

	drive = (int) drive_f;
}

#endif
