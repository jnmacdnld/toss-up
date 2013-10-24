#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"

int armPotVal;					// FIXME: move to another task in another file
int leftDriveEncoder;		//
int rightDriveEncoder;	//

task UserControl() {
	while (true) {
		updateIntake();
		updateDriveTankDrive();
		updateArm();

		armPotVal = SensorValue[armPot];              	// FIXME: move to another task in another file
    leftDriveEncoder = nMotorEncoder[leftDrive];		//
    rightDriveEncoder = nMotorEncoder[rightDrive];	//
    
    wait1Msec(25);
	}
}

#endif
