#define SPINNER_OUT_PWR 127
#define SPINNER_IN_PWR -127

void setSpinners(int value) {
	motor[leftSpinner] = value;
	motor[rightSpinner] = value;
}

void updateSpinners() {
	if (vexRT[Btn6D])
			setSpinners(SPINNER_IN_PWR);
		else if (vexRT[Btn6U])
			setSpinners(SPINNER_OUT_PWR);
		else
			setSpinners(0);
}