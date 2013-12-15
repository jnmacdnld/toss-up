#ifndef AUTON_TEST
#define AUTON_TEST

void AutonTestMove() {
  writeDebugStream("Should move forward 20 inches");
  DriveMoveInches(20);
  WaitForTouch();

  writeDebugStreamLine("Should move backward 20 inches");
  DriveMoveInches(-20);

  writeDebugStreamLine("Done.");
}

void AutonTestTurn() {
  writeDebugStreamLine("At position %f", GyroGetAngle() );

  writeDebugStreamLine("Should turn to position 90 degrees left");
  DriveTurnToDegrees(-90.0);
  wait1Msec(500);
  writeDebugStreamLine("Should be at position 90 degrees left");
  writeDebugStreamLine("At position %f", GyroGetAngle() );
  WaitForTouch();

  writeDebugStreamLine("Should turn to position 90 degrees right");
  DriveTurnToDegrees(90.0);
  wait1Msec(500);
  writeDebugStreamLine("Should be at position 90 degrees right");
  writeDebugStreamLine("At position %f", GyroGetAngle() );
  WaitForTouch();

  writeDebugStreamLine("Should turn to position 0 ahead");
  DriveTurnToDegrees(0.0);
  wait1Msec(500);
  writeDebugStreamLine("Should be at position 0 ahead");
  writeDebugStreamLine("At position %f", GyroGetAngle() );

  writeDebugStreamLine("Done.");
}

#endif /* AUTON_TEST */
