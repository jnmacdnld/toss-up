#define MAX_POWER 127

#define ARM_UP_POS   // Need to be defined
#define ARM_DOWN_POS //

#include "PidLib.c"



void setArm(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
}

void setArmUp() {
	setArm(MAX_POWER);
}

void setArmDown() {
	setArm(-MAX_POWER);
}

bool armCanMoveDown() {
	return SensorValue[armPot] > ARM_DOWN_POS;
}

bool armCanMoveUp() {
	return SensorValue[armPot] < ARM_UP_POS;
}

void updateArm() {
		if ( vexRT[Btn5D] && armCanMoveDown() ) {
		SetArmDown();
		lastDesiredPos = SensorValue[armPot];
	} else if ( vexRT[Btn5U] && armCanMoveUp() ) {
		SetArmUp();
		lastDesiredPos = SensorValue[armPot]; 
	} else {
		// Don't let the arm fall

		// The target is the position just before the driver stopped moving the arm
		armPid->target_value = lastDesiredPos;

		// update pid control
    PidControllerUpdate(armPid);  
    
    // Send command to arm
    setArm(arm_pid->drive_cmd);
  }
}