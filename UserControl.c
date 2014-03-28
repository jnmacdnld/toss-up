#ifndef USER_CONTROL
#define USER_CONTROL

#include "Drive.c"
#include "Intake.c"
#include "Arm.c"
#include "ArcadeDrive.c"
#include "GyroLib.c"
#include "TankDrive.c"

task UserControl()
{
  while (true)
  {
    IntakeUpdate();
    ArcadeDriveUpdate();
    ArmUpdate();

    wait1Msec(25);
  }
}

#endif
