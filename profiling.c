void profileMotorAtSetting(tMotor mtr, int setting) {
	motor[mtr] = setting;
	wait1Msec(1000);

	int last_sample;
	int v;
	float avg;

	for (int i = 0; i < 50; i++) {
		last_sample = nMotorEncoder[mtr];

		wait1Msec(25);

		v = nMotorEncoder[mtr] - last_sample;

		avg += v;
	}

	avg /= 50.0;

	writeDebugStreamLine("%f", avg);
}

	//motor[leftDrive] = 75;
	//motor[rightDrive] = 127;

	//int last_sample_right;
	//int last_sample_left;

	//int left_v;
	//int right_v;

	//for (int i = 0; i < 50; i++) {
	//	last_sample_left = nMotorEncoder[leftDrive];
	//	last_sample_right = nMotorEncoder[rightDrive];

	//	wait1Msec(500);

	//	left_v = nMotorEncoder[leftDrive] - last_sample_left;
	//	right_v = nMotorEncoder[rightDrive] - last_sample_right;

	//	left_avg += left_v;
	//	right_avg += right_v;
	//}

	//left_avg /= 50.0;
	//right_avg /= 50.0;
