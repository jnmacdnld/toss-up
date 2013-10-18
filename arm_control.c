#ifndef ARM_CONTROL_C
#define ARM_CONTROL_C

#include "arm.c"
#include "PidLib.c"

typedef enum requestType {
	NONE,
	POSITION,
	POWER
}

struct {
	requestType request_type
	int pos_request;
	int power_request;
} armController;

task ArmControl() {
	pidController* armPid = PidControllerInit(0.0025, 0.0, 0.02, 0.157, armPot);

	while (true) {		
		switch (armController.request_type) {
			case POWER:
				armSetPower(armController.power_request);
				break;
			case POSITION:
				armPid->target_value = pos_request;
				int cmd = PidControllerUpdate(armPid);
				armSetPower(cmd);
				break;
			default:
				break;
		}

		wait1Msec(25);
	}
}

void armControlSetPos(int pos) {
	armController.request_type = POSITION;
	armController.pos_request = pos;
}

void armControlSetPower(int power) {
	armController.request_type = POWER;
	armController.power_request = power;
}

#endif