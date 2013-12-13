#ifndef TANK_DRIVE
#define TANK_DRIVE

#include "joystick.c"
#include "drive.c"

void updateDriveTankDrive() {
  driveSetLeft( joystickGetAxis(LEFT_Y) );
  driveSetRight( joystickGetAxis(RIGHT_Y) );
}
 
#endif /* TANK_DRIVE */
