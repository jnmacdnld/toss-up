#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  touch,          sensorTouch)
#pragma config(Sensor, I2C_1,  backRightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  backLeftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           middleLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           backLeftDrive, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           frontLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port5,           leftIntake,    tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port6,           backRightDrive, tmotorVex393HighSpeed, openLoop, reversed, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port7,           frontRightDrive, tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port8,           rightArm,      tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port9,           rightIntake,   tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port10,          middleRightDrive, tmotorVex393HighSpeed, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"

#include "user_control.c"
#include "motor_luts.c"
#include "auton.c"

#include "GyroLib.c"

void pre_auton() {
  bStopTasksBetweenModes = true;

  initMotorLuts();
  initMotors();
  initDrive();

  initJoystickLuts();

  GyroInit(gyro);
}

task autonomous() {
	StartTask(updateMotors);
	GyroReinit();

  AutonBlueMiddleZone();
}

task usercontrol() {
	GyroReinit();
  StartTask(userControl);
  StartTask(updateMotors);

  while(true)
    wait1Msec(1000);
}
