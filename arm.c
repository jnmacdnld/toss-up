#include "arm.h"

void updateArm() {
	if (armUpMacroPressed)
		armControlSetTarget(ARM_UP_POS);
	else if (armDownMacroPressed)
		armControlSetTarget(ARM_DOWN_POS);
	
	if (armUpPressed)
		armUpPressedCb();
	else if (armDownPressed)
		armDownPressedCb();
	else if (armControlActive)
		armControlStep();
	else
		holdArmPos();
}

void setArmPwr(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
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
	
	setArmPwr(ARM_UP_PWR);
	armControlActive = false;
}

void armDownPressedCb() {
	if ( armIsDown() ) {
		holdArmPos();
		return;
	}

	setArmPwr(ARM_DOWN_PWR);
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
			armControlPwr < 0 && armPos > armControlTarget)
		setArmPwr(armControlPwr);
	// else
	//   armControlActive = false;
}

void holdArmPos() {
	if ( armIsDown() ) // Don't try to hold up the arm if it's all the way down
			setArmPwr(0);
	else
		setArmPwr(ARM_HOLD_PWR); // Hold up the arm so it doesn't fall
}
