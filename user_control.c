#include "drive.c"
#include "intake.c"
#include "arm.c"

int armPotVal;
int leftDriveEncoder;
int rightDriveEncoder;

void userControlLoop() {
	while (true) {
		updateIntake();
		updateDriveTankDrive();
		updateArm();

		armPotVal = SensorValue[armPot]; // For debugging
    leftDriveEncoder = nMotorEncoder[leftDrive];
    rightDriveEncoder = nMotorEncoder[rightDrive];
	}
}
