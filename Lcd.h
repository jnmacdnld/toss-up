#ifndef LCD_H
#define LCD_H

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

#endif
