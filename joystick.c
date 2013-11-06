#ifndef JOYSTICK
#define JOYSTICK

#define RADIANS_TO_DEG 57.295779

typedef enum {
  LEFT_JOYSTICK,
  RIGHT_JOYSTICK
} Joystick;

int joystickGetXAxis(Joystick j) {
  int x;

  switch (j) {
    case LEFT_JOYSTICK:
      x = vexRT[Ch4];
      break;
    case RIGHT_JOYSTICK:
      x = vexRT[Ch1];
      break;
  }

  // Ignore values less than 20 to compensate for
  // imperfectly centered joysticks
  if (abs(x) < 20)
    x = 0;

  return x;
}

int joystickGetYAxis(Joystick j) {
  int y;

  switch (j) {
    case LEFT_JOYSTICK:
      y = vexRT[Ch3];
      break;
    case RIGHT_JOYSTICK:
      y = vexRT[Ch2];
      break;
  }

  // Ignore values less than 20 to compensate for
  // imperfectly centered joysticks
  if (abs(y) < 20)
    y = 0;

  return y;
}

// Get the joystick angle (in standard position) in tenths of degrees
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

#endif
