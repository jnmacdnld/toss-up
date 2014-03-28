#ifndef TUNING_C
#define TUNING_C

#include "Motors.c"

#define kSamplePeriod 1000
#define kNumDriveMotorsPerSide 3

#define PAUSE_PRESSED vexRT[Btn6D]
#define CONTINUE_PRESSED vexRT[Btn6U]

int motorSettingLut[128];
float motorSpeeds[128];

float GetActualMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev);
void FillMotorSpeedsArrWithUnadjusted(tMotor mtr, float ticks_per_rev);
void FillMotorsSettingLut();
float GetIdealSpeed(int setting, float max_speed);
float GetAdjustedMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev);
void WaitForContinue();

float max_motor_speed = 0.0;

float GetAdjustedMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev) {
	return GetActualMotorSpeedAtSetting(mtr, motorSettingLut[setting], ticks_per_rev);
}

float GetActualMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev) {
	// If pause is pressed, wait until continue is pressed in order to continue
	if (PAUSE_PRESSED)
		WaitForContinue();

	// Declare the variables that will be used
	int final_pos;
	int initial_pos;
	int speed;

	// Define a constant to convert ticks per sample period to RPM
	float to_rpm = 60000.0 / (kSamplePeriod * ticks_per_rev);

	// Set the motor to the requested speed
	motor[mtr] = setting;

	// Wait until the motor has reached the speed
	wait1Msec(250);

	// Record the initial position of the motor
	initial_pos = nMotorEncoder[mtr];

	// Wait for the sample period
	wait1Msec(kSamplePeriod);
	
	// Record the position of the motor after the sample period has passed
	final_pos = nMotorEncoder[mtr];

	// Caculate the speed
	speed = abs(final_pos - initial_pos);

	// Convert the speed to RPM
	speed *= to_rpm;

	return speed;
}

void FillMotorSpeedsArrWithUnadjusted(tMotor mtr, float ticks_per_rev) {
	// Find the actual speed of the motor at each power setting

	// Iterate through each power setting
	for (short s = 0; s < 128; s++) {
		// Calculate the actual speed of the motor and record it in the motorSpeeds array
		motorSpeeds[s] = GetActualMotorSpeedAtSetting(mtr, s, ticks_per_rev);

		// Print the calculated speed to the debug stream
		writeDebugStreamLine("speed at power setting %d is about %d rpm", s, (int) motorSpeeds[s]);
	}
}

void FillMotorSpeedsArrWithAdjusted(tMotor mtr, float ticks_per_rev) {
	for (short s = 0; s < 128; s++) {
		float speed = GetAdjustedMotorSpeedAtSetting(mtr, s, ticks_per_rev);

		motorSpeeds[s] = speed;

		float ideal_speed = GetIdealSpeed(s, max_motor_speed);
		float error = ( (speed - ideal_speed) / speed ) * 100;

		writeDebugStreamLine("adjusted speed at power setting %d is about %d rpm (about %d percent error)", s, (int) speed, (int) error);
	}
}

void FillMotorsSettingLut() {
	// Define the variables that will be used
	float least_diff = 0;
	int best_match = 0;
	float diff = 0;

	// Calculate the best power setting to re-map each power setting so that 
	// motor speed is linearly related to power settings
	for (short s = 0; s <= 127; s++) {
		least_diff = 1000000;
		best_match = 0;

		for (short k = 0; k <= 127; k++) {
			diff = abs(GetIdealSpeed(s, max_motor_speed) - motorSpeeds[k]);

			// The power setting that gives a speed closest to the speed we want
			// (the speed that makes the acceleration constant) is the best match
			if (diff < least_diff) {
				best_match = k;
				least_diff = diff;
			}
		}

		motorSettingLut[s] = best_match;
	}
}

