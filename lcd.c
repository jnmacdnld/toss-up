#ifndef LCD
#define LCD

#include "auton.c"

#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4

void LcdUpdateScreen();

task Lcd()
{
  short current_state = nLCDButtons;
  short last_state = kNonePressed;

  while (true)
  {
    // Record the current state
    current_state = nLCDButtons;

    // Call the right functions when buttons are released
    if (current_state == kNonePressed)
    {
      if (last_state == kLeftPressed)
        AutonToggleColor();

      if (last_state == kRightPressed)
        AutonToggleZone();
    }

    last_state = current_state;

    // Update what it says on the screen
    LcdUpdateScreen();

    wait1Msec(25);
  }
}

void LcdUpdateScreen()
{
  // Update the team color on the screen
  if ( AutonGetColor() == kRed )
    displayLCDCenteredString(0, "Red");
  else
    displayLCDCenteredString(0, "Blue");

  // Update the zone on the screen
  if ( AutonGetZone() == kHangingZone )
    displayLCDCenteredString(1, "Hanging Zone");
  else
    displayLCDCenteredString(1, "Middle Zone");
}
 
#endif /* LCD */
