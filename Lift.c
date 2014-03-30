#ifndef LIFT_C
#define LIFT_C

#include "Motors.c"

#define kLiftUpPos      3160
#define kLiftDownPos    1460
#define kLiftAllDownPos 1451
#define kLiftBarrierPos 2300

#define kLiftUpPower    kFullPower
#define kLiftDownPower  -kFullPower / 2
#define kLiftHoldPower  25 // Meant for two rubber bands (double looped) on both sides of the lift

#define LIFT_POT            SensorValue[liftPot]
#define kPotTicksPerDegree  16.05882

void LiftSetPower(int value);
bool LiftIsDown();
bool LiftIsUp();
void LiftHoldPos();

void LiftSetPower(int value) {
	MotorsSet(leftLift, value);
	MotorsSet(rightLift, value);
}

bool LiftIsDown() {
	return (LIFT_POT <= kLiftDownPos);
}

bool LiftIsUp() {
	return (LIFT_POT >= kLiftUpPos);
}


void LiftHoldPos() {
	if ( LiftIsDown() ) // Don't try to hold up the lift if it's all the way down
			LiftSetPower(-15);
	else
		LiftSetPower(kLiftHoldPower); // Hold up the lift so it doesn't fall
}

void LiftInit() {
	short lift_motors[2] = {leftLift, rightLift};

	for (short i = 0; i < 2; i++) {
		Motor* m = &motors[lift_motors[i]];
    m->min_delta_setting = -256;
    m->max_delta_setting = 60;
	}
}

#endif
