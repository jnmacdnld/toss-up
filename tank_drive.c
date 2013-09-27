#pragma config(Motor,  port2,           leftDrive,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           rightDrive,     tmotorNormal, openLoop)

task main()
{
	while (true) {
		motor[leftDrive] = vexRT[Ch3];
		motor[rightDrive] = -vexRT[Ch2];
	}
}
