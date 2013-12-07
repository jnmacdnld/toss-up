#ifndef ARM_C
#define ARM_C

#include "motor.c"

#define ARM_UP_POS   3200
#define ARM_DOWN_POS 1500
#define ARM_ALL_DOWN_POS 1310 // Define me to an actual value
#define ARM_BARRIER_POS 2240
#define ARM_BIG_BALL_POS 1775 // Define me to an actual value

#define ARM_UP_PWR    FULL_POWER
#define ARM_DOWN_PWR  -FULL_POWER / 2
#define ARM_HOLD_PWR  25 // Meant for two rubber bands (double looped) on both sides of the arm

#define armPos         SensorValue[armPot]

#define armDownPressed    vexRT[Btn6D]
#define armUpPressed      vexRT[Btn6U]
#define armUpMacroPressed vexRT[Btn8U]
#define armDownMacroPressed vexRT[Btn8D]


#define BEGIN_SLOWING_AT_DEG 45.0
#define ARM_KP ( (127.0 - ARM_HOLD_PWR) / BEGIN_SLOWING_AT_DEG) * (250.0 / 4095.0)

int armControlTarget = -1;
int armControlPwr = 0;
bool armControlActive = false;

void armSetPower(int value);

bool armIsDown();
bool armIsUp();

void armUpPressedCb();
void armDownPressedCb();

void armControlSetTarget(int target);
void armControlStep();

void holdArmPos();
void updateArm();

void updateArm() {
	if (armUpMacroPressed && !armIsUp() )
		armControlSetTarget(ARM_UP_POS);
	else if (armDownMacroPressed && !armIsDown() )
		armControlSetTarget(ARM_ALL_DOWN_POS); // Go a little past the down position so we know it gets there

	if (armUpPressed)
		armUpPressedCb();
	else if (armDownPressed)
		armDownPressedCb();
	else if (armControlActive)
		armControlStep();
	else
		holdArmPos();
}

void armSetPower(int value) {
	setMotor(leftArm, value);
	setMotor(rightArm, value);
}

bool armIsDown() {
	return (armPos <= ARM_DOWN_POS);
}

bool armIsUp() {
	return (armPos >= ARM_UP_POS);
}

void armUpPressedCb() {
	if ( armIsUp() ) {
		holdArmPos();
		return;
	}

	armSetPower(ARM_UP_PWR);
	armControlActive = false;
}

void armDownPressedCb() {
	if ( armIsDown() ) {
		holdArmPos();
		return;
	}

	armSetPower(ARM_DOWN_PWR);
	armControlActive = false;
}

void armControlSetTarget(int target) {
	if (armPos < target)
		armControlPwr = ARM_UP_PWR;
	else
		armControlPwr = ARM_DOWN_PWR;

	armControlTarget = target;
	armControlActive = true;
}

void armControlStep() {
	if (armControlPwr > 0 && armPos < armControlTarget ||
			armControlPwr < 0 && armPos > armControlTarget) {
		int power = (armControlTarget - armPos) * ARM_KP;

		if (abs(power) > armControlPwr)
			power = sgn(power) * abs(armControlPwr);

		armSetPower(power + ARM_HOLD_PWR);
	}	else {
		writeDebugStreamLine("armControlTarget = %d, armPos = %d, deactivating arm control", armControlTarget, armPos);
		armControlActive = false;
	}
}

void holdArmPos() {
	if ( armIsDown() ) // Don't try to hold up the arm if it's all the way down
			armSetPower(0);
	else
		armSetPower(ARM_HOLD_PWR); // Hold up the arm so it doesn't fall
}

void armMoveToPos(int pos) {
	armControlSetTarget(ARM_BARRIER_POS);

  while(armControlActive)
  	armControlStep();

  holdArmPos();
}

#endif
