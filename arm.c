#define ARM_UP_POS   3060
#define ARM_DOWN_POS 1400

#define ARM_UP_PWR    MAX_PWR
#define ARM_DOWN_PWR -MAX_PWR / 3
#define ARM_HOLD_PWR  10

#define armPos         SensorValue[armPot]

#define armDownPressed    vexRT[Btn6D]
#define armUpPressed      vexRT[Btn6U]
#define armUpMacroPressed vexRT[Btn7U]
#define armDownMacroPressed vexRT[Btn7D]

int armControlTarget = -1;
int armControlPwr = 0;
bool armControlActive = false;

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
	if ( armIsUp() )
		return;

	setArmPwr(ARM_UP_PWR);
	armControlActive = false;
}

void armDownPressedCb() {
	if ( armIsDown() )
		return;

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
	else
		armControlActive = false;
}

void holdArmPos() {
	if ( armIsDown() ) // Don't try to hold up the arm if it's all the way down
			setArmPwr(0);
	else
		setArmPwr(ARM_HOLD_PWR); // Hold up the arm so it doesn't fall
}

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
