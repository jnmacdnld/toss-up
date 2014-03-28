#ifndef TANK_DRIVE
#define TANK_DRIVE

#include "Joystick.c"
#include "Drive.c"

void TankDriveUpdate()
{
  // Read the joystick
  short left_stick = JoystickGet(kLeftStickYAxis);
  short right_stick = JoystickGet(kRightStickYAxis);

  // If the stick values are close, the driver is probably trying to move straight
  if ( abs(right_stick - left_stick) < 30 )
    left_stick = right_stick;

  // Set the drive power
  DriveSetLeft(left_stick);
  DriveSetRight(right_stick);
}
 
#endif /* TANK_DRIVE */
