#pragma config(Motor, port2, leftDrive,    tmotorNormal, openLoop)
#pragma config(Motor, port3, rightDrive,   tmotorNormal, openLoop)
#pragma config(Motor, port4, leftSpinner,  tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, rightSpinner, tmotorNormal, openLoop)
#pragma config(Motor, port6, leftArm,      tmotorNormal, openLoop, reversed)
#pragma config(Motor, port7, rightArm,     tmotorNormal, openLoop)
// Add a line to config the pot as "armPot"

#define SPINNER_OUT_PWR 127
#define SPINNER_IN_PWR -127

#define MAX_POWER 127

#define ARM_UP_POS   // Need to be defined
#define ARM_DOWN_POS //

#include "PidLib.c"

void setSpinners(int value) {
	motor[leftSpinner] = value;
	motor[rightSpinner] = value;
}

void setArm(int value) {
	motor[leftArm] = value;
	motor[rightArm] = value;
}

task main()
{
	while (true) {
		// Spinners
		if (vexRT[Btn6D]) {
			setSpinners(SPINNER_IN_PWR);
		} else if (vexRT[Btn6U]) {
			setSpinners(SPINNER_OUT_PWR);
		} else {
			setSpinners(0);
		}

		// Drive
		motor[leftDrive] = vexRT[Ch3];
		motor[rightDrive] = -vexRT[Ch2];

		// Arm
		if (vexRT[Btn5D] && SensorValue[armPot] > ARM_DOWN_POS) {
			setArm(-MAX_POWER);
		} else if (vexRT[Btn5U] && SensorValue[armPot] < ARM_UP_POS) {
			setArm(MAX_POWER);
		} else {
			// Maintain current position via pid
		}
	}
}
