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
	armPid->target_value = pos;
}

void armControlDisable() {
	armPid->enabled = 0;
}

void initArmControl() {
	armPid = PidControllerInit(0.003, 0.0, 0.02, 0.23, armPot);
}

#endif
