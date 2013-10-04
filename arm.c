#define ARM_UP_POS   3060
#define ARM_DOWN_POS 1400

#define ARM_UP_PWR    MAX_PWR
#define ARM_DOWN_PWR -MAX_PWR / 3
#define ARM_HOLD_PWR  20

#define armPos         SensorValue[armPot]
#define armDownPressed vexRT[Btn5D]
#define armUpPressed   vexRT[Btn5U]

bool armUpMacroActive = false;
bool armDownMacroActive = false;

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

void armUpPressed() {
	if ( armIsUp() )
		return;
	
	setArmPwr(ARM_UP_PWR);
	armControlActive = false;
}

void armDownPressed() {
	if ( armIsDown() )
		return;
	
	setArmPwr(ARM_DOWN_PWR);
	armControlActive = false;
}

int armControlTarget = -1;
int armControlPwr = 0;
bool armControlActive = false;

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
	if (/* arm up macro button pressed */) {
		armControlSetTarget(ARM_UP_POS);
	else if (/*arm down macro button pressed */) {
		armControlSetTarget(ARM_DOWN_POS);
	
	if (armUpPressed)
		armUpPressed();
	else if (armDownPressed)
		armDownPressed();
	else if (armControlActive)
		armControlStep();
	else
		holdArmPos();
}
