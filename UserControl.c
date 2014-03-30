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

// Define joystick macros
#define ARM_UP_PRESSED              vexRT[Btn6U]
#define ARM_DOWN_PRESSED            vexRT[Btn6D]

#define ARM_UP_PRESET_PRESSED       vexRT[Btn8U]
#define ARM_DOWN_PRESET_PRESSED     vexRT[Btn8D]

#define ARM_DOWN_FULL_POWER_PRESSED vexRT[Btn7D]
#define ARM_UP_FULL_POWER_PRESSED   vexRT[Btn7U]

void UserControlUpdateArm();

// Task to handle joystick input from the user
task UserControl()
{
  while (true)
  {
    IntakeUpdate();
    ArcadeDriveUpdate();
    UserControlUpdateArm();

    wait1Msec(25);
  }
}

void UserControlUpdateArm() {
  if (ARM_UP_PRESET_PRESSED)
    ArmControlMoveToPosAsync(kArmUpPos);
  else if (ARM_DOWN_PRESET_PRESSED)
    ArmControlMoveToPosAsync(kArmDownPos);

  if ( ARM_DOWN_FULL_POWER_PRESSED )
  {
    ArmSetPower(-kFullPower);
  }
  else if ( ARM_UP_FULL_POWER_PRESSED )
  {
    ArmSetPower( kFullPower );
  }
  else if ( ARM_UP_PRESSED && !ArmIsUp() )
  {
    short error = kArmUpPos - ARM_POT;
    int power = error * armKp;

    if (abs(power) > kFullPower)
      power = kFullPower;

    ArmSetPower(power + kArmHoldPower + 10);

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

#endif
