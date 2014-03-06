#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 17, 17, 17, 17, 
17, 17, 17, 17, 17, 18, 18, 18, 18, 19, 
19, 20, 20, 20, 20, 21, 21, 21, 21, 21, 
22, 22, 22, 23, 23, 24, 24, 24, 25, 25, 
26, 26, 26, 26, 27, 27, 28, 28, 28, 29, 
29, 30, 30, 30, 31, 31, 32, 32, 33, 33, 
34, 34, 35, 35, 36, 36, 36, 37, 37, 38, 
38, 39, 39, 40, 41, 41, 42, 42, 43, 43, 
44, 44, 45, 45, 46, 47, 47, 48, 49, 51, 
52, 53, 53, 54, 54, 55, 56, 56, 58, 59, 
60, 61, 63, 64, 66, 67, 69, 70, 71, 74, 
75, 76, 76, 78, 78, 79, 80, 82, 83, 84, 
85, 86, 88, 87, 91, 98, 122, 123 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 10, 10, 10, 11, 11, 11, 11, 
12, 12, 12, 12, 12, 13, 13, 13, 13, 14, 
14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 
16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 
18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 
20, 21, 21, 21, 21, 22, 22, 22, 22, 23, 
23, 23, 24, 24, 24, 24, 25, 25, 25, 26, 
26, 26, 27, 27, 27, 28, 28, 29, 29, 29, 
30, 30, 31, 31, 31, 32, 32, 33, 33, 34, 
35, 36, 36, 37, 37, 38, 38, 39, 40, 40, 
41, 41, 42, 43, 44, 45, 46, 47, 48, 49, 
50, 53, 54, 55, 58, 59, 61, 63, 65, 67, 
68, 71, 72, 73, 74, 75, 77, 78 
};

short leftDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 
19, 19, 19, 19, 19, 21, 21, 21, 21, 22, 
22, 23, 23, 24, 24, 24, 24, 25, 25, 25, 
26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 
29, 30, 30, 31, 31, 32, 32, 33, 33, 33, 
34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 
39, 39, 40, 41, 41, 42, 42, 43, 44, 44, 
45, 46, 46, 47, 47, 49, 50, 50, 51, 52, 
52, 53, 54, 55, 56, 57, 57, 58, 59, 61, 
62, 63, 64, 66, 68, 69, 71, 71, 75, 73, 
76, 77, 78, 79, 81, 81, 82, 83, 83, 84, 
85, 89, 92, 95, 110, 118, 123, 126 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 13, 13, 13, 13, 13, 12, 
12, 12, 12, 12, 12, 14, 14, 14, 14, 14, 
14, 14, 15, 15, 15, 15, 15, 16, 16, 16, 
16, 17, 17, 17, 17, 18, 18, 18, 18, 18, 
19, 19, 19, 19, 19, 20, 20, 20, 20, 21, 
21, 21, 21, 22, 22, 22, 22, 22, 23, 23, 
23, 23, 24, 24, 24, 24, 25, 25, 25, 26, 
26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 
29, 29, 30, 30, 31, 31, 31, 32, 32, 32, 
33, 33, 34, 35, 35, 36, 36, 37, 37, 38, 
38, 39, 39, 40, 41, 41, 42, 43, 43, 44, 
45, 47, 48, 50, 52, 53, 54, 57, 57, 58, 
59, 61, 62, 63, 64, 66, 67, 68 
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
