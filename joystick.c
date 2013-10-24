float getJoystickAngle(int x, int y) {
  return arctan( (float) x / (float) y );
}

int getJoystickMagnitude(int x, int y) {
  return (int) sqrt( (x * x) + (y * y) );
}

