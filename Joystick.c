#ifndef JOYSTICK
#define JOYSTICK

#define kRadiansToDeg 57.295779

#include "Motors.c"

typedef enum {
  kLeftStickXAxis = 0,
  kRightStickXAxis = 1,
  kLeftStickYAxis = 2,
  kRightStickYAxis = 3
} Joystick;

// int joystickLuts[4][128];

int GetAdjustedJoystickValue(int value) {
  if ( abs(value) <= 117 )
    return (int) (value * (80.0 / 117) ) * sgn(value);
  else
    return kFullPower * sgn(value);
}

void InitJoystickLuts() {
  /*for (int i = 0; i < 128; i++){
    joystickLuts[kRightStickXAxis][i] = GetAdjustedJoystickValue(i);
    joystickLuts[kLeftStickXAxis][i] = i;
    joystickLuts[kRightStickYAxis][i] = i;
    joystickLuts[kLeftStickYAxis][i] = i;
  }*/
}

int JoystickGet(Joystick j) {
  int value;

  switch (j) {
    case kLeftStickXAxis:
      value = vexRT[Ch4];
      break;
    case kRightStickXAxis:
      value = vexRT[Ch1];
      break;
    case kLeftStickYAxis:
      value = vexRT[Ch3];
      break;
    case kRightStickYAxis:
      value = vexRT[Ch2];
      break;
  }

  // Ignore values less than 20 to compensate for
  // imperfectly centered joysticks
  if (abs(value) < 20)
    value = 0;

  // value = joystickLuts[j][ abs(value) ] * sgn(value);

  return value;
}

/*// Get the joystick angle (in standard position) in tenths of degrees
int JoystickGetAngle(Joystick j) {
  float x = JoystickGetXAxis(j);
  float y = JoystickGetYAxis(j);
  float angle = Atan(x / y);

  // Adjust if the angle if it is not in Q1 so the correct value is returned
  if (x < 0 && y > 0 || x < 0 && y < 0) // If in Q2 or Q2
    angle += PI;
  else if (x > 0 && y < 0) // If in Q3
    angle += 2 * PI;

  // Convert to tenths of degrees
  return (int) (angle * RADIANS_TO_DEG * 10);
}

// Get joystick magnitude (returns values from 0 to 127)
int JoystickGetMagnitude(Joystick j) {
  int x = JoystickGetXAxis(j);
  int y = JoystickGetYAxis(j);

  return (int) Sqrt( (x * x) + (y * y) );
}
*/
#endif
