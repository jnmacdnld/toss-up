#ifndef ARM_C
#define ARM_C

#include "motors.c"

#define kArmUpPos   3270
#define kArmDownPos 1500
#define kArmAllDownPos 1310 // Define me to an actual value
#define kArmBarrierPos 2300
#define kArmBigBallPos 1775 // Define me to an actual value

int armPresets[4] = {kArmAllDownPos, kArmBigBallPos, kArmBarrierPos, kArmUpPos};

#define kArmUpPower    kFullPower
#define kArmDownPower  -kFullPower / 2
#define kArmHoldPower  25 // Meant for two rubber bands (double looped) on both sides of the arm

#define armPos         SensorValue[armPot]

#define armDownPressed    vexRT[Btn6D]
#define armUpPressed      vexRT[Btn6U]
#define armUpPresetPressed vexRT[Btn8U]
#define armDownPresetPressed vexRT[Btn8D]

#define armDownFullPowerPressed vexRT[Btn7D]
#define armUpFullPowerPressed vexRT[Btn7U]

float armKp = ( (127.0 - kArmHoldPower) / 45.0) * (250.0 / 4095.0);

void ArmSetKp(float begin_slowing_at_deg) {
	armKp = ( (127.0 - kArmHoldPower) / begin_slowing_at_deg) * (250.0 / 4095.0);
}

int armControlTarget = -1;
int armControlPower = 0;
bool armControlActive = false;
bool armControlReachedTarget = false;

void ArmSetPower(int value);

bool ArmIsDown();
bool ArmIsUp();

void ArmControlSetTarget(int target);
void ArmControlStep();
void ArmControlReset();

void ArmHoldPos();
void ArmUpdate();

void ArmUpdate() {
	if (armUpPresetPressed)
		ArmControlSetTarget(kArmUpPos);
	else if (armDownPresetPressed)
		ArmControlSetTarget(kArmAllDownPos);

	if ( armDownFullPowerPressed ) {
		ArmSetPower(-kFullPower);
	} else if ( armUpFullPowerPressed ) {
		ArmSetPower( kFullPower );
	} else if ( armUpPressed && !ArmIsUp() ) {
		ArmSetPower(kArmUpPower);
		armControlActive = false;
	} else if ( armDownPressed && !ArmIsDown() ) {
		ArmSetPower(kArmDownPower);
		armControlActive = false;
	} else if (armControlActive) {
		ArmControlStep();
	} else {
		ArmHoldPos();
	}
}

void ArmSetPower(int value) {
	MotorsSet(leftArm, value);
	MotorsSet(rightArm, value);
}

bool ArmIsDown() {
	return (armPos <= kArmDownPos);
}

bool ArmIsUp() {
	return (armPos >= kArmUpPos);
}

void ArmControlSetTarget(int target) {
	if (target == kArmBarrierPos)
		// ArmSetKp(25.0);
	else
		ArmSetKp(45.0);

	if (armPos < target)
		armControlPower = kArmUpPower;
	else
		armControlPower = kArmDownPower;

	armControlTarget = target;
	armControlActive = true;

	armControlReachedTarget = false;
}

void ArmControlStep() {
	if (armControlActive == false)
		return;
	
	int power = (armControlTarget - armPos) * armKp;

	if (abs(power) > armControlPower)
		power = sgn(power) * abs(armControlPower);

	ArmSetPower(power + kArmHoldPower);

	if ( abs(armControlTarget - armPos) < 25)
		armControlReachedTarget = true;
}

void ArmHoldPos() {
	if ( ArmIsDown() ) // Don't try to hold up the arm if it's all the way down
			ArmSetPower(0);
	else
		ArmSetPower(kArmHoldPower); // Hold up the arm so it doesn't fall
}

void ArmMoveToPos(int pos) {
	writeDebugStreamLine("Moving arm");

	ArmControlSetTarget(pos);

  while (!armControlReachedTarget)
  	ArmControlStep();

  ArmHoldPos();
}

void ArmControlReset() {
  armControlTarget = -1;
  armControlPower = 0;
  armControlActive = false;
  armControlReachedTarget = false;
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
