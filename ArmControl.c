#ifndef ARM_CONTROL
#define ARM_CONTROL

#include "Arm.c"

// Task to move   the arm to the requested position
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

#endif
