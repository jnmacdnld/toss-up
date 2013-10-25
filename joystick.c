#ifndef JOYSTICK
#define JOYSTICK

int joystickGetAxis(TVexJoysticks axis) {
  // Ignore values less than 10 to compensate for
  // imperfectly centered joysticks
  if ( abs(vexRT[axis]) < 10)
    return 0;
  else
    return vexRT[axis];
}

#endif
