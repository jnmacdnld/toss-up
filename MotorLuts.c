#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 14, 14, 14, 17, 17, 17, 17, 
17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 
18, 18, 18, 20, 20, 20, 20, 20, 20, 21, 
21, 21, 21, 21, 22, 22, 22, 23, 23, 23, 
24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 
26, 26, 27, 27, 27, 27, 28, 28, 29, 29, 
30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 
33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 
38, 39, 39, 40, 40, 41, 42, 42, 43, 43, 
44, 45, 46, 47, 48, 48, 49, 50, 51, 52, 
53, 53, 54, 55, 55, 56, 57, 58, 59, 60, 
62, 63, 66, 67, 69, 70, 72, 73, 76, 77, 
80, 82, 84, 86, 94, 111, 117, 100 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 14, 14, 14, 14, 14, 14, 15, 15, 
15, 15, 15, 16, 16, 16, 16, 17, 17, 17, 
17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 
20, 20, 20, 21, 21, 21, 21, 22, 22, 23, 
23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 
26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 
29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 
33, 33, 34, 34, 34, 35, 35, 35, 36, 37, 
38, 38, 38, 39, 39, 40, 42, 42, 43, 43, 
44, 44, 45, 46, 47, 47, 48, 51, 50, 56, 
56, 56, 57, 57, 57, 57, 58, 59, 59, 61, 
65, 66, 67, 69, 71, 73, 75, 76, 80, 81, 
83, 84, 85, 85, 86, 91, 100, 104 
};

short leftDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 16, 16, 16, 16, 16, 16, 
18, 18, 18, 18, 17, 17, 17, 17, 19, 19, 
19, 19, 19, 19, 20, 20, 20, 20, 20, 22, 
22, 22, 21, 21, 21, 21, 23, 23, 23, 23, 
23, 24, 24, 24, 25, 25, 26, 26, 26, 27, 
27, 28, 28, 28, 28, 29, 29, 30, 30, 30, 
31, 31, 31, 31, 32, 32, 32, 33, 33, 34, 
34, 35, 35, 36, 36, 36, 37, 38, 38, 39, 
40, 40, 41, 41, 42, 43, 43, 44, 44, 45, 
46, 46, 47, 48, 49, 50, 51, 52, 53, 54, 
57, 57, 58, 58, 59, 60, 61, 62, 63, 64, 
66, 68, 69, 71, 72, 76, 77, 81, 82, 83, 
84, 84, 85, 91, 100, 114, 122, 124 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 17, 17, 17, 17, 17, 17, 17, 17, 
17, 17, 17, 17, 17, 17, 18, 18, 18, 19, 
19, 19, 19, 20, 20, 20, 20, 20, 21, 21, 
21, 22, 22, 22, 22, 23, 23, 23, 23, 24, 
24, 24, 25, 25, 25, 25, 26, 26, 27, 27, 
27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 
31, 31, 31, 32, 32, 32, 33, 33, 34, 34, 
35, 35, 36, 36, 36, 37, 38, 38, 39, 39, 
40, 41, 41, 42, 43, 44, 44, 45, 46, 47, 
48, 48, 49, 50, 52, 53, 54, 54, 55, 56, 
58, 59, 60, 62, 63, 69, 71, 73, 74, 75, 
78, 80, 81, 81, 84, 85, 86, 86 
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
