#ifndef TUNING_C
#define TUNING_C

#include "motor.c"

#define SAMPLE_PERIOD 25

// LUT that goes 0 to 100 rpm linearly (however speeds below 20 rpm are not reliable)
// Calculated for left drive motor
// int motorSettingLut[128] = 
// {
// 0, 11, 11, 16, 16, 16, 16, 14, 14, 14, 
// 14, 14, 14, 14, 14, 14, 14, 17, 17, 17, 
// 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 
// 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 
// 19, 19, 20, 20, 20, 21, 21, 21, 21, 21, 
// 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 
// 24, 24, 24, 24, 25, 25, 25, 25, 26, 26, 
// 26, 26, 27, 27, 27, 27, 28, 28, 28, 28, 
// 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 
// 32, 32, 33, 33, 34, 34, 34, 35, 35, 36, 
// 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 
// 42, 43, 43, 44, 45, 45, 46, 47, 47, 48, 
// 49, 50, 51, 52, 53, 54, 55, 56 
// };

int motorSettingLut[128];
float motorSpeeds[128];
// float motorSpeeds[128] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 10.408163232, 13.524489752640001, 16.954163211052798, 23.5278596185884, 27.6389233809432, 31.318086634475996, 34.6824833073834, 37.5048710534538, 42.306221803395594, 45.080816182271995, 48.197536835563795, 50.9384424390378, 54.7432574778828, 57.72751894792499, 60.465776592223804, 62.586868422170994, 64.08336714187199, 66.86840412275579, 68.83737222869999, 71.09613497657399, 74.049470426307, 73.9554793551792, 74.030127314124, 74.10815792611919, 79.08420510407339, 79.64290918391819, 81.7969359627396, 82.987978050765, 84.61894105575, 85.722990797115, 86.96956349720759, 87.8363300760666, 89.2312191022152, 90.4836004757586, 91.12089384106619, 92.51119868355599, 93.3808389868956, 94.01047546447259, 94.6353096461466, 95.6427050510862, 96.58122290522579, 96.5234614258188, 97.74679943210819, 98.0773772371728, 99.0023644791108, 99.55656855897, 100.1033759551794, 100.7265609021648, 100.968615748329, 101.4326361550074, 102.1306871731818, 102.2977152338718, 103.06635808855499, 103.00520630303639, 103.6927534947138, 104.2422241562208, 104.5593325735734, 104.5656731347776, 105.2545749182874, 105.19182746950861, 105.95587466094119, 106.2772802721576, 106.5133006795656, 106.9772024637954, 107.2160812895616, 107.4504448092198, 107.99084276667419, 107.7720685326804, 108.3034014391434, 108.2374894495584, 109.1545519466238, 109.86166801578959, 111.1768197972954, 113.5755761671704, 113.9296794823638, 113.5541093305044, 114.005777696406, 113.708685860622, 114.00886570660019, 113.55568586111158, 113.4700978511814, 113.85103662547259, 113.55252514683599, 113.9292088191, 113.55408637132079, 113.6996590749366, 113.779094023662, 113.627620809861, 113.62459019762579, 114.00718203313619, 113.55565907539739, 113.9292776966508, 113.55408637132079, 113.85272029893659, 114.0882815226726, 113.7103350953106, 113.8558389213756, 113.93528152316219, 113.5542202998918, 114.005777696406, 113.708685860622, 114.00886570660019, 113.8618083091116, 114.0884575430802, 113.9399384109024, 114.16655703262619, 114.17107616526481, 113.8650493805298, 113.93546519663099, 114.0134077984224, 114.09149198184599, 114.0165225943308, 114.01502642086619, 114.09152259409079};

float getActualMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev);
void fillMotorSpeedsArrWithUnadjusted(tMotor mtr, float ticks_per_rev);
void fillMotorSettingLut();
float getIdealSpeed(int setting, float max_speed);
float getAdjustedMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev);

float getAdjustedMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev) {
	return getActualMotorSpeedAtSetting(mtr, motorSettingLut[setting], ticks_per_rev);
}

float getActualMotorSpeedAtSetting(tMotor mtr, int setting, float ticks_per_rev) {
	float to_rpm = 60000.0 / (SAMPLE_PERIOD * ticks_per_rev);
	int num_samples = 50;

	writeDebugStreamLine("Dectected encoder ticks per revolution: %f", ticks_per_rev);

	motor[mtr] = setting;
	wait1Msec(250); // Wait until the motor reached the speed

	int final_pos;
	int initial_pos;
	int s;
	float avg_s;

	for (int i = 0; i < num_samples; i++) {
		initial_pos = nMotorEncoder[mtr];
		wait1Msec(SAMPLE_PERIOD);
		final_pos = nMotorEncoder[mtr];
		s = abs(final_pos - initial_pos);

		avg_s += s;
	}

	avg_s /= num_samples;
	avg_s *= to_rpm;

	return avg_s;
}

void fillMotorSpeedsArrWithUnadjusted(tMotor mtr, float ticks_per_rev) {
	for (short s = 0; s < 128; s++) {
		motorSpeeds[s] = getActualMotorSpeedAtSetting(mtr, s, ticks_per_rev);
		writeDebugStreamLine("speed at power setting %d is about %d rpm", s, (int) motorSpeeds[s]);
	}
}

void fillMotorSpeedsArrWithAdjusted(tMotor mtr, float ticks_per_rev) {
	for (short s = 0; s < 128; s++) {
		float speed = getAdjustedMotorSpeedAtSetting(mtr, s, ticks_per_rev);

		motorSpeeds[s] = speed;

		float ideal_speed = getIdealSpeed(s, 100.0);
		float error = ( (speed - ideal_speed) / speed ) * 100;

		writeDebugStreamLine("adjusted speed at power setting %d is about %d rpm (about %d percent error)", s, (int) speed, (int) error);
	}
}

void fillMotorSettingLut() {
	float least_diff = 0;
	int best_match = 0;
	float diff = 0;

	// Calculate the best power setting to re-map each power setting to
  // so that acceleration is constant when the joystick is moved forward
	for (short s = 0; s <= 127; s++) {
		least_diff = 1000000;
		best_match = 0;

		for (short k = 0; k <= 127; k++) {
			diff = abs(getIdealSpeed(s, 100.0) - motorSpeeds[k]);

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

float getIdealSpeed(int setting, float max_speed) {
	float max_setting = 127.0;
	float low_speed = 25.0;

	// An equation in point-slope form with the x1 term moved to the right side
	// Speed goes linearly from 0 rpm to max_speed over the values 0 to 127
	// return (max_speed / max_setting) * (setting - max_setting) + max_speed;

	// Speed goes linearly from 20 rpm to max_speed over the values 0 to 127
	return ((max_speed - low_speed) / max_setting) * (setting - max_setting) + max_speed;
}

void printMotorSpeedsGraphable() {
	for (int i = 0; i < 128; i++) {
		writeDebugStreamLine("%f", motorSpeeds[i]);
	}

	// for (int i = 0; i < 128; i++) {
	// 	writeDebugStreamLine("%d", i);
	// }

	writeDebugStream("\n\n");
}

void printSettingLut() {
	writeDebugStream("\nint motorSettingLut[128] = \n{\n");

	for (int i = 0; i < 127; i++) {
		writeDebugStream("%d, ", motorSettingLut[i]);

		// Print a line break after every tenth value
	  if ( (i + 1) % 10 == 0)
	  	writeDebugStream("\n");
	}

	writeDebugStream("%d \n};", motorSettingLut[127]);
}


#endif /* TUNING_C */
