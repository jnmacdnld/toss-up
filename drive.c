#ifndef DRIVE_C
#define DRIVE_C

#include "motor.c"

void setLeftDrive(int setting);
void setRightDrive(int setting);

// LUT that goes from 20 to 100 rpm linearly
// Computed for left drive
int leftDriveSettingLut[128] =
{
0, 29, 29, 29, 30, 30, 30, 30, 30, 30,
31, 31, 31, 32, 32, 32, 32, 32, 32, 33,
33, 33, 33, 33, 33, 33, 34, 34, 34, 34,
34, 35, 35, 36, 37, 37, 38, 38, 38, 39,
39, 39, 39, 39, 39, 40, 40, 40, 40, 40,
41, 41, 41, 41, 42, 44, 43, 45, 45, 45,
45, 45, 46, 46, 46, 46, 46, 49, 47, 48,
50, 50, 50, 51, 51, 51, 51, 54, 52, 55,
53, 53, 53, 53, 53, 56, 56, 56, 56, 56,
59, 63, 60, 62, 62, 61, 61, 64, 64, 64,
67, 65, 65, 70, 70, 71, 69, 69, 74, 74,
72, 73, 75, 78, 78, 76, 76, 76, 79, 79,
81, 80, 80, 82, 82, 82, 83, 83
};

// LUT that goes from 20 10 100 rpm linearly
// Computed for right drive
int rightDriveSettingLut[128] =
{
0, 31, 31, 31, 32, 32, 32, 32, 33, 33,
34, 34, 35, 35, 36, 36, 37, 37, 37, 37,
38, 38, 38, 38, 38, 38, 39, 39, 39, 39,
39, 39, 40, 40, 40, 41, 42, 43, 43, 43,
45, 45, 45, 45, 45, 46, 46, 46, 46, 46,
50, 50, 50, 47, 49, 49, 51, 51, 51, 51,
51, 52, 52, 52, 52, 55, 54, 54, 56, 56,
56, 60, 60, 60, 57, 58, 59, 59, 61, 61,
61, 61, 64, 64, 64, 63, 65, 65, 65, 66,
66, 68, 67, 67, 73, 73, 70, 72, 71, 71,
74, 74, 74, 76, 77, 77, 78, 78, 80, 79,
79, 81, 81, 81, 81, 82, 82, 82, 83, 83,
84, 84, 84, 85, 85, 85, 85, 86
};

void updateDriveTankDrive();
void driveSetPower(int pwr);

void updateDriveTankDrive() {
  setLeftDrive(vexRT[Ch3]);
  setRightDrive(vexRT[Ch2]);
}

void driveSetPowerUnadjusted(int pwr) {
  motor[leftDrive]  = pwr;
  motor[rightDrive] = pwr;
}

void driveSetPower(int pwr) {
  setLeftDrive(pwr);
  setRightDrive(pwr);
}

void bound(int &number, int bounds) {
  if (abs(number) > bounds)
    number = sgn(number) * bounds;
}

void setRightDrive(int setting) {
  bound(setting, 127);

  if (setting < 0)
    motor[rightDrive] = -rightDriveSettingLut[-setting];
  else
    motor[rightDrive] = rightDriveSettingLut[setting];
}

void setLeftDrive(int setting) {
  bound(setting, 127);

  if (setting < 0)
    motor[leftDrive] = -leftDriveSettingLut[-setting];
  else
    motor[leftDrive] = leftDriveSettingLut[setting];
}

#endif
