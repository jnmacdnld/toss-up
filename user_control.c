#ifndef USER_CONTROL_C
#define USER_CONTROL_C

#include "drive.c"
#include "intake.c"
#include "arm.c"
#include "arcade_drive.c"
#include "GyroLib.c"

#define ARM_DOWN_PRESSED         vexRT[Btn6D]
#define ARM_UP_PRESSED           vexRT[Btn6U]
#define ARM_UP_PRESET_PRESSED    vexRT[Btn8U]
#define ARM_DOWN_PRESET_PRESSED  vexRT[Btn8D]

task UserControl()
{
  ArmControllerReset();

  while (true)
  {
    IntakeUpdate();
    ArcadeDriveUpdate();
    UserControlUpdateArm();

    wait1Msec(25);
  }
}

void UserControlUpdateArm()
{
  if (ARM_UP_PRESET_PRESSED)
    ArmControllerSetTarget(kArmStashHeight);
  else if (ARM_DOWN_PRESET_PRESSED)
    ArmControllerSetTarget(kArmFloorHeight);

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

#endif
