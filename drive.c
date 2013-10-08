#include "PidLib.c"

PidControllerMakeLut();

void updateDrive() {
	//motor[leftDrive]  = _LinearizeDrive(vexRT[Ch2]);
	//motor[rightDrive] = _LinearizeDrive(vexRT[Ch3]);

	motor[leftDrive]  = vexRT[Ch2];
	motor[rightDrive] = vexRT[Ch3];
}
