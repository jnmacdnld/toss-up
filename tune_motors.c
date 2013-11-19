#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPot,         sensorPotentiometer)
#pragma config(Sensor, dgtl3,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  ,               sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  touch,          sensorTouch)
#pragma config(Sensor, I2C_1,  backRightDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  backLeftDriveEncoder, sensorQuadEncoderOnI2CPort,    , AutoAssign)
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

#include "tuning.c"
#include "motor.c"
#include "drive.c"

task main() {
  float left_drive_top_speed = getLeftDriveSpeedAtSetting(FULL_POWER);
  driveSetPower(0);
 	while (!SensorValue[touch]) wait1Msec(25);

  float right_drive_top_speed = getRightDriveSpeedAtSetting(FULL_POWER);
  driveSetPower(0);
  while (!SensorValue[touch]) wait1Msec(25);

  writeDebugStreamLine("left drive top speed: %d", left_drive_top_speed);
  writeDebugStreamLine("right drive top speed: %d", right_drive_top_speed);

  if (left_drive_top_speed < right_drive_top_speed)
    max_motor_speed = left_drive_top_speed;
  else
    max_motor_speed = right_drive_top_speed;

  writeDebugStreamLine("slower drive top speed: %d", max_motor_speed);

  tuneDrive(backLeftDrive, middleLeftDrive, frontLeftDrive);

  while (!SensorValue[touch]) wait1Msec(25);

  tuneDrive(backRightDrive, middleRightDrive, frontRightDrive);
}
