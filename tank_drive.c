#pragma config(Motor,  port2,           leftDrive,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           rightDrive,     tmotorNormal, openLoop)

task main()
{
	wait1Msec(2000);

	while (true) {
		leftDrive = vexRT[Ch3];
		rightDrive = vexRT[Ch2];
	}
}
