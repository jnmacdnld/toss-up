#ifndef INTAKE_C
#define INTAKE_C

#include "motor.c"

#define INTAKE_OUT_PWR -40
#define INTAKE_IN_PWR   127

#define intakeInPressed  vexRT[Btn5U]
#define intakeOutPressed vexRT[Btn5D]

void setIntakePwr(int value) {
	SetMotor(leftIntake, value);
	SetMotor(rightIntake, value);
}

void updateIntake() {
	if (intakeInPressed)
		setIntakePwr(INTAKE_IN_PWR);
	else if (intakeOutPressed)
		setIntakePwr(INTAKE_OUT_PWR);
	else
		setIntakePwr(0);
}

#endif
