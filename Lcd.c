#ifndef LCD
#define LCD

#include "Auton.c"

#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4

void LcdUpdateAuton();

task LcdSetAuton()
{
  short current_state = nLCDButtons;
  short last_state = kNonePressed;

  while (true)
  {
    // Store the current state
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
    LcdUpdateAuton();

    // Don't hog CPU
    wait1Msec(25);
  }
}

void LcdUpdateAuton()
{
  // Display labels for color and zone
  displayLCDCenteredString(0, "Color:     Zone:");

  // Get the color and zone
  TeamColor color = AutonGetColor();
  Zone zone = AutonGetZone();

  // Display the color and zone on the screen
  if ( color == kRed && zone == kMiddleZone)
    displayLCDCenteredString(1, "Red       Middle");
  else if (color == kRed && zone == kHangingZone)
    displayLCDCenteredString(1, "Red      Hanging");
  else if (color == kBlue && zone == kMiddleZone)
    displayLCDCenteredString(1, "Blue      Middle");
  else if (color == kBlue && zone == kHangingZone)
    displayLCDCenteredString(1, "Blue     Hanging");
  else
    displayLCDCenteredString(1, "Error      Error");
}

#endif /* LCD */
