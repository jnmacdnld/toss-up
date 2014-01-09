#ifndef INTAKE_C
#define INTAKE_C

#include "motor.c"
#include "arm.c"

#define kIntakeOutSlowPower -40
#define kIntakeOutFastPower -127
#define kIntakeInPower   127

#define intakeInPressed  vexRT[Btn5U]
#define intakeOutPressed vexRT[Btn5D]

bool intakeInHasBeenPressed = false;

void IntakeSetPower(int value) {
	MotorSet(leftIntake, value);
	MotorSet(rightIntake, value);
}

void IntakeUpdate() {
	if (intakeInPressed && intakeOutPressed)
		IntakeSetPower(kIntakeOutFastPower);
	else if (intakeInPressed) {
		intakeInHasBeenPressed = true;
		IntakeSetPower(kIntakeInPower);
	} else if (intakeOutPressed) {
		if (armPos > kArmUpPos - 300 )
			IntakeSetPower(kIntakeOutSlowPower);
		else
			IntakeSetPower(kIntakeOutFastPower);
  } else if (intakeInHasBeenPressed)
		IntakeSetPower(kIntakeInPower);
	else
		IntakeSetPower(0);
}

#endif
