#include "Lcd.c"

void allMotorsOff();
void allTasksStop();
void pre_auton();
task autonomous();
task usercontrol();

bool bStopTasksBetweenModes = true;

task main()
{
  // Turn on the LCD backlight
  bLCDBacklight = true;
  
  // Clear the LCD
  LcdClear();

  // Display a startup message
  displayLCDCenteredString(0, "Starting up...");

  // Don't start the robot for two seconds, as the original code did
  wait1Msec(2000);

  // Call the pre_auton funtion
  pre_auton();

  // Main loop
  while (true)
  {
    if (bIfiRobotDisabled)
    {
      // Allow the auton to be set using the LCD when disabled
      StartTask(LcdSetAuton);

      // Stop all motors when disabled
      allMotorsOff();
    }

    // If the robot is disabled, do nothing until it is enabled
    while (bIfiRobotDisabled)
      wait1Msec(25);

    // Stop allowing the autonomous to be set from the LCD
    StopTask(LcdSetAuton);

    // Clear the LCD
    LcdClear();

    // Handle autonomous mode
    if (bIfiAutonomousMode)
    {
      // Clear the LCD
      LcdClear();

      // Start the autonomous task
      StartTask(autonomous);

      // Loop to be run while autonomous is running and the robot is enabled
      while (bIfiAutonomousMode && !bIfiRobotDisabled)
      {
        // If the VEXNET disconnects, power off all of the motors
        if (!bVEXNETActive)
          if (nVexRCReceiveState == vrNoXmiters)
            allMotorsOff();

        // Don't hog CPU
        wait1Msec(25);
      }

      // After autonomous has expired, power off all of the motors
      allMotorsOff();

      // Stop all tasks if the user has set tasks to end between modes
      if(bStopTasksBetweenModes)
        allTasksStop();
    }

    else
    {
      // Clear the LCD
      LcdClear();

      // Display Driver Control to reflect the current mode
      displayLCDCenteredString(0, "Driver Control");

      // Start the user control task
      StartTask(usercontrol);

      // Here we repeat loop waiting for user control to end and (optionally) start
      // of a new competition run
      while (!bIfiAutonomousMode && !bIfiRobotDisabled)
      {
        // If the VEXNET disconnects, turn off the motors
        if (nVexRCReceiveState == vrNoXmiters)
          allMotorsOff();

        // Don't hog CPU
        wait1Msec(25);
      }

      // If the mode is switched from user control, turn of all motors
      allMotorsOff();

      // Stop all tasks if the user has set tasks to end between modes
      if(bStopTasksBetweenModes)
        allTasksStop();
    }
  }
}

void allMotorsOff()
{
  motor[port1] = 0;
  motor[port2] = 0;
  motor[port3] = 0;
  motor[port4] = 0;
  motor[port5] = 0;
  motor[port6] = 0;
  motor[port7] = 0;
  motor[port8] = 0;
#if defined(VEX2)
  motor[port9] = 0;
  motor[port10] = 0;
#endif
}

void allTasksStop()
{
  StopTask(1);
  StopTask(2);
  StopTask(3);
  StopTask(4);
#if defined(VEX2)
  StopTask(5);
  StopTask(6);
  StopTask(7);
  StopTask(8);
  StopTask(9);
  StopTask(10);
  StopTask(11);
  StopTask(12);
  StopTask(13);
  StopTask(14);
  StopTask(15);
  StopTask(16);
  StopTask(17);
  StopTask(18);
  StopTask(19);
#endif
}
