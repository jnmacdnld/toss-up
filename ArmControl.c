#ifndef ARM_CONTROL
#define ARM_CONTROL

#include "Arm.c"

void ArmControlMoveToPosAsync(int target);
void ArmControlStep();
void ArmControlReset();
void ArmControlStepDownPreset();

int armControlTarget = -1;
int armControlPower = 0;
bool armControlActive = false;
bool armControlReachedTarget = false;

float armKp = ( (127.0 - kArmHoldPower) / 45.0) * (250.0 / 4095.0);

// Task to move the arm to the requested position
task ArmControl()
{
	while (true)
	{
		// Only move the arm if arm control is enabled
		if (armControlActive)
		{
			// If the requested position has been reached, hold the arm in place,
			// if not, move toward that position
			if (armControlReachedTarget)
				ArmHoldPos();
			else
				ArmControlStep();
		}

		// Don't hog CPU
		wait1Msec(25);
	}
}

void ArmControlSetKp(float begin_slowing_at_deg) {
  armKp = ( (127.0 - kArmHoldPower) / begin_slowing_at_deg) * (250.0 / 4095.0);
}

void ArmControlMoveToPosAsync(int target) {
  if (target == kArmBarrierPos)
    // ArmControlSetKp(25.0);
  else
    ArmControlSetKp(45.0);

  if (ARM_POT < target)
    armControlPower = kArmUpPower;
  else
    armControlPower = kArmDownPower;

  armControlTarget = target;
  armControlActive = true;

  armControlReachedTarget = false;
}

void ArmControlMoveToPosSync(int pos) {
	writeDebugStreamLine("Call to ArmControlMoveToPosSync\n");

	ArmControlMoveToPosAsync(pos);

  while (!armControlReachedTarget)
  	ArmControlStep();

  ArmHoldPos();
}

void ArmControlStep() {

  if (!armControlActive)
    return;

  // Handle the down preset separately
  if (armControlTarget == kArmDownPos) {
    ArmControlStepDownPreset();
    return;
  }

  short error = armControlTarget - ARM_POT;

  if ( abs(error) > (kPotTicksPerDegree * 15) ) {
    int power = error * armKp;

    if (abs(power) > armControlPower)
      power = sgn(power) * abs(armControlPower);

    if (armControlTarget == kArmUpPos)
      power += 10;

    ArmSetPower(power + kArmHoldPower);
  } else {
    armControlReachedTarget = true;
    ArmHoldPos();
  }
}

void ArmControlStepDownPreset() {
  if ( ArmIsDown() )
  {
    ArmHoldPos();
    armControlReachedTarget = true;
  }
  else
  {
    ArmSetPower(kArmDownPower);
  }
}

void ArmControlReset() {
  armControlTarget = -1;
  armControlPower = 0;
  armControlActive = false;
  armControlReachedTarget = false;
}

#endif
