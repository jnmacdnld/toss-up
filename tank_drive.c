#ifndef TANK_DRIVE
#define TANK_DRIVE

#include "joystick.c"
#include "drive.c"

void updateDriveTankDrive() {
  setLeftDrive( joystickGetAxis(LEFT_Y) );
  setRightDrive( joystickGetXAxis(RIGHT_Y) );
}
 
#endif /* TANK_DRIVE */
