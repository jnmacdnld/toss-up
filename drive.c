#include "motor.c"
#include "PidLib.c"

void updateDriveTankDrive();
void setDrivePwr(int pwr);
//void driveDistanceInches(int d);

void updateDriveTankDrive() {
	setMotorLinear(leftDrive,  vexRT[Ch3]);
	setMotorLinear(rightDrive, vexRT[Ch2]);
}

void updateDriveArcadeDrive() {
	setMotorLinear(leftDrive, vexRT[Ch3] + vexRT[Ch1]);
	setMotorLinear(rightDrive, vexRT[Ch3] - vexRT[Ch1]);
}

// void driveDistanceInches(int d) {
// 	int initial = nMotorEncoder[leftDrive];
//   int ticks = d * ENCODER_TICKS_PER_INCH;

// 	while ( nMotorEncoder[leftDrive] < (initial + ticks) )
// 		setDrivePwr(FULL_PWR);
//   setDrivePwr(0);
// }

//void driveDistanceInches(int d) {
//  int initial = nMotorEncoder[leftDrive];
//  int ticks = d * ENCODER_TICKS_PER_INCH;
//  int target = initial + ticks;

//  //drivePid->enabled = 1;
//  drivePid->target_value = target;

//  while (true) {
//  	int motor_cmd = PidControllerUpdate(drivePid);
//    setDrivePwr(motor_cmd);
//	}
//}

void setDrivePwr(int pwr) {
	int left_pwr = (int) (0.9166 * pwr);

	motor[leftDrive]  = left_pwr;
	motor[rightDrive] = pwr;
}
