#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 
16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 
18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 
21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 
24, 24, 24, 24, 24, 25, 25, 25, 26, 26, 
26, 27, 27, 27, 27, 28, 28, 28, 29, 29, 
30, 30, 30, 31, 31, 31, 31, 32, 32, 33, 
34, 34, 35, 35, 35, 35, 36, 36, 37, 37, 
38, 38, 39, 39, 40, 41, 41, 42, 42, 43, 
43, 45, 45, 46, 46, 46, 47, 47, 48, 50, 
50, 51, 52, 52, 53, 55, 56, 57, 59, 60, 
61, 63, 64, 66, 68, 68, 70, 72, 74, 76, 
81, 82, 84, 89, 122, 126, 126, 126 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 13, 13, 13, 13, 
13, 13, 13, 13, 15, 15, 15, 15, 16, 16, 
16, 16, 16, 16, 18, 18, 18, 17, 17, 17, 
17, 19, 19, 19, 19, 20, 20, 20, 20, 21, 
21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 
23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 
27, 27, 27, 28, 28, 28, 29, 29, 30, 30, 
30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 
35, 36, 36, 36, 37, 37, 38, 39, 39, 40, 
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 
51, 52, 53, 54, 55, 58, 59, 60, 63, 64, 
67, 70, 72, 74, 77, 77, 79, 80, 81, 82, 
82, 83, 84, 84, 85, 85, 86, 90 
};

short leftDriveBackwardSettingLut[128] =
{
	0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 
16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 
18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 
21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 
24, 24, 24, 24, 24, 25, 25, 25, 26, 26, 
26, 27, 27, 27, 27, 28, 28, 28, 29, 29, 
30, 30, 30, 31, 31, 31, 31, 32, 32, 33, 
34, 34, 35, 35, 35, 35, 36, 36, 37, 37, 
38, 38, 39, 39, 40, 41, 41, 42, 42, 43, 
43, 45, 45, 46, 46, 46, 47, 47, 48, 50, 
50, 51, 52, 52, 53, 55, 56, 57, 59, 60, 
61, 63, 64, 66, 68, 68, 70, 72, 74, 76, 
81, 82, 84, 89, 122, 126, 126, 126 
};

short rightDriveBackwardSettingLut[128] =
{
	0, 0, 0, 0, 0, 0, 13, 13, 13, 13, 
13, 13, 13, 13, 15, 15, 15, 15, 16, 16, 
16, 16, 16, 16, 18, 18, 18, 17, 17, 17, 
17, 19, 19, 19, 19, 20, 20, 20, 20, 21, 
21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 
23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 
27, 27, 27, 28, 28, 28, 29, 29, 30, 30, 
30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 
35, 36, 36, 36, 37, 37, 38, 39, 39, 40, 
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 
51, 52, 53, 54, 55, 58, 59, 60, 63, 64, 
67, 70, 72, 74, 77, 77, 79, 80, 81, 82, 
82, 83, 84, 84, 85, 85, 86, 90 
};

void MotorLutsInit() {
  motorLutsForward[frontLeftDrive] = &leftDriveForwardSettingLut;
  motorLutsForward[middleLeftDrive] = &leftDriveForwardSettingLut;
  motorLutsForward[backLeftDrive] = &leftDriveForwardSettingLut;

 	motorLutsForward[frontRightDrive] = &rightDriveForwardSettingLut;
  motorLutsForward[middleRightDrive] = &rightDriveForwardSettingLut;
  motorLutsForward[backRightDrive] = &rightDriveForwardSettingLut;

  motorLutsBackward[frontLeftDrive] = &leftDriveBackwardSettingLut;
  motorLutsBackward[middleLeftDrive] = &leftDriveBackwardSettingLut;
  motorLutsBackward[backLeftDrive] = &leftDriveBackwardSettingLut;

 	motorLutsBackward[frontRightDrive] = &rightDriveBackwardSettingLut;
  motorLutsBackward[middleRightDrive] = &rightDriveBackwardSettingLut;
  motorLutsBackward[backRightDrive] = &rightDriveBackwardSettingLut;
}

#endif /* MOTOR_LUTS */
