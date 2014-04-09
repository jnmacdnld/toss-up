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
      AutonSetRoutine(current_choice);
      screens[kRoutineSelectedScreenId].title = LcdGetAutonString();
      break;
    case 3:
      AutonSetRoutine(current_choice);
      screens[kRoutineSelectedScreenId].title = LcdGetAutonString();
      break;
    case 4:
      break;
    default:
      break;
  }

  // Change the screen to the target screen of the current choice of the current screen
  current_screen = screens[current_screen].choice_targets[current_choice];
}

void LcdInitScreens()
{
  // Fill the middle zone routine select screen choices
  for (short i = 0; i < kNumMiddleRoutines; i++)
    screens[kMiddleRoutineScreenId].choices[i] = middle_routine_names[i];
  
  // Fill the hanging zone routine select screen choices
  for (short i = 0; i < kNumHangingRoutines; i++)
    screens[kHangingRoutineScreenId].choices[i] = middle_routine_names[i];
}

void LcdGetAutonString()
{
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
  
  
  return color + " " + zone + " " + routine;
}

void LcdClear()
{
  clearLCDLine(0);
  clearLCDLine(1);
}

#endif /* LCD */
