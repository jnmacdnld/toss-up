#include "drive.c"
#include "intake.c"
#include "arm.c"

void userControlLoop() {
	int armPotVal;
	
	while (true) {
		updateIntake();
		updateDriveTankDrive();
		updateArm();

		armPotVal = SensorValue[armPot]; // For debugging
	}
}