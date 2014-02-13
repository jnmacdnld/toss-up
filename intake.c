#ifndef INTAKE_C
#define INTAKE_C

#include "motors.c"
#include "Arm.c"

#define kIntakeOutSlowPower -40
#define kIntakeOutFastPower -127
#define kIntakeInPower   127

void IntakeSetPower(short power) {
	MotorsSet(leftIntake, power);
	MotorsSet(rightIntake, power);
}

#endif
