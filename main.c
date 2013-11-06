#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  rightBackDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  leftBackDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port1,           middleLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port2,           backLeftDrive, tmotorVex393HighSpeed, openLoop, encoder, encoderPort, I2C_2, 1000)
#pragma config(Motor,  port3,           frontLeftDrive, tmotorVex393HighSpeed, openLoop)
#pragma config(Motor,  port4,           leftArm,       tmotorVex393, openLoop)
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
#include "SmartMotorLib.c"

void pre_auton() {
  bStopTasksBetweenModes = true;

  InitMotorLuts();

  // Initialize the Smart Motor Library
  SmartMotorsInit();
  // Limit current based on default motor current threshold
  //SmartMotorCurrentMonitorEnable();

  // Use 1 encoder for each side of the drive
  SmartMotorLinkMotors(backLeftDrive, frontLeftDrive);
  SmartMotorLinkMotors(backLeftDrive, middleLeftDrive);
  SmartMotorLinkMotors(backRightDrive, frontRightDrive);
  SmartMotorLinkMotors(backRightDrive, middleRightDrive);

  // Run smart motors
  SmartMotorRun();
}

task autonomous() {
  AutonomousCodePlaceholderForTesting();
}

task usercontrol() {
  userControlLoop();
}
