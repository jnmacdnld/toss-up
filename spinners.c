#pragma config(Motor,  port2,           leftSpinner,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           rightSpinner,     tmotorNormal, openLoop)

#define SPINNER_OUT_PWR  127
#define SPINNER_IN_PWR  -127

void setSpinnersIn() {
	motor[leftSpinner]  = SPINNER_IN_PWR;
	motor[rightSpinner] = SPINNER_IN_PWR;
}

void setSpinnersOut() {
	motor[leftSpinner]  = SPINNER_OUT_PWR;
	motor[rightSpinner] = SPINNER_OUT_PWR;
}

void setSpinnersIdle() {
	motor[leftSpinner]  = 0;
	motor[rightSpinner] = 0;
}

task main()
{
	wait1Msec(2000);

	while (true) {
		if (vexRT[Btn5U]) {
			setSpinnersIn();
		} else if (vexRT[Btn5D]) {
			setSpinnersOut();
		} else {
			setSpinnersIdle();
		}
	}
}
