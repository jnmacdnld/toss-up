#ifndef INTERFACE
#define INTERFACE
 
void waitForTouch() {
  writeDebugStreamLine("Press touch to continue.");
  while (!SensorValue[touch]) wait1Msec(25);
}
 
#endif /* INTERFACE */