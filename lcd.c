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

    // If no buttons are currently pressed and one was pressed on the last
    // iteration, that button was just released; call the appropriate function
    if (current_state == kNonePressed)
    {
      if (last_state == kLeftPressed)
        AutonToggleColor();

      if (last_state == kRightPressed)
        AutonToggleZone();
    }

    // Update last_state for the next iteration
    last_state = current_state;

    // Update what it says on the screen
    LcdUpdateScreen();

    // Don't hog CPU
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
