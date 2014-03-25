#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLutsForward[10];
short* motorLutsBackward[10];

short leftDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 19, 19, 19, 19, 19, 19, 19, 19, 19, 
19, 19, 19, 20, 20, 20, 21, 21, 21, 21, 
22, 22, 22, 22, 22, 23, 23, 24, 24, 24, 
24, 25, 25, 25, 25, 25, 26, 26, 26, 27, 
27, 27, 28, 28, 28, 29, 29, 30, 30, 30, 
31, 31, 31, 32, 32, 32, 32, 33, 33, 34, 
34, 35, 35, 36, 36, 37, 37, 37, 38, 38, 
39, 40, 40, 41, 42, 43, 43, 44, 44, 45, 
45, 46, 47, 47, 49, 49, 50, 51, 52, 53, 
54, 56, 62, 62, 62, 64, 64, 64, 65, 63, 
66, 66, 67, 70, 71, 72, 75, 76, 81, 82, 
83, 84, 85, 86, 86, 87, 90, 103 
};

short rightDriveForwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
0, 18, 18, 18, 18, 18, 18, 18, 18, 18, 
18, 18, 18, 18, 18, 18, 20, 20, 20, 21, 
22, 22, 22, 23, 23, 23, 23, 23, 24, 24, 
24, 24, 25, 26, 26, 27, 27, 27, 27, 28, 
28, 28, 29, 29, 29, 30, 30, 31, 31, 31, 
32, 32, 32, 33, 33, 33, 35, 35, 35, 36, 
36, 36, 38, 38, 38, 39, 39, 40, 40, 40, 
42, 42, 42, 43, 44, 44, 45, 47, 47, 48, 
48, 49, 50, 50, 51, 52, 53, 54, 54, 55, 
57, 57, 58, 58, 61, 64, 65, 67, 68, 69, 
72, 73, 74, 76, 77, 79, 81, 81, 82, 82, 
84, 84, 84, 86, 90, 99, 125, 125 
};

short leftDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 
20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 
20, 20, 20, 21, 21, 21, 21, 21, 21, 22, 
22, 22, 23, 23, 23, 24, 24, 24, 24, 24, 
25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 
28, 28, 28, 29, 29, 29, 29, 30, 30, 30, 
31, 31, 31, 33, 33, 32, 32, 32, 34, 34, 
34, 34, 36, 36, 37, 37, 37, 38, 38, 38, 
40, 40, 40, 41, 41, 41, 42, 42, 42, 44, 
44, 44, 46, 46, 49, 49, 49, 50, 50, 51, 
52, 53, 53, 54, 55, 57, 58, 60, 60, 62, 
64, 65, 66, 70, 71, 77, 77, 75, 81, 81, 
80, 80, 80, 82, 82, 85, 84, 116 
};

short rightDriveBackwardSettingLut[128] =
{
0, 0, 0, 0, 18, 18, 18, 18, 18, 18, 
21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 
22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 
23, 25, 25, 25, 25, 25, 24, 24, 24, 24, 
26, 26, 26, 26, 27, 27, 28, 28, 28, 28, 
29, 29, 29, 30, 30, 30, 30, 30, 31, 31, 
32, 32, 32, 33, 33, 33, 33, 34, 35, 35, 
36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 
40, 40, 40, 42, 42, 43, 43, 44, 44, 45, 
46, 47, 47, 48, 48, 49, 50, 50, 51, 52, 
53, 55, 55, 56, 57, 59, 59, 61, 63, 62, 
65, 66, 67, 70, 72, 73, 75, 79, 80, 81, 
81, 83, 84, 85, 87, 91, 101, 96 
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
