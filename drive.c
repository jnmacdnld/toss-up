#include "motor.c"

void updateDriveTankDrive();
void setDrivePwr(int pwr);
void driveDistance(int d);

void updateDriveTankDrive() {
	setMotorLinear(leftDrive,  vexRT[Ch3]);
	setMotorLinear(rightDrive, vexRT[Ch2]);
}

void updateDriveArcadeDrive() {
	setMotorLinear(leftDrive, vexRT[Ch3] + vexRT[Ch1]);
	setMotorLinear(rightDrive, vexRT[Ch3] - vexRT[Ch1]);
}

void driveDistance(int d) {
	int intial = SensorValue[leftDriveEncoder];
	
	while ( SensorValue[leftDriveEncoder] < (initial + d) )
		setDrivePwr(FULL_PWR);
}

void setDrivePwr(int pwr) {
	motor[leftDrive]  = pwr;
	motor[rightDrive] = pwr;
}