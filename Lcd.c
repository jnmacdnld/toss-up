#ifndef LCD_C
#define LCD_C

#include "Lcd.h"

#include "Auton.c"

task LcdSetAuton()
{
  // Define variables to store the current and last state of the LCD buttons
  short current_state = nLCDButtons;
  short last_state = kNonePressed;

  while (true)
  {
    // Store the current state
    current_state = nLCDButtons;

    // If a button is pressed and no buttons were previously pressed, it's just
    // been pressed; call the appropriate function
    if (current_state != kNonePressed && last_state == kNonePressed)
    {
      if (current_state == kLeftPressed)
        AutonToggleColor();

      if (current_state == kCenterPressed)
      {
        AutonToggleZone();
        AutonSetRoutine(0);
      }

      if (current_state == kRightPressed)
        AutonStepRoutine();
      
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
  // Display a heading
  displayLCDCenteredString(0, "Clr: Zone: Rtne:");

  // Define a variable to hold the autonomous descriptor
  string auton_string = "";

  // Get the autonomous descriptor
  LcdGetAutonString(auton_string);

  // Display the autonomous descriptor
  displayLCDCenteredString(1, auton_string);
}

/*void LcdUpdateScreen()
{
  // Update title on the display
  displayLCDCenteredString(0, screens[current_screen].title);

  // Update the current choice on the display
  displayLCDCenteredString(1, screens[current_screen].choices[current_choice] );

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
}*/

/*void LcdSelect()
{
  string auton_string;

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
      AutonSetRoutine(current_choice);
      LcdGetAutonString(auton_string);
      screens[kRoutineSelectedScreenId].title = auton_string;
      break;
    case 3:
      AutonSetRoutine(current_choice);
      LcdGetAutonString(auton_string);
      screens[kRoutineSelectedScreenId].title = auton_string;
      break;
    case 4:
      break;
    default:
      break;
  }

  // Change the screen to the target screen of the current choice of the current screen
  current_screen = screens[current_screen].choice_targets[current_choice];
}*/

/*void LcdInitScreens()
{
  // Fill the middle zone routine select screen choices
  for (short i = 0; i < kNumMiddleRoutines; i++)
    screens[kMiddleRoutineScreenId].choices[i] = middle_routine_names[i];

  // Fill the hanging zone routine select screen choices
  for (short i = 0; i < kNumHangingRoutines; i++)
    screens[kHangingRoutineScreenId].choices[i] = middle_routine_names[i];
}*/

void LcdGetAutonString(string &auton_string)
{
  auton_string = "";

  string color;
  string zone;
  string routine;

  if (AutonGetColor() == kRed)
    color = "Red ";
  else
    color = "Blue";

  if (AutonGetZone() == kMiddleZone)
  {
    zone = "Mid  ";
    routine = middle_routine_abbs[AutonGetRoutine()];
  }
  else
  {
    zone = "Hang ";
    routine = hanging_routine_abbs[AutonGetRoutine()];
  }

  strcat(auton_string, color);
  strcat(auton_string, " ");
  strcat(auton_string, zone);
  strcat(auton_string, " ");
  strcat(auton_string, routine);
}

void LcdClear()
{
  clearLCDLine(0);
  clearLCDLine(1);
}

#endif /* LCD */
