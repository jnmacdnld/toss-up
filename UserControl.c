#ifndef USER_CONTROL
#define USER_CONTROL

// Include drive modules
#include "Drive.c"
#include "ArcadeDrive.c"
#include "TankDrive.c"

// Include intake modules
#include "Intake.c"

// Include arm modules
#include "Arm.c"
#include "ArmControl.c"

// Include gyro library
#include "GyroLib.c"

// Define joystick macros for arm movement
#define ARM_UP_PRESSED              vexRT[Btn6U]
#define ARM_DOWN_PRESSED            vexRT[Btn6D]

#define ARM_UP_PRESET_PRESSED       vexRT[Btn8U]
#define ARM_DOWN_PRESET_PRESSED     vexRT[Btn8D]

#define ARM_DOWN_FULL_POWER_PRESSED vexRT[Btn7D]
#define ARM_UP_FULL_POWER_PRESSED   vexRT[Btn7U]

// Define joystick macros for intake movement
#define INTAKE_IN_PRESSED  vexRT[Btn5U]
#define INTAKE_OUT_PRESSED vexRT[Btn5D]

void UserControlUpdateArm();
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

    // Update arm
    UserControlUpdateArm();

    // Don't hog CPU
    wait1Msec(25);
  }
}

void UserControlUpdateArm()
{
  // Handle arm presets
  if (ARM_UP_PRESET_PRESSED)
    ArmControlMoveToPosAsync(kArmUpPos);
  else if (ARM_DOWN_PRESET_PRESSED)
    ArmControlMoveToPosAsync(kArmDownPos);

  // Handle manual arm movement
  if (ARM_DOWN_FULL_POWER_PRESSED)
  {
    ArmSetPower(-kFullPower);
  }
  else if (ARM_UP_FULL_POWER_PRESSED)
  {
    ArmSetPower(kFullPower);
  }
  else if ( ARM_UP_PRESSED && !ArmIsUp() )
  {
    // Store the error to move to stash height
    short error = kArmUpPos - ARM_POT;

    // Calculate and store the power based on the error and arm P constant
    int power = error * armKp;

    // Don't let the power exceed the maximum motor power
    if (abs(power) > kFullPower)
      power = kFullPower;

    // Set the arm power 10 more than the calculation so that it reaches the
    // mechanical stop
    ArmSetPower(power + kArmHoldPower + 10);

    // Disable arm control
    armControlActive = false;
  }
  else if ( ARM_DOWN_PRESSED && !ArmIsDown() )
  {
    ArmSetPower(kArmDownPower);
    armControlActive = false;
  }
  else if (armControlActive)
  {
    ArmControlStep();
  }
  else
  {
    ArmHoldPos();
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
    // Eject the buckies slowly if the arm is at stash height and quickly if
    // the arm is not
    if (ARM_POT > kArmUpPos - 300 )
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
