#ifndef ARCADE_DRIVE_C
#define ARCADE_DRIVE_C

#define MAX_TURN 127.0

#include "drive.c"

void slowDrive(int& drive, int turn);

void updateDriveArcadeDrive() {
	int speed_axis = vexRT[Ch3];
	int turn_axis = vexRT[Ch1];

	// If the joysticks have been moved very very little, ignore it
	if ( abs(speed_axis) < 10)
		speed_axis = 0;
	
	if ( abs(turn_axis) < 10 )
		turn_axis = 0;

	// If no joysticks have been moved, do nothing
	if (speed_axis == 0 && turn_axis == 0) {
		setLeftDrive(0);
		setRightDrive(0);

	// If only the turn joystick has been moved, pivot
	} else if (speed_axis == 0 && turn_axis != 0) {
		setLeftDrive(turn_axis);
		setRightDrive(-turn_axis);

	// If only the speed joystick has been moved (no turn), move straight
	} else if (speed_axis != 0 && turn_axis == 0) {
		setLeftDrive(speed_axis);
		setRightDrive(speed_axis);

	// If the speed joystick and turn joystick have been moved,
	// slow one of the wheels to turn the robot
	} else if (speed_axis != 0 && turn_axis != 0) {
		int left = speed_axis;
		int right = speed_axis;

		if (turn_axis > 0)
			slowDrive(right, turn_axis);
		else
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
