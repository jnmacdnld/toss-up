// #include "PidLib.c"

// PidControllerMakeLut();

void updateDrive() {
	//motor[leftDrive]  = _LinearizeDrive(vexRT[Ch2]);
	//motor[rightDrive] = _LinearizeDrive(vexRT[Ch3]);

	motor[leftDrive]  = vexRT[Ch2];
	motor[rightDrive] = vexRT[Ch3];
}

void setDrivePwr(int pwr) {
	motor[leftDrive]  = pwr;
	motor[rightDrive] = pwr;
}

void driveDistance(int d) {
	int intial = SensorValue[leftDriveEncoder];
	
	while ( SensorValue[leftDriveEncoder] < (initial + d) )
		setDrivePwr(MAX_PWR);
}
