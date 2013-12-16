#ifndef ARM_C
#define ARM_C

#include "motor.c"

#define kArmUpPos   3200
#define kArmDownPos 1500
#define kArmAllDownPos 1310 // Define me to an actual value
#define kArmBarrierPos 2240
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

float armKp = ( (127.0 - kArmHoldPower) / 45.0) * (250.0 / 4095.0);

void ArmSetKp(float begin_slowing_at_deg) {
	armKp = ( (127.0 - kArmHoldPower) / begin_slowing_at_deg) * (250.0 / 4095.0);
}

int armControlTarget = -1;
int armControlPower = 0;
bool armControlActive = false;

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

	if ( armUpPressed && !ArmIsUp() ) {
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
	MotorSet(leftArm, value);
	MotorSet(rightArm, value);
}

bool ArmIsDown() {
	return (armPos <= kArmDownPos);
}

bool ArmIsUp() {
	return (armPos >= kArmUpPos);
}

void ArmControlSetTarget(int target) {
	if (target == kArmBarrierPos)
		ArmSetKp(35.0);
	else
		ArmSetKp(45.0);

	if (armPos < target)
		armControlPower = kArmUpPower;
	else
		armControlPower = kArmDownPower;

	armControlTarget = target;
	armControlActive = true;
}

void ArmControlStep() {
	if (armControlPower > 0 && armPos < armControlTarget ||
			armControlPower < 0 && armPos > armControlTarget) {
		int power = (armControlTarget - armPos) * armKp;

		if (abs(power) > armControlPower)
			power = sgn(power) * abs(armControlPower);

		ArmSetPower(power + kArmHoldPower);
	}	else {
		writeDebugStreamLine("armControlTarget = %d, armPos = %d, deactivating arm control", armControlTarget, armPos);
		armControlActive = false;
	}
}

void ArmHoldPos() {
	if ( ArmIsDown() ) // Don't try to hold up the arm if it's all the way down
			ArmSetPower(0);
	else
		ArmSetPower(kArmHoldPower); // Hold up the arm so it doesn't fall
}

void ArmMoveToPos(int pos) {
	ArmControlSetTarget(pos);

  while (armControlActive)
  	ArmControlStep();

  ArmHoldPos();
}

void ArmControlReset() {
  armControlTarget = -1;
  armControlPower = 0;
  armControlActive = false;
}

#endif
