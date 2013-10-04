#include "PidLib.c"

void updateDrive() {
	motor[leftDrive]  = _LinearizeDrive(vexRT[Ch2]);
	motor[rightDrive] = _LinearizeDrive(vexRT[Ch3]);
}
