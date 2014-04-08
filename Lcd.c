#ifndef LCD
#define LCD

#include "Auton.c"

// Define constants for the state of the LCD buttons
#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4
#define kCenterPressed 2

// Define constatnts for the screens that will appear on the Lcd
#define kNumScreens 4

// Define a struct to hold data about a screen
typedef struct {
  string title;
  string choices[5];
  short choice_targets[5];
  short current_choice;
} Screen;

// Declare the fucntions that will be defined
void LcdUpdateAuton();
void LcdClear();
void LcdInitScreens();
void LcdGoNext();
void LcdGoPrev();
void LcdSelect();

task LcdSetAuton()
{
  // Define variables to store the current and last state of the LCD buttons
  short current_state = nLCDButtons;
  short last_state = kNonePressed;

  // Define variables to store the screens and currently displayed screen
  Screen screens[kNumScreens];
  short current_screen;

  // Initialize the screens array
  LcdInitScreens();

  while (true)
  {
    // Store the current state
    current_state = nLCDButtons;

    // If no buttons are currently pressed and one was pressed on the last
    // iteration, that button was just released; call the appropriate function
    if (current_state == kNonePressed)
    {
      if (last_state == kLeftPressed)
        LcdGoPrev();

      if (last_state == kRightPressed)
        LcdGoNext();

      if (last_state == kCenterPressed)
        LcdSelect();
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
  screens[0].title = "Select Color";
  screens[0].choices = {"Red", "Blue", "", "", ""};
  screens[0].choice_targets = {1, 1, -1, -1, -1};

  screens[1].title = "Select Zone";
  screens[1].choices = {"Middle", "Hanging", "", "", ""};
  screens[1].choice_targets = {2, 2, -1, -1, -1};

  screens[2].title = "Select Routine";
  screens[2].choices = {"Push", "Block & Push", "", "", ""};
  screens[2].choice_targets = {4, 4, 4, 4, 4};

  screens[3].title = "Select Routine";
  screens[3].choices = {"Stash", "Stash & Block", "Stash Three", "", ""};
  screens[3].choice_targets = {4, 4, 4, 4, 4};

  screens[4].choices = {"Change", "", "", "", ""};
  screens[4].choice_targets = {0, -1, -1, -1, -1};
}

#endif /* LCD */
