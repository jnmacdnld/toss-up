#define ARM_UP_POS   3060
#define ARM_DOWN_POS 1400

#define ARM_UP_PWR    MAX_PWR
#define ARM_DOWN_PWR -(MAX_PWR / 3)

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

void updateArm() {
	if ( vexRT[Btn5U] && !armIsUp() )
		setArmPwr(ARM_UP_PWR);
	else if ( vexRT[Btn5D] && !armIsDown() )
		setArmPwr(ARM_DOWN_PWR);
	else
		if ( armIsDown() ) // Don't try to hold up the arm if it's all the way down
			setArmPwr(0);
		else
			setArmPwr(20); // Hold up the arm so it doesn't fall
}
