#ifndef MOTOR_LUTS
#define MOTOR_LUTS

int* motorLuts[10];

// LUT that goes from 20 10 100 rpm linearly
// Computed for right drive
int backRightDriveSettingLut[128] =
{
0, 31, 31, 31, 32, 32, 32, 32, 33, 33,
34, 34, 35, 35, 36, 36, 37, 37, 37, 37,
38, 38, 38, 38, 38, 38, 39, 39, 39, 39,
39, 39, 40, 40, 40, 41, 42, 43, 43, 43,
45, 45, 45, 45, 45, 46, 46, 46, 46, 46,
50, 50, 50, 47, 49, 49, 51, 51, 51, 51,
51, 52, 52, 52, 52, 55, 54, 54, 56, 56,
56, 60, 60, 60, 57, 58, 59, 59, 61, 61,
61, 61, 64, 64, 64, 63, 65, 65, 65, 66,
66, 68, 67, 67, 73, 73, 70, 72, 71, 71,
74, 74, 74, 76, 77, 77, 78, 78, 80, 79,
79, 81, 81, 81, 81, 82, 82, 82, 83, 83,
84, 84, 84, 85, 85, 85, 85, 86
};


void InitMotorLuts() {
	// Use the back right drive LUT for now since LUTs haven't been made for the other motors
  motorLuts[frontLeftDrive] = &backRightDriveSettingLut;
  motorLuts[middleLeftDrive] = &backRightDriveSettingLut;
  motorLuts[backLeftDrive] = &backRightDriveSettingLut;

 	motorLuts[frontRightDrive] = &backRightDriveSettingLut;
  motorLuts[middleRightDrive] = &backRightDriveSettingLut;
  motorLuts[backRightDrive] = &backRightDriveSettingLut;
}

#endif /* MOTOR_LUTS */
