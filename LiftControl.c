#ifndef LIFT_CONTROL
#define LIFT_CONTROL

#include "Lift.c"

void LiftControlMoveToPosAsync(int target);
void LiftControlStep();
void LiftControlStepDownPreset();

void LiftControlReset();
void LiftControlDisable();
void LiftControlEnable();

int liftControlTarget = -1;
int liftControlPower = 0;
bool liftControlActive = false;
bool liftControlReachedTarget = false;

float liftKp = ( (127.0 - kLiftHoldPower) / 45.0) * (250.0 / 4095.0);

// Task to move the lift to the requested position
task LiftControl()
{
	while (true)
	{
		// Only move the lift if lift control is enabled
		if (liftControlActive)
		{
			// If the requested position has been reached, hold the lift in place,
			// if not, move toward that position

      // Handle moving to the down position separately
			if (liftControlTarget == kLiftDownPos)
        LiftControlStepDownPreset();
      else if (liftControlReachedTarget)
				LiftHoldPos();
			else
				LiftControlStep();
		}

		// Don't hog CPU
		wait1Msec(25);
	}
}

void LiftControlSetKp(float begin_slowing_at_deg) {
  liftKp = ( (127.0 - kLiftHoldPower) / begin_slowing_at_deg) * (250.0 / 4095.0);
}

void LiftControlMoveToPosAsync(int target) {
  if (target == kLiftBarrierPos)
    // LiftControlSetKp(25.0);
  else
    LiftControlSetKp(45.0);

  if (LIFT_POT < target)
    liftControlPower = kLiftUpPower;
  else
    liftControlPower = kLiftDownPower;

  liftControlTarget = target;
  liftControlActive = true;

  liftControlReachedTarget = false;
}

void LiftControlMoveToPosSync(int pos) {
	writeDebugStreamLine("Call to LiftControlMoveToPosSync\n");

	LiftControlMoveToPosAsync(pos);

  while (!liftControlReachedTarget)
  	LiftControlStep();

  LiftHoldPos();
}

void LiftControlStep() {

  if (!liftControlActive)
    return;

  // Handle the down preset separately
  if (liftControlTarget == kLiftDownPos) {
    LiftControlStepDownPreset();
    return;
  }

  short error = liftControlTarget - LIFT_POT;

  if ( abs(error) > (kPotTicksPerDegree * 15) ) {
    int power = error * liftKp;

    if (abs(power) > liftControlPower)
      power = sgn(power) * abs(liftControlPower);

    if (liftControlTarget == kLiftUpPos)
      power += 10;

    LiftSetPower(power + kLiftHoldPower);
  } else {
    liftControlReachedTarget = true;
    LiftHoldPos();
  }
}

void LiftControlStepDownPreset() {
  if ( LiftIsDown() )
  {
    LiftHoldPos();
    liftControlReachedTarget = true;
  }
  else
  {
    LiftSetPower(kLiftDownPower);
  }
}

void LiftControlReset()
{
  liftControlTarget = -1;
  liftControlPower = 0;
  liftControlActive = false;
  liftControlReachedTarget = false;
}

void LiftControlDisable()
{
	liftControlActive = false;
}

void LiftControlEnable()
{
	liftControlActive = true;
}

#endif
