#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

#include "user_control.c"

void pre_autonomous() {
 
}

task autonomous() {
	AutonomousCodePlaceholderForTesting(); 
}

task usercontrol() {
	userControlLoop();
}