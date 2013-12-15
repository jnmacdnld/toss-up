#ifndef TANK_DRIVE
#define TANK_DRIVE

#include "joystick.c"
#include "drive.c"

void TankDriveUpdate() {
  DriveSetLeft( JoystickGet(kLeftStickYAxis) );
  DriveSetRight( JoystickGet(kRightStickYAxis) );
}
 
#endif /* TANK_DRIVE */
