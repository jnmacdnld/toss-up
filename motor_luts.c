#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 18, 18, 
18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 
19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 
22, 22, 22, 22, 23, 23, 23, 23, 24, 24, 
24, 25, 25, 25, 26, 26, 26, 26, 27, 27, 
27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 
30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 
34, 34, 35, 35, 36, 36, 37, 37, 37, 38, 
39, 39, 40, 40, 40, 41, 42, 42, 43, 44, 
44, 45, 46, 47, 47, 48, 48, 49, 50, 52, 
52, 53, 54, 54, 56, 57, 60, 61, 62, 65, 
66, 69, 70, 71, 71, 72, 73, 75, 76, 79, 
79, 82, 84, 85, 85, 87, 97, 98 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 
18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 
19, 20, 20, 20, 21, 21, 21, 21, 21, 22, 
22, 22, 22, 23, 23, 23, 24, 24, 24, 24, 
25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 
28, 28, 29, 29, 29, 29, 29, 30, 30, 30, 
31, 31, 32, 32, 32, 33, 33, 34, 34, 35, 
35, 35, 36, 36, 36, 37, 37, 38, 38, 39, 
39, 39, 40, 40, 40, 42, 42, 43, 43, 44, 
44, 45, 46, 47, 48, 49, 49, 50, 50, 51, 
51, 53, 55, 55, 56, 58, 60, 61, 63, 65, 
66, 68, 72, 74, 75, 77, 79, 80, 80, 81, 
82, 82, 83, 83, 84, 84, 84, 85 
};

short leftDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 16, 16, 16, 16, 16, 
16, 16, 16, 16, 18, 18, 18, 18, 18, 18, 
19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 
21, 22, 22, 22, 22, 23, 23, 23, 23, 23, 
24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 
26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 
30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 
34, 34, 34, 35, 35, 36, 36, 37, 37, 38, 
38, 39, 39, 40, 40, 41, 41, 42, 43, 43, 
44, 45, 46, 46, 47, 47, 48, 49, 50, 52, 
52, 53, 55, 56, 57, 59, 60, 60, 61, 61, 
65, 66, 68, 68, 71, 73, 74, 79, 82, 83, 
84, 84, 114, 114, 86, 89, 122, 127 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 19, 19, 
19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 
21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 
23, 23, 23, 23, 23, 23, 23, 26, 26, 26, 
26, 25, 25, 27, 27, 27, 27, 27, 27, 28, 
28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 
31, 31, 32, 32, 33, 33, 33, 33, 34, 34, 
37, 37, 35, 35, 36, 36, 38, 38, 38, 38, 
39, 39, 39, 40, 41, 41, 41, 42, 43, 43, 
44, 45, 45, 46, 46, 47, 48, 49, 50, 50, 
50, 51, 52, 53, 54, 55, 56, 56, 58, 60, 
64, 63, 66, 67, 69, 70, 72, 73, 75, 76, 
78, 79, 80, 80, 81, 82, 83, 83 
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
