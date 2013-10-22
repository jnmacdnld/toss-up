#ifndef ARM_CONTROL_C
#define ARM_CONTROL_C

#include "arm.c"
#include "PidLib.c"

pidController* armPid;

task ArmControl() {
	while (true) {
		int cmd = PidControllerUpdate(armPid);
		armSetPowerRaw(cmd);

		wait1Msec(25);
	}
}

void armControlMoveToPos(int pos) {
	armPid->enabled = 1;
	armPid->target_value = pos;
}

void armControlDisable() {
	armPid->enabled = 0;
}

void startArmControl() {
	armPid = PidControllerInit(0.04, 0.0, 0.02, 0.48, armPot);
	StartTask(ArmControl);
}

#endif
