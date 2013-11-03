#ifndef TANK_DRIVE
#define TANK_DRIVE

#include "joystick.c"
#include "drive.c"

void updateDriveTankDrive() {
  setLeftDrive( joystickGetYAxis(LEFT_JOYSTICK) );
  setRightDrive( joystickGetXAxis(RIGHT_JOYSTICK) );
}
 
#endif /* TANK_DRIVE */
