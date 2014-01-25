#ifndef MOTOR_LUTS
#define MOTOR_LUTS

short* motorLuts[10];

short rightDriveSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 15, 15, 15, 15,
15, 15, 15, 15, 15, 17, 17, 17, 17, 17,
17, 17, 18, 18, 18, 18, 18, 20, 19, 19,
19, 21, 21, 21, 21, 22, 22, 22, 23, 23,
23, 23, 24, 24, 24, 24, 25, 25, 26, 26,
27, 27, 27, 28, 28, 28, 29, 29, 29, 30,
30, 30, 31, 31, 32, 32, 32, 33, 33, 33,
34, 34, 34, 35, 35, 36, 37, 37, 37, 38,
38, 38, 40, 40, 40, 41, 41, 43, 43, 44,
45, 45, 46, 47, 48, 49, 50, 51, 52, 52,
54, 54, 55, 57, 57, 59, 60, 62, 63, 64,
65, 66, 67, 70, 73, 75, 79, 80, 82, 82,
83, 84, 84, 85, 86, 86, 96, 113
};

short leftDriveSettingLut[128] =
{
0, 0, 0, 0, 0, 0, 0, 15, 15, 15,
15, 15, 15, 15, 15, 15, 17, 17, 17, 17,
17, 17, 18, 18, 18, 18, 18, 19, 19, 19,
19, 19, 20, 20, 20, 20, 21, 21, 21, 22,
22, 22, 22, 22, 23, 23, 23, 23, 24, 24,
24, 25, 25, 26, 26, 26, 26, 27, 27, 27,
28, 28, 28, 29, 29, 29, 30, 30, 30, 31,
31, 32, 32, 32, 33, 33, 33, 34, 34, 35,
35, 35, 36, 36, 36, 37, 37, 38, 39, 39,
40, 40, 41, 41, 42, 43, 43, 44, 45, 46,
46, 47, 49, 50, 50, 51, 53, 53, 54, 54,
56, 57, 58, 60, 62, 62, 65, 66, 67, 69,
69, 72, 75, 79, 82, 84, 87, 87
};

void MotorLutsInit() {
  motorLuts[frontLeftDrive] = &leftDriveSettingLut;
  motorLuts[middleLeftDrive] = &leftDriveSettingLut;
  motorLuts[backLeftDrive] = &leftDriveSettingLut;

 	motorLuts[frontRightDrive] = &rightDriveSettingLut;
  motorLuts[middleRightDrive] = &rightDriveSettingLut;
  motorLuts[backRightDrive] = &rightDriveSettingLut;
}

#endif /* MOTOR_LUTS */
