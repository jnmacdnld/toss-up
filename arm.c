#define ARM_UP_POS   3060
#define ARM_DOWN_POS 1400

#define ARM_UP_PWR    MAX_PWR
#define ARM_DOWN_PWR -MAX_PWR / 3
#define ARM_HOLD_PWR  20

bool armUpMacroActive = false;
bool armDownMacroActive = false;

void setArmPwr(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
}

bool armIsDown() {
	return (SensorValue[armPot] <= ARM_DOWN_POS);
}

bool armIsUp() {
	return (SensorValue[armPot] >= ARM_UP_POS);
}

void armUpRequested() {
	if ( armIsUp() )
		return;
	
	setArmPwr(ARM_UP_PWR);
	resetMacros();
}

void armDownRequested() {
	if ( armIsDown() )
		return;
	
	setArmPwr(ARM_DOWN_PWR);
	resetMacros();
}

void stepArmUpMacro() {
	if ( !armIsUp() )
		setArm(ARM_UP_PWR);
	else
		armUpMacroActive = false;
}

void stepArmDownMacro() {
	if ( !armIsDown() )
		setArm(ARM_DOWN_PWR);
	else
		armDownMacroActive = false;
}

void holdArmPos() {
	if ( armIsDown() ) // Don't try to hold up the arm if it's all the way down
			setArmPwr(0);
	else
		setArmPwr(ARM_HOLD_PWR); // Hold up the arm so it doesn't fall
}

void resetMacros() {
	armUpMacroActive = false;
	armDownMacroActive = false;
}

void updateArm() {
	if (/* arm up macro button pressed */ && !armUpMacroActive)
		armUpMacroActive = true;
	else if (/*arm down macro button pressed */ && !armDownMacroActive)
		armDownMacroActive = true;
	
	if (vexRT[Btn5U])
		armUpRequested();
	else if (vexRT[Btn5D])
		armDownRequested();
	else if (armUpMacroActive)
		stepArmUpMacro();
	else if (armDownMacroActive)
		stepArmDownActive();
	else
		holdArmPos();
}
