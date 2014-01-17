#ifndef JUMPERS
#define JUMPERS
  
#include "auton.c"

// Digital Port 6: Red initially, Blue with jumper
// Digital Port 8: Middle Zone initally, Hanging Zone with Jumper

void JumpersSetAuton()
{
  // Set the team color from one jumper
  if ( SensorBoolean[ColorJumper] == true )
    AutonSetColor(kRed);
  else
    AutonSetColor(kBlue);

  // Set the zone from one jumper
  if ( SensorBoolean[ZoneJumper] == true )
    AutonSetZone(kMiddleZone);
  else
    AutonSetZone(kHangingZone);
}
  
#endif
