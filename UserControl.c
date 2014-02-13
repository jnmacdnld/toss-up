#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "Intake.c"
#include "Arm.c"
#include "arcade_drive.c"
#include "GyroLib.c"

#define ARM_DOWN_PRESSED         vexRT[Btn6D]
#define ARM_UP_PRESSED           vexRT[Btn6U]
#define ARM_UP_PRESET_PRESSED    vexRT[Btn8U]
#define ARM_DOWN_PRESET_PRESSED  vexRT[Btn8D]

#define INTAKE_IN_PRESSED  vexRT[Btn5U]
#define INTAKE_OUT_PRESSED vexRT[Btn5D]

task UserControl()
{
  // Reset the ArmController module because autonomous might've been using it
  ArmControllerReset();

  while (true)
  {
    // Update the intake
    UserControlUpdateIntake();

    // Update the arm
    UserControlUpdateArm();

    // Update the drive using arcade drive
    ArcadeDriveUpdate();

    // Update frequently
    wait1Msec(25);
  }
}

void UserControlUpdateArm()
{
  // Handle arm presets
  if (ARM_UP_PRESET_PRESSED)
    ArmControllerSetTarget(kArmStashHeight);
  else if (ARM_DOWN_PRESET_PRESSED)
    ArmControllerSetTarget(kArmFloorHeight);

  // Handle manual arm movement
  if ( ARM_UP_PRESSED && !ArmIsUp() )
  {
    ArmControllerDisable();
    ArmSetPower(kArmUpPower);
  }
  else if ( ARM_DOWN_PRESSED && !ArmIsDown() )
  {
    ArmControllerDisable();
    ArmSetPower(kArmDownPower);
  }
  else if ( !ArmControllerEnabled() )
  {
    ArmHoldPos();
  }
}

void UserControlUpdateIntake()
{
  // Handle fast eject
  if (INTAKE_IN_PRESSED && INTAKE_OUT_PRESSED)
  {
    IntakeSetPower(kIntakeOutFastPower);
  }
  else if (INTAKE_IN_PRESSED)
  {
    IntakeSetPower(kIntakeInPower);
  }
  else if (INTAKE_OUT_PRESSED)
  {
    if ( ArmAtPreset(kArmStashHeight) )
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
