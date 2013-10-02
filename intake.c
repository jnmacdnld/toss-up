#define INTAKE_OUT_PWR -127
#define INTAKE_IN_PWR   127

void setIntakePwr(int value) {
	motor[leftSpinner] = value;
	motor[rightSpinner] = value;
}

void updateIntake() {
	if (vexRT[Btn6U])
		setIntakePwr(INTAKE_IN_PWR);
	else if (vexRT[Btn6D])
		setIntakePwr(INTAKE_OUT_PWR);
	else
		setIntakePwr(0);
}
