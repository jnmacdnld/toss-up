#ifndef INTAKE_C
#define INTAKE_C

#define INTAKE_OUT_PWR -50
#define INTAKE_IN_PWR   127

#define intakeInPressed  vexRT[Btn5U]
#define intakeOutPressed vexRT[Btn5D]

void setIntakePwr(int value) {
	motor[leftIntake] = value;
	motor[rightIntake] = value;
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