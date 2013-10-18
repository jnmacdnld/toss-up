#ifndef PROFILING_C
#define PROFILING_C
 
getActualMotorSpeedAtSetting(tMotor mtr, int setting);
fillActualSpeedsArr(tMotor mtr, float* actualSpeeds);
fillMotorSettingLut(tMotor mtr, int* motorSettingLut, float* actualSpeeds);
getIdealSpeed(int setting, float* actualSpeeds);

float getActualMotorSpeedAtSetting(tMotor mtr, int setting) {
	int num_samples = 50;
	
	motor[mtr] = setting;
	wait1Msec(1000); // Wait until the motor reached the speed

	int final_pos;
	int initial_pos;
	int s;
	float avg_s;

	for (int i = 0; i < num_samples; i++) {
		initial_pos = nMotorEncoder[mtr];
		wait1Msec(25);
		final_pos = nMotorEncoder[mtr];
		s = abs(final_pos - initial_pos);

		avg_s += s;
	}

	avg_s /= num_samples;

	return avg_s;
}

void fillActualSpeedsArr(tMotor mtr, float* actualSpeeds) {
	for (short s = 0; s <= 127; s++) {
		actualSpeeds[s] = getActualMotorSpeedAtSetting(mtr, s);
	}
}


void fillMotorSettingLut(tMotor mtr, int* motorSettingLut, float* actualSpeeds) {
	float least_diff = 0;
	int best_match = 0;
	float diff = 0;
	
	// Calculate the best power setting to re-map each power setting to
  // so that acceleration is constant when the joystick is moved forward 
	for (short s = 0; s <= 127; s++) {
		least_diff = abs(getIdealSpeed(s) - actualSpeeds[0];
		best_match = 0;
		
		for (short k = 0; k <= 127; k++) {
			diff = abs(getIdealSpeed(s) - actualSpeeds[k]);
			
			// The power setting that gives a speed closest to the speed we want 
			// (the speed that makes the acceleration constant) is the best match
			if (diff < least_diff) { 
				best_match = k;
				least_diff = diff;
			}
		}
		
		motorSettingLut[i] = best_match;
	}
}

void getIdealSpeed(int setting, float* actualSpeeds) {
	float max_speed = actualSpeeds[127];
	float max_setting = 127.0
	
	// An equation in point-slope form with the x1 term moved to the right side
	return (max_speed / max_setting) * (setting - max_setting) + max_speed;
}

 
#endif /* PROFILING_C */
