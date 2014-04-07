#ifndef LCD
#define LCD

#include "Auton.c"

// Define constants for the state of the LCD buttons
#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4

// Define a struct to hold data about a screen
/*typedef struct {
  string title;
  string[5] choices;
  short[5] target_screens;
  short current_choice;
} Screen;*/

void LcdUpdateAuton();
void LcdClear();

task LcdSetAuton()
{
  // Define variables to store the current and last state of the LCD buttons
  short current_state = nLCDButtons;
  short last_state = kNonePressed;

  // Define variables to store the screens and currently displayed screen
  /*Screen[] screens;
  short current_screen;*/

  // Initialize the screens array
  /*LcdInitScreens();*/

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

void LcdClear()
{
  clearLCDLine(0);
  clearLCDLine(1);
}

void LcdInitScreens()
{
  
}

#endif /* LCD */
