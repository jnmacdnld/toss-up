#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 19, 19, 19, 
19, 19, 19, 19, 20, 20, 20, 21, 21, 21, 
21, 22, 22, 22, 22, 23, 23, 23, 23, 23, 
23, 24, 24, 24, 24, 24, 25, 25, 25, 26, 
26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 
29, 29, 30, 30, 30, 30, 31, 31, 32, 32, 
32, 33, 33, 33, 34, 34, 34, 35, 35, 36, 
36, 37, 37, 38, 38, 38, 39, 40, 40, 41, 
41, 41, 42, 43, 43, 44, 44, 45, 45, 47, 
47, 48, 49, 49, 50, 51, 52, 53, 53, 54, 
55, 56, 57, 58, 59, 59, 61, 62, 64, 69, 
69, 72, 71, 71, 73, 74, 74, 77, 78, 82, 
83, 84, 84, 85, 85, 86, 86, 87 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 25, 25, 25, 25, 
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 
25, 25, 26, 26, 26, 26, 26, 27, 27, 27, 
27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 
30, 31, 31, 32, 32, 32, 33, 33, 33, 35, 
35, 35, 35, 36, 36, 36, 37, 37, 38, 38, 
39, 39, 40, 40, 41, 41, 42, 42, 42, 43, 
44, 44, 45, 46, 46, 47, 47, 48, 48, 50, 
50, 51, 51, 52, 53, 54, 54, 55, 56, 57, 
58, 59, 60, 61, 62, 63, 64, 66, 65, 68, 
69, 70, 72, 73, 74, 74, 77, 78, 80, 82, 
82, 83, 84, 85, 86, 87, 98, 103 
};

short leftDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 
19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 
20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 
22, 22, 23, 23, 23, 23, 24, 24, 25, 25, 
25, 26, 26, 26, 26, 26, 27, 27, 28, 28, 
28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 
32, 32, 33, 33, 34, 34, 34, 35, 35, 35, 
36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 
41, 42, 42, 42, 43, 43, 44, 45, 46, 47, 
47, 48, 49, 50, 50, 51, 51, 53, 54, 54, 
55, 57, 57, 59, 62, 61, 63, 64, 66, 67, 
70, 71, 73, 75, 75, 76, 77, 77, 78, 82, 
82, 83, 83, 84, 84, 86, 88, 93 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 21, 21, 21, 21, 
21, 21, 23, 23, 23, 22, 22, 22, 24, 24, 
24, 24, 25, 25, 25, 25, 25, 25, 27, 27, 
27, 27, 27, 26, 26, 26, 29, 29, 29, 29, 
28, 28, 30, 30, 30, 30, 30, 31, 31, 31, 
31, 32, 32, 32, 33, 33, 34, 34, 35, 35, 
36, 36, 36, 36, 37, 37, 37, 38, 38, 38, 
39, 39, 40, 41, 42, 42, 42, 43, 43, 44, 
44, 45, 45, 46, 46, 47, 47, 48, 49, 50, 
51, 51, 52, 53, 53, 54, 55, 56, 57, 57, 
59, 60, 61, 62, 63, 64, 66, 66, 67, 69, 
70, 71, 72, 74, 75, 78, 80, 81, 82, 84, 
84, 85, 86, 86, 87, 91, 99, 115 
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
