#ifndef ARM_CONTROL
#define ARM_CONTROL

void armControlMoveToPos(int pos);
void armControlDisable();

#include "arm.c"
#include "PidLib.c"

pidController* armPid;
bool armControlEnabled = false;

void armControlEnable();

task ArmControl() {
	while (true) {
		if (armControlEnabled) {
			int cmd = PidControllerUpdate(armPid);
			armSetPowerUnadjusted(cmd);
		}

		wait1Msec(25);
	}
}

void armControlMoveToPos(int pos) {
	armPid->enabled = 1;
	armPid->target_value = pos;
}

void armControlStart() {
	armPid = PidControllerInit(0.001682, 0.0, 0.00, 0.48, armPot);
	armControlEnable();
	StartTask(ArmControl);
}

void armControlDisable() {
	armControlEnabled = false;
}

void armControlEnable() {
	armControlEnabled = true;
}

#endif
