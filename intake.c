#ifndef INTAKE_C
#define INTAKE_C

#include "Motors.c"
#include "Arm.c"

#define kIntakeOutSlowPower -50
#define kIntakeOutFastPower -127
#define kIntakeInPower   127

#define intakeInPressed  vexRT[Btn5U]
#define intakeOutPressed vexRT[Btn5D]

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

void IntakeUpdate() {
	if (intakeInPressed && intakeOutPressed)
		IntakeSetPower(kIntakeOutFastPower);
	else if (intakeInPressed)
		IntakeSetPower(kIntakeInPower);
	else if (intakeOutPressed) {
		if (armPos > kArmUpPos - 300 )
			IntakeSetPower(kIntakeOutSlowPower);
		else
			IntakeSetPower(kIntakeOutFastPower);
	} else
		IntakeSetPower(0);
}

#endif
