#ifndef ARM_C
#define ARM_C

#include "Motors.c"

#define kArmUpPos      3160
#define kArmDownPos    1460
#define kArmAllDownPos 1451
#define kArmBarrierPos 2300

#define kArmUpPower    kFullPower
#define kArmDownPower  -kFullPower / 2
#define kArmHoldPower  25 // Meant for two rubber bands (double looped) on both sides of the arm

#define ARM_POT            SensorValue[armPot]
#define kPotTicksPerDegree 16.05882

void ArmSetPower(int value);
bool ArmIsDown();
bool ArmIsUp();
void ArmHoldPos();

void ArmSetPower(int value) {
	MotorsSet(leftArm, value);
	MotorsSet(rightArm, value);
}

bool ArmIsDown() {
	return (ARM_POT <= kArmDownPos);
}

bool ArmIsUp() {
	return (ARM_POT >= kArmUpPos);
}


void ArmHoldPos() {
	if ( ArmIsDown() ) // Don't try to hold up the arm if it's all the way down
			ArmSetPower(-15);
	else
		ArmSetPower(kArmHoldPower); // Hold up the arm so it doesn't fall
}

void ArmInit() {
	short arm_motors[2] = {leftArm, rightArm};

	for (short i = 0; i < 2; i++) {
		Motor* m = &motors[arm_motors[i]];
    m->min_delta_setting = -256;
    m->max_delta_setting = 60;
	}
}

#endif
