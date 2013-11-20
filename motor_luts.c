#ifndef MOTOR_LUTS
#define MOTOR_LUTS

int* motorLuts[10];

int rightDriveSettingLut[128] =
{
22, 22, 22, 22, 22, 23, 23, 24, 24, 24, 
24, 25, 25, 25, 25, 25, 27, 27, 27, 27, 
28, 28, 29, 29, 29, 30, 30, 30, 30, 30, 
31, 31, 32, 33, 33, 33, 34, 34, 34, 35, 
35, 35, 36, 36, 36, 37, 37, 38, 38, 38, 
39, 39, 40, 41, 41, 42, 42, 43, 43, 43, 
44, 44, 44, 44, 45, 45, 47, 47, 47, 49, 
49, 48, 50, 50, 50, 51, 51, 53, 53, 54, 
55, 55, 57, 57, 58, 58, 59, 59, 61, 61, 
62, 64, 64, 65, 67, 67, 68, 70, 71, 71, 
72, 73, 75, 75, 76, 77, 78, 79, 80, 80, 
81, 81, 82, 83, 83, 84, 84, 85, 86, 93, 
111, 121, 124, 125, 126, 126, 126, 126 
};

int leftDriveSettingLut[128] = 
{
23, 23, 23, 23, 77, 25, 25, 25, 26, 26, 
26, 26, 27, 27, 27, 29, 29, 29, 29, 30, 
30, 30, 31, 31, 32, 32, 32, 33, 33, 33, 
34, 34, 35, 35, 36, 36, 36, 37, 37, 37, 
37, 38, 38, 39, 39, 40, 40, 40, 41, 41, 
42, 43, 43, 44, 44, 44, 45, 45, 46, 46, 
47, 47, 48, 48, 50, 50, 49, 49, 51, 51, 
52, 53, 53, 54, 56, 55, 57, 57, 57, 58, 
59, 60, 61, 62, 62, 63, 64, 64, 66, 66, 
67, 68, 69, 69, 70, 72, 72, 73, 74, 75, 
76, 78, 79, 80, 81, 85, 85, 85, 85, 85, 
85, 85, 85, 86, 86, 86, 86, 86, 86, 89, 
87, 101, 113, 122, 126, 126, 126, 126 
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
