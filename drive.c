void updateDrive() {
	motor[leftDrive]  =  vexRT[Ch3];
	motor[rightDrive] = -vexRT[Ch2];
}