#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPot,         sensorNone)
#pragma config(Sensor, in2,    gyro,           sensorGyro)
#pragma config(Sensor, in3,    leftFrontLine,  sensorLineFollower)
#pragma config(Sensor, dgtl1,  stashSonar,     sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  ColorJumper,    sensorDigitalIn)
#pragma config(Sensor, dgtl4,  ZoneJumper,     sensorDigitalIn)
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

#include "competition_includes.c"

#include "user_control.c"
#include "motors.c"
#include "motor_luts.c"
#include "auton.c"
#include "lcd.c"
#include "jumpers.c"
#include "Recorder.c"
#include "ArmControl.c"

#include "GyroLib.c"

void pre_auton()
{
  // Stop all running tasks when the mode is switched
  bStopTasksBetweenModes = true;

  MotorLutsInit();
  MotorsInit();
  DriveInit();
  ArmInit();
  AutonInit();
  // DriveInitGyro();
  GyroInit(gyro);

  StartTask(Lcd);
}

task autonomous()
{
  ArmControlReset();

  StartTask(MotorsUpdate);
  StartTask(ArmControl);

  AutonRun();
}

task usercontrol()
{
  StartTask(UserControl);
  StartTask(MotorsUpdate);
  StartTask(Recorder);

  while (true)
    wait1Msec(1000);
}
