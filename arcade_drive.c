#ifndef ARCADE_DRIVE
#define ARCADE_DRIVE

#define kMaxTurn 127.0

#include "drive.c"
#include "joystick.c"

bool arcade_drive_can_pivot;

void ArcadeDriveSlowDrive(int& drive, int turn);

void ArcadeDriveUpdate() {
	int left, right;
	int speed_axis = JoystickGet(kLeftStickYAxis);
	int turn_axis = JoystickGet(kRightStickXAxis);

	// If the robot is curve turning, it can only pivot turn after the turn stick
	// has been released
	if (speed_axis != 0 && turn_axis != 0)
		arcade_drive_can_pivot = false;

	// Allow pivoting when the turn stick is released
	if (turn_axis == 0)
		arcade_drive_can_pivot = true;

	// If the speed joystick has not been moved,
	// pivot according to the turn joystick
	if (speed_axis == 0 && arcade_drive_can_pivot)
	{
  	left = turn_axis;
		right = -turn_axis;
		DriveSetLeft(left);
		DriveSetRight(right);
	}
	// If the speed joystick has been moved, curve accoring to the turn joystick
	else if (speed_axis != 0)
	{
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

void ArcadeDriveSlowDrive(int& drive, int turn)
{
	float drive_f = drive;
	float turn_f = abs(turn);

	drive_f *= 1.0 - (turn_f  / kMaxTurn);

	drive = (int) drive_f;
}

#endif
