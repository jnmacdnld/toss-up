        #ifndef UI
#define UI

void WaitForTouch() {
  writeDebugStreamLine("Press touch to continue.");
  while (!SensorValue[touch]) wait1Msec(25);
}
 
#endif /* UI */