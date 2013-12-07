#ifndef MOTOR_LUTS
#define MOTOR_LUTS

int* motorLuts[10];

int rightDriveSettingLut[128] =
{
18, 18, 18, 18, 18, 19, 19, 19, 19, 20, 
20, 20, 20, 21, 21, 21, 22, 22, 22, 22, 
22, 23, 23, 23, 24, 24, 24, 24, 25, 25, 
25, 26, 26, 26, 26, 27, 27, 27, 27, 28, 
28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 
31, 31, 32, 32, 33, 33, 33, 34, 34, 35, 
35, 36, 36, 36, 37, 37, 38, 38, 39, 39, 
40, 40, 40, 41, 41, 42, 43, 43, 44, 44, 
45, 46, 47, 47, 48, 48, 49, 49, 51, 52, 
52, 53, 54, 54, 56, 56, 57, 58, 59, 60, 
61, 63, 64, 65, 66, 67, 70, 71, 72, 73, 
74, 75, 78, 79, 81, 82, 83, 83, 84, 85, 
85, 86, 91, 99, 123, 124, 126, 126 
};

int leftDriveSettingLut[128] = 
{
19, 19, 19, 20, 20, 20, 20, 20, 20, 21, 
21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 
23, 23, 24, 24, 24, 25, 25, 25, 25, 25, 
26, 26, 26, 26, 27, 27, 27, 28, 28, 28, 
28, 28, 28, 30, 30, 30, 31, 31, 31, 32, 
32, 32, 33, 33, 33, 34, 34, 34, 35, 36, 
36, 37, 37, 37, 38, 38, 38, 39, 39, 40, 
40, 41, 41, 42, 42, 42, 43, 44, 44, 44, 
46, 46, 46, 47, 47, 49, 49, 50, 50, 51, 
51, 52, 52, 54, 55, 55, 56, 57, 57, 58, 
60, 60, 63, 64, 64, 67, 67, 68, 69, 70, 
70, 72, 74, 75, 76, 78, 78, 80, 82, 83, 
83, 84, 85, 87, 93, 109, 121, 124 
};


void initMotorLuts() {
  motorLuts[frontLeftDrive] = &leftDriveSettingLut;
  motorLuts[middleLeftDrive] = &leftDriveSettingLut;
  motorLuts[backLeftDrive] = &leftDriveSettingLut;

 	motorLuts[frontRightDrive] = &rightDriveSettingLut;
  motorLuts[middleRightDrive] = &rightDriveSettingLut;
  motorLuts[backRightDrive] = &rightDriveSettingLut;
}

#endif /* MOTOR_LUTS */