float GetIdealSpeed(int setting, float max_speed) {
	float max_setting = 127.0;
	float low_speed = 0.0;

	// An equation in point-slope form with the x1 term moved to the right side
	// Speed goes linearly from 0 rpm to max_speed over the values 0 to 127
	// return (max_speed / max_setting) * (setting - max_setting) + max_speed;

	// Speed goes linearly from 0 rpm to max_speed over the values 0 to 127
	return ((max_speed - low_speed) / max_setting) * (setting - max_setting) + max_speed;
}

void PrintMotorSpeedsGraphable() {
	for (int i = 0; i < 128; i++) {
		writeDebugStreamLine("%f", motorSpeeds[i]);
	}

	// for (int i = 0; i < 128; i++) {
	// 	writeDebugStreamLine("%d", i);
	// }

	writeDebugStream("\n\n");
}

void PrintSettingLut() {
	writeDebugStream("\nint motorSettingLut[128] = \n{\n");

	for (int i = 0; i < 127; i++) {
		writeDebugStream("%d, ", motorSettingLut[i]);

		// Print a line break after every tenth value
	  if ( (i + 1) % 10 == 0)
	  	writeDebugStream("\n");
	}

	writeDebugStream("%d \n};", motorSettingLut[127]);
}

void TuneMotor(tMotor _motor, float ticks_per_rev) {
	FillMotorSpeedsArrWithUnadjusted(_motor, ticks_per_rev);

  wait1Msec(1000);

  writeDebugStreamLine("Unadjusted motor speed data:");
  PrintMotorSpeedsGraphable();

  FillMotorsSettingLut();
  FillMotorSpeedsArrWithAdjusted(_motor, ticks_per_rev);

  wait1Msec(1000);

  writeDebugStreamLine("Adjusted motor speed data:");
  PrintMotorSpeedsGraphable();

  PrintSettingLut();
}

// MESSY

float GetDriveSpeedAtSetting(tMotor motor1, tMotor motor2, tMotor motor3, int setting) {
	float ticks_per_rev = 392.0;

	int final_pos;
	int initial_pos;
	int speed;
	float to_rpm = 60000.0 / (kSamplePeriod * ticks_per_rev);

	motor[motor1] = setting;
	motor[motor2] = setting;
	motor[motor3] = setting;
	wait1Msec(1000); // Wait until the motors have reached the speed

	initial_pos = nMotorEncoder[motor1];
	wait1Msec(kSamplePeriod);
	final_pos = nMotorEncoder[motor1];
	speed = abs(final_pos - initial_pos);

	speed *= to_rpm;

	motor[motor1] = 0;
	motor[motor2] = 0;
	motor[motor3] = 0;

	return speed;
}

float GetLeftDriveSpeedAtSetting(int setting) {
	return GetDriveSpeedAtSetting(backLeftDrive, middleLeftDrive, frontLeftDrive, setting);
}

float GetRightDriveSpeedAtSetting(int setting) {
	return GetDriveSpeedAtSetting(backRightDrive, middleRightDrive, frontRightDrive, setting);
}

void FillMotorSpeedsArrWithUnadjustedDrive(tMotor motor1, tMotor motor2, tMotor motor3) {
	for (short s = 0; s < 128; s++) {
		motorSpeeds[s] = GetDriveSpeedAtSetting(motor1, motor2, motor3, s);
		writeDebugStreamLine("drive speed at power setting %d is about %d rpm", s, (int) motorSpeeds[s]);
	}

	motor[motor1] = 0;
	motor[motor2] = 0;
	motor[motor3] = 0;
}

void TuneDriveSide(tMotor motor1, tMotor motor2, tMotor motor3) {
	FillMotorSpeedsArrWithUnadjustedDrive(motor1, motor2, motor3);

  wait1Msec(1000);

  writeDebugStreamLine("Unadjusted motor speed data:");
  PrintMotorSpeedsGraphable();

  FillMotorsSettingLut();

  PrintSettingLut();
}

void WaitForContinue() {
	writeDebugStreamLine("Paused. Press button 6U to continue.");
	while (!CONTINUE_PRESSED) wait1Msec(25);
}

#endif /* TUNING_C */
