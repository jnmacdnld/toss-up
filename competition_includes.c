//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                       VEX Competition Control Include File
//
// This file provides control over a VEX Competition Match. It should be included in the user's
// program with the following line located near the start of the user's program
//        #include "VEX_Competition_Includes.h"
// The above statement will cause this program to be included in the user's program. There's no
// need to modify this program.
//
// The program displays status information on the new VEX LCD about the competition state. You don't
// need the LCD, the program will work fine whether or not the LCD is actually provisioned.
//
// The status information is still useful without the LCD. The ROBOTC IDE debugger has a "remote screen"
// that contains a copy of the status information on the LCD. YOu can use this to get a view of the
// status of your program. The remote screen is shown with the menu command
//   "Robot -> Debugger Windows -> VEX Remote Screen"
//
// The LCD is 2 lines x 16 characters. There are three display formats to look for:
//
//        State          Description
//
//    ----------------
//   |Disabled        |  The robot is idle. This occurs before both the autonomous and user
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been idle.
//    ----------------
//
//    ----------------
//   |Autonomous      |  The robot is running autonomous code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//
//    ----------------
//   |User Control    |  The robot is running user control code.
//   |Time mm:ss.s    |  control states. The time display is minutes and seconds it has been running.
//    ----------------
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Lcd.c"

void allMotorsOff();
void allTasksStop();
void pre_auton();
task autonomous();
task usercontrol();

bool bStopTasksBetweenModes = true;

static void displayStatusAndTime();

task main()
{
  // Turn on the LCD backlight
  bLCDBacklight = true;
  
  // Clear the LCD
  clearLCDLine(0);
  clearLCDLine(1);

  // Display a startup message
  displayLCDCenteredString(0, "Starting up...");

  // Don't start the robot for two seconds, as the original code did
  wait1Msec(2000);

  // Call the pre_auton funtion
  pre_auton();

  // Main loop
  while (true)
  {
    // If the robot is disabled, allow the auton to be set using the LCD
    if (bIfiRobotDisabled)
      StartTask(LcdSetAuton);

    // If the robot is disabled, do nothing until it is enabled
    while (bIfiRobotDisabled)
      wait1Msec(25);

    // Handle autonomos mode
    if (bIfiAutonomousMode)
    {
      // Clear the LCD
      clearLCDLine(0);
      clearLCDLine(1);

      // Display the current autonomous routine
      LcdUpdateAuton();

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
      clearLCDLine(0);
      clearLCDLine(1);

      // Display User Control to reflect the current mode
      displayLCDCenteredString(0, "User Control");

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

static void UserControlCodePlaceholderForTesting()
{
  // Following code is simply for initial debuggging.
  //
  // It can be safely removed in a real program and removing it will slightly improve the
  // real-time performance of your robot.
  //
  displayStatusAndTime();
  wait1Msec(100);
  ++nTimeXX;
}

static void AutonomousCodePlaceholderForTesting()
{
  // This is where you insert your autonomous code. Because we don't have any, we'll
  // simply display a running count of the time on the VEX LCD.

  while (true)
  {
    displayStatusAndTime();
    wait1Msec(100);
    ++nTimeXX;
  }
}
