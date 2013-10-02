#define MAX_POWER 127
#define HALF_POWER 64

#define ARM_UP_POS   0 // Give this an actual value
#define ARM_DOWN_POS 1400

pidController* armPid;

void setArm(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
}

void setArmUp() {
	setArm(MAX_POWER);
}

void setArmDown() {
	setArm(-HALF_POWER);
}

bool armCanMoveDown() {
	return (SensorValue[armPot] > ARM_DOWN_POS);
}

bool armCanMoveUp() {
	return (SensorValue[armPot] < ARM_UP_POS);
}

int lastDesiredPos = 0;

void updateArm() {
	if ( vexRT[Btn5U] /*&& armCanMoveUp()*/ )
		setArmUp();
	else if ( vexRT[Btn5D] && armCanMoveDown() )
		setArmDown();
	else
		if (SensorValue[armPot] < 1400) // If the arm is all the way down, it
			setArm(0);										// doesn't need to be held up
		else	
			setArm(20); // Hold up the arm so it doesn't fall
  }
}
