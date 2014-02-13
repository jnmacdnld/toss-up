#ifndef ARM_C
#define ARM_C

#include "Motors.c"

#define kNumArmMotors 2

#define kArmUpperLimit 0
#define kArmLowerLimit 0
#define kArmTolerance 25

#define kArmFloorHeight 0
#define kArmBarrierHeight 0
#define kArmStashHeight 0

#define ARM_POT SensorValue[armPot]

static tMotor arm_motors[kNumArmMotors];

void ArmSetPower(short power) {
  // Set each arm motor to the requested power
  for (short i = 0; i < kNumArmMotors; i++)
    MotorsSet(arm_motors[i], power);
}

bool ArmAtPreset(short preset) {
  // Account for the tolerance
  if ( abs(preset - ARM_POT) < kArmTolerance)
    return true;
  else
    return false;
}

bool ArmAtUpperLimit() {
  return ArmAtPreset(kArmLowerLimit);
}

bool ArmAtLowerLimit() {
  return ArmAtPreset(kArmLowerLimit);
}

#endif
