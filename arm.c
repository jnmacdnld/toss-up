#ifndef ARM_C
#define ARM_C

void armSetPowerRaw(int value);

bool armIsDown();
bool armIsUp();

#include "motor.c"
#include "arm_control.c"

#define ARM_UP_POS   3080
#define ARM_DOWN_POS 1400
#define ARM_MIDDLE_POS 1500

#define armPos         SensorValue[armPot]

#define armUpMacroPressed vexRT[Btn8U]
#define armDownMacroPressed vexRT[Btn8D]
#define armMiddleMacroPresed vexRT[Btn8L]

void updateArm() {
	if (armUpMacroPressed) {
		armControlMoveToPos(ARM_UP_POS);
	} else if (armDownMacroPressed) {
		armControlDisable();
		armSetPowerRaw(0);
	} else if (armMiddleMacroPresed) {
		armControlMoveToPos(ARM_MIDDLE_POS);
	}
}

void armSetPowerUnadjusted(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
}

bool armIsDown() {
	return (armPos <= ARM_DOWN_POS);
}

bool armIsUp() {
	return (armPos >= ARM_UP_POS);
}

#endif
