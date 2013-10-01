#pragma config(Motor, port2, leftDrive,    tmotorNormal, openLoop)
#pragma config(Motor, port3, rightDrive,   tmotorNormal, openLoop)
#pragma config(Motor, port4, leftSpinner,  tmotorNormal, openLoop, reversed)
#pragma config(Motor, port5, rightSpinner, tmotorNormal, openLoop)
#pragma config(Motor, port6, leftArm,      tmotorNormal, openLoop, reversed)
#pragma config(Motor, port7, rightArm,     tmotorNormal, openLoop)
// Add a line to config the pot as "armPot"

task main() {
	int lastDesiredPos = SensorValue[armPot];

	// Pass sensical values to this
	pidController* armPid = PidControllerInit(/*float Kp, float Ki, float Kd, float Kbias, tSensors port*/);

	while (true) {
		updateSpinners();
		updateDrive();

		// Arm
		updateArm();
}
