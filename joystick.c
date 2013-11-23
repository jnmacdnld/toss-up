#ifndef JOYSTICK
#define JOYSTICK

#define RADIANS_TO_DEG 57.295779

#include "motor.c"

typedef enum {
  LEFT_X = 0,
  RIGHT_X = 1,
  LEFT_Y = 2,
  RIGHT_Y = 3
} Joystick;

int joystickLuts[4][128];

int getAdjustedJoystickValue(int value) {
  if ( abs(value) <= 117 )
    return (int) (value * (70.0 / 117) ) * sgn(value);
  else
    return FULL_POWER * sgn(value);
}

void initJoystickLuts() {
  for (int i = 0; i < 128; i++){
    joystickLuts[RIGHT_X][i] = getAdjustedJoystickValue(i);
    joystickLuts[LEFT_X][i] = i;
    joystickLuts[RIGHT_Y][i] = i;
    joystickLuts[LEFT_Y][i] = i;
  }
}

int joystickGetAxis(Joystick j) {
  int value;

  switch (j) {
    case LEFT_X:
      value = vexRT[Ch4];
      break;
    case RIGHT_X:
      value = vexRT[Ch1];
      break;
    case LEFT_Y:
      value = vexRT[Ch3];
      break;
    case RIGHT_Y:
      value = vexRT[Ch2];
      break;
  }

  // Ignore values less than 20 to compensate for
  // imperfectly centered joysticks
  if (abs(value) < 20)
    value = 0;

  value = joystickLuts[j][ abs(value) ] * sgn(value);

  return value;
}

/*// Get the joystick angle (in standard position) in tenths of degrees
int joystickGetAngle(Joystick j) {
  float x = joystickGetXAxis(j);
  float y = joystickGetYAxis(j);
  float angle = atan(x / y);

  // Adjust if the angle if it is not in Q1 so the correct value is returned
  if (x < 0 && y > 0 || x < 0 && y < 0) // If in Q2 or Q2
    angle += PI;
  else if (x > 0 && y < 0) // If in Q3
    angle += 2 * PI;

  // Convert to tenths of degrees
  return (int) (angle * RADIANS_TO_DEG * 10);
}

// Get joystick magnitude (returns values from 0 to 127)
int joystickGetMagnitude(Joystick j) {
  int x = joystickGetXAxis(j);
  int y = joystickGetYAxis(j);

  return (int) sqrt( (x * x) + (y * y) );
}
*/
#endif
