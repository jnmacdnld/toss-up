#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 21, 21, 21, 21, 21, 21, 21, 21, 
21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 
23, 23, 23, 24, 24, 24, 24, 25, 25, 25, 
26, 26, 27, 27, 28, 28, 28, 29, 29, 29, 
30, 30, 31, 31, 31, 32, 32, 33, 33, 34, 
34, 35, 35, 36, 36, 37, 37, 37, 38, 39, 
39, 40, 40, 41, 43, 44, 44, 44, 44, 45, 
45, 45, 46, 46, 47, 48, 49, 50, 53, 53, 
56, 56, 56, 56, 57, 57, 57, 58, 59, 60, 
60, 62, 64, 64, 67, 68, 69, 70, 72, 73, 
75, 78, 79, 80, 81, 82, 83, 83, 85, 85, 
87, 87, 92, 93, 96, 103, 125, 127 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 12, 12, 12, 12, 11, 11, 
11, 14, 14, 14, 14, 13, 13, 13, 13, 15, 
15, 15, 15, 16, 16, 16, 16, 16, 17, 17, 
17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 
20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 
22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 
25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 
28, 28, 29, 29, 30, 30, 31, 31, 31, 32, 
32, 33, 33, 34, 34, 35, 36, 36, 37, 37, 
37, 39, 40, 41, 42, 42, 43, 43, 45, 46, 
46, 47, 48, 49, 51, 53, 54, 55, 57, 58, 
60, 64, 65, 67, 68, 70, 72, 73, 76, 77, 
79, 81, 82, 82, 83, 83, 84, 84 
};

short leftDriveBackwardSettingLut[128] =
{
0, 11, 19, 19, 19, 19, 19, 19, 19, 19, 
19, 19, 19, 19, 19, 22, 22, 22, 22, 22, 
22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 
23, 24, 24, 24, 25, 25, 25, 25, 26, 26, 
27, 27, 27, 28, 28, 28, 29, 29, 30, 30, 
31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 
35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 
40, 40, 41, 41, 42, 42, 43, 44, 45, 46, 
47, 47, 48, 48, 49, 49, 50, 51, 51, 52, 
53, 54, 55, 57, 59, 60, 61, 61, 62, 62, 
63, 64, 65, 66, 67, 68, 71, 72, 73, 75, 
76, 76, 79, 79, 80, 81, 82, 84, 85, 94, 
87, 92, 92, 101, 105, 122, 125, 127 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 
14, 14, 14, 14, 14, 14, 14, 14, 18, 18, 
18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 
18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 
20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 
22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 
25, 26, 26, 26, 27, 27, 27, 28, 28, 29, 
29, 29, 29, 30, 30, 30, 31, 31, 32, 32, 
32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 
37, 38, 39, 40, 41, 42, 42, 43, 43, 43, 
44, 44, 45, 46, 46, 47, 48, 50, 50, 51, 
54, 54, 58, 60, 61, 64, 67, 67, 68, 68, 
69, 72, 75, 77, 78, 82, 83, 84 
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
