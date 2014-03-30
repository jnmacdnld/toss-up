#ifndef DEBUG
#define DEBUG

// Declare globals to hold sensor values that can be viewed in the debugger
int liftPotVal;
int _backLeftDriveEncoder;
int _backRightDriveEncoder;
float gyroValue;
int gyroValueRaw;
int sonarValue;
int leftFrontLineValue;

bool seeLine;
int lineNumber;

task Debug()
{
  while (true)
  {
    // Store sensor values in globals so they can be viewed in the debugger
    liftPotVal = SensorValue[liftPot];
    _backLeftDriveEncoder = nMotorEncoder[backLeftDrive];
    _backRightDriveEncoder = nMotorEncoder[backRightDrive];
    gyroValue = GyroGetAngle();
    gyroValueRaw = SensorValue[gyro];
    sonarValue = SensorValue[stashSonar];
    leftFrontLineValue = SensorValue[leftFrontLine];

    seeLine = SensorValue[leftFrontLine] < 2300;

    if (seeLine)
      lineNumber++;

    wait1Msec(25);
  }
}

#endif
