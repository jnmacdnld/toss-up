#ifndef LCD
#define LCD

#include "auton.c"

#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4

task Lcd()
{
  current_state = nLcdButtons;

  // Call the right functions when buttons are released
  if (current_state == kNonePressed)
  {
    if (last_state == kLeftPressed)
      AutonToggleColor();

    if (last_state == kRightPressed)
      AutonToggleZone();
  }

  last_state = current_state;

  LcdUpdate();
}

void LcdUpdate()
{
  // Update the team color on the screen
  if (auton.color == kRed)
    displayLCDCenterString(0, "Red");
  else
    displayLCDCenterString(0, "Blue");

  // Update the zone on the screen
  if (auton.zone == kHangingZone)
    displayLCDCenterString(1, "Hanging Zone");
  else
    displayLCDCenterString(1, "Middle Zone");
}
 
#endif /* LCD */
