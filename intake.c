#ifndef INTAKE_C
#define INTAKE_C

#include "motor.c"
#include "arm.c"

#define INTAKE_OUT_SLOW_PWR -40
#define INTAKE_OUT_FAST_PWR -127
#define INTAKE_IN_PWR   127

#define intakeInPressed  vexRT[Btn5U]
#define intakeOutPressed vexRT[Btn5D]

void intakeSetPower(int value) {
	setMotor(leftIntake, value);
	setMotor(rightIntake, value);
}

void updateIntake() {
	if (intakeInPressed) 
		intakeSetPower(INTAKE_IN_PWR);
	else if (intakeOutPressed) {
		if (armPos > ARM_UP_POS - 300 )
			intakeSetPower(INTAKE_OUT_SLOW_PWR);
		else
			intakeSetPower(INTAKE_OUT_FAST_PWR);
  } else
		intakeSetPower(0);
}

#endif
