// #include "PidLib.c"

// PidControllerMakeLut();
#include "motor.c"

void updateDrive() {
	//motor[leftDrive]  = _LinearizeDrive(vexRT[Ch2]);
	//motor[rightDrive] = _LinearizeDrive(vexRT[Ch3]);
	setMotor(leftDrive,  vexRT[Ch2]);
	setMotor(rightDrive, vexRt[Ch3]);
}

void setDrivePwr(int pwr) {
	setMotor(leftDrive,  pwr);
	setMotor(rightDrive, pwr);
}

void driveDistance(int d) {
	int intial = SensorValue[leftDriveEncoder];
	
	while ( SensorValue[leftDriveEncoder] < (initial + d) )
		setDrivePwr(MAX_PWR);
}
