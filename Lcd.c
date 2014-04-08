#ifndef LCD
#define LCD

#include "Auton.c"

// Define constants for the state of the LCD buttons
#define kNonePressed 0
#define kLeftPressed 1
#define kRightPressed 4
#define kCenterPressed 2

// Define constants for the screens that will appear on the Lcd
#define kNumScreens 5
#define kNumChoices 5

// Define a struct to hold data about a screen
typedef struct {
  string title;
  string choices[kNumChoices];
  short choice_targets[kNumChoices];
} Screen;

// Declare the fucntions that will be defined
void LcdUpdateScreen();
void LcdClear();
void LcdInitScreens();
void LcdGoNext();
void LcdGoPrev();
void LcdSelect();
bool LcdCanGoNext();
bool LcdCanGoPrev();

// Define and initialize the Screen structs
static Screen color_select =
{
  "Select Color",
  {"Red", "Blue", "", "", ""},
  {1, 1, -1, -1, -1},
};

static Screen zone_select =
{
  "Select Zone",
  {"Middle", "Hanging", "", "", ""},
  {2, 2, -1, -1, -1},
};

static Screen middle_routine_select =
{
  "Select Routine",
  {"Push", "Block & Push", "", "", ""},
  {4, 4, 4, 4, 4},
};

static Screen hanging_routine_select =
{
  "Select Routine",
  {"Stash", "Stash & Block", "Stash Three", "", ""},
  {4, 4, 4, 4, 4},
};

static Screen routine_selected =
{
  "",
  {"Change", "", "", "", ""},
  {0, -1, -1, -1, -1},
};

// Initialize variables to hold data about the Lcd
static Screen screens[kNumScreens] = 
{
  color_select, zone_select, middle_routine_select, hanging_routine_select,
  routine_selected
};

static short current_screen = 0;
static short current_choice = 0;

task LcdSetAuton()
{
  // Define variables to store the current and last state of the LCD buttons
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
        LcdGoPrev();

      if (last_state == kRightPressed)
        LcdGoNext();

      if (last_state == kCenterPressed)
        LcdSelect();
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
  // Update title on the display
  displayLCDCenteredString(0, screens[current_screen].title);

  // Update the current choice on the display
  displayLCDCenteredString(0, screens[current_screen].choices[current_choice] );

  // Update whether there is a previous choice
  if ( LcdCanGoPrev() )
    displayLCDChar(1, 0, '<');
  else 
    displayLCDChar(1, 0, ' ');

  // Update whethter there is a next choice
  if ( LcdCanGoNext() )
    displayLCDChar(1, 15, '>');
  else 
    displayLCDChar(1, 15, ' ');
}

bool LcdCanGoPrev()
{
  // If the choice id is zero, you can't go the previous choice
  if (current_choice == 0)
    return false;
  else
    return true;
}

bool LcdCanGoNext()
{
  // If this is the last choice, you can't go to the next choice
  if (current_choice == kNumChoices - 1)
    return false;

  // Store the target screen of the next choice
  short next_choice_tagret = screens[current_screen].choice_targets[current_choice + 1];

  // If the next choice has no target, you can't go to the next choice
  if (next_choice_tagret == -1)
    return false;
  
  // If the function hasn't exited yet, there must be a next choice
  return true;
}

void LcdGoNext()
{
  // If there is a next choice, increment the current choice
  if ( LcdCanGoNext() )
    current_choice++;
}

void LcdGoPrev()
{
  // If there is a previous choice, decrement the current choice
  if ( LcdCanGoPrev() )
    current_choice--;
}

void LcdSelect()
{
  // Call the appropriate callback functions for the screens
  switch (current_screen)
  {
    case 0:
      if (current_choice == 0)
        AutonSetColor(kRed);
      else
        AutonSetColor(kBlue);
      break;
    case 1:
      if (current_choice == 0)
        AutonSetZone(kMiddleZone);
      else
        AutonSetZone(kHangingZone);
      break;
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
    default:
      break;
  }

  // Change the screen to the target screen of the current choice of the current screen
  current_screen = screens[current_screen].choice_targets[current_choice];
}

void LcdClear()
{
  clearLCDLine(0);
  clearLCDLine(1);
}

#endif /* LCD */
