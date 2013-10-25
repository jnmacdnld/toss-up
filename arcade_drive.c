#ifndef ARCADE_DRIVE_C
#define ARCADE_DRIVE_C

typedef struct {
	short sign;
	short raw;
	float mag;
	short cmd;
} DriveMotor;

void normalizeDrive(DriveMotor* left, DriveMotor* right);

void updateDriveArcadeDrive() {
	DriveMotor left;
	DriveMotor right;

	short speed_axis = (short) vexRT[Ch3];
	short turn_axis = (short) vexRT[Ch1];

	if (speed_axis < -50) {
		left.raw = speed_axis - turn_axis;
		right.raw = speed_axis + turn_axis;
	} else {
		left.raw = (short) (speed_axis + turn_axis);
		right.raw = (short) (speed_axis - turn_axis);
	}

	left.mag = (float) abs(left.raw);
	right.mag = (float) abs(right.raw);

	if (left.mag > FULL_PWR || right.mag > FULL_PWR) {
		normalizeDrive(&left, &right);
	} else {
		left.cmd = (int) left.raw;
		right.cmd = (int) right.raw
	}

	setMotorLinear(leftDrive, left.cmd);
	setMotorLinear(rightDrive, right.cmd);
}

void normalizeDrive(DriveMotor* left, DriveMotor* right) {
	left->sign = sgn(left->raw);
	right->sign = sgn(right->raw);

	DriveMotor* greater;
	DriveMotor* lesser;

	if (left->mag > right->mag) {
		greater = left;
		lesser = right;
	} else {
		greater = right;
		lesser = left;
	}

	greater->cmd = FULL_PWR * greater->sign;
	lesser->cmd = (short) ( (lesser->mag / greater->mag) * FULL_PWR * lesser->sign );
}

#endif
