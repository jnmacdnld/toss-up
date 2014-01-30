#ifndef DEBUG_C
#define DEBUG_C

typedef struct {
  short arm_pot;

  long back_left_encoder;
  long back_right_encoder;

  float gyro;
} DebugInfo;

DebugInfo debug_info;

task DebugInfo()
{
  // Pointer to debug_info for convenience
  DebugInfo* d = &debug_info;

  while (true)
  {
    // Update the data in the debug_info structure
    d->arm_pot = SensorValue[armPot];
    d->back_left_encoder = nMotorEncoder[backLeftDrive];
    d->back_right_encoder = nMotorEncoder[backRightDrive];
    d->gyro = GyroGetAngle();

    // The data doesn't need to be updated very frequently
    wait1Msec(500);
  }
}

#endif