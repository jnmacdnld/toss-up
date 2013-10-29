#ifndef ARCADE_DRIVE_C
#define ARCADE_DRIVE_C

#define MAX_TURN 127.0

#include "drive.c"
#include "joystick.c"

void slowDrive(int& drive, int turn);

void updateDriveArcadeDrive() {
	int speed_axis = joystickGetYAxis(LEFT_JOYSTICK);
	int turn_axis = joystickGetXAxis(RIGHT_JOYSTICK);

	// If the speed joystick has not been moved,
	// pivot according to the turn joystick
	if (speed_axis == 0) {
		setLeftDrive(turn_axis);
		setRightDrive(-turn_axis);

	// If the speed joystick has been moved, curve accoring to the turn joystick
	} else {
		int left = speed_axis;
		int right = speed_axis;

		if (turn_axis > 0)
			slowDrive(right, turn_axis);
		else if (turn_axis < 0)
			slowDrive(left, turn_axis);

		setLeftDrive(left);
		setRightDrive(right);
	}
}

void slowDrive(int& drive, int turn) {
	float drive_f = drive;
	float turn_f = abs(turn);

	drive_f *= 1.0 - (turn_f  / MAX_TURN);

	drive = (int) drive_f;
}

#endif
