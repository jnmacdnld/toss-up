#ifndef USER_CONTROL
#define USER_CONTROL

// Include drive modules
#include "Drive.c"
#include "ArcadeDrive.c"
#include "TankDrive.c"

// Include intake modules
#include "Intake.c"

// Include lift modules
#include "Lift.c"
#include "LiftControl.c"

// Include gyro library
#include "GyroLib.c"

// Define joystick macros for lift movement
#define LIFT_UP_PRESSED              vexRT[Btn6U]
#define LIFT_DOWN_PRESSED            vexRT[Btn6D]

#define LIFT_UP_PRESET_PRESSED       vexRT[Btn8U]
#define LIFT_DOWN_PRESET_PRESSED     vexRT[Btn8D]

#define LIFT_DOWN_FULL_POWER_PRESSED vexRT[Btn7D]
#define LIFT_UP_FULL_POWER_PRESSED   vexRT[Btn7U]

// Define joystick macros for intake movement
#define INTAKE_IN_PRESSED  vexRT[Btn5U]
#define INTAKE_OUT_PRESSED vexRT[Btn5D]

void UserControlUpdateLift();
void UserControlUpdateIntake();

// Task to handle joystick input from the user
task UserControl()
{
  while (true)
  {
    // Update intake
    UserControlUpdateIntake();

    // Update drive
    ArcadeDriveUpdate();

    // Update lift
    UserControlUpdateLift();

    // Don't hog CPU
    wait1Msec(25);
  }
}

void UserControlUpdateLift()
{
  // Handle lift presets
  if (LIFT_UP_PRESET_PRESSED)
    LiftControlMoveToPosAsync(kLiftUpPos);
  else if (LIFT_DOWN_PRESET_PRESSED)
    LiftControlMoveToPosAsync(kLiftDownPos);

  // Handle manual lift movement
  if (LIFT_DOWN_FULL_POWER_PRESSED)
  {
    LiftSetPower(-kFullPower);
  }
  else if (LIFT_UP_FULL_POWER_PRESSED)
  {
    LiftSetPower(kFullPower);
  }
  else if ( LIFT_UP_PRESSED && !LiftIsUp() )
  {
    // Store the error to move to stash height
    short error = kLiftUpPos - LIFT_POT;

    // Calculate and store the power based on the error and lift P constant
    int power = error * liftKp;

    // Don't let the power exceed the maximum motor power
    if (abs(power) > kFullPower)
      power = kFullPower;

    // Set the lift power 10 more than the calculation so that it reaches the
    // mechanical stop
    LiftSetPower(power + kLiftHoldPower + 10);

    // Disable lift control
    liftControlActive = false;
  }
  else if ( LIFT_DOWN_PRESSED && !LiftIsDown() )
  {
    LiftSetPower(kLiftDownPower);
    liftControlActive = false;
  }
  else if (liftControlActive)
  {
    LiftControlStep();
  }
  else
  {
    LiftHoldPos();
  }
}

void UserControlUpdateIntake()
{
  // Handle fast eject
  if (INTAKE_IN_PRESSED && INTAKE_OUT_PRESSED)
    IntakeSetPower(kIntakeOutFastPower);
  // Handle intake in
  else if (INTAKE_IN_PRESSED)
    IntakeSetPower(kIntakeInPower);
  // Handle eject
  else if (INTAKE_OUT_PRESSED)
  {
    // Eject the buckies slowly if the lift is at stash height and quickly if
    // the lift is not
    if (LIFT_POT > kLiftUpPos - 300 )
      IntakeSetPower(kIntakeOutSlowPower);
    else
      IntakeSetPower(kIntakeOutFastPower);
  }
  else
  {
    IntakeSetPower(0);
  }
}

#endif
