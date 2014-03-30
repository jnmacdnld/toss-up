#ifndef INTAKE_C
#define INTAKE_C

#include "Motors.c"
#include "Lift.c"

#define kIntakeOutSlowPower -50
#define kIntakeOutFastPower -127
#define kIntakeInPower   127

void IntakeSetPower(int value) {
	MotorsSet(leftIntake, value);
	MotorsSet(rightIntake, value);
}

void IntakeSetSweepLeft() {
	MotorsSet(leftIntake, kIntakeOutFastPower);
	MotorsSet(rightIntake, kIntakeInPower);
}

void IntakeSetSweepRight() {
	MotorsSet(leftIntake, kIntakeInPower);
	MotorsSet(rightIntake, kIntakeOutFastPower);
}

#endif
