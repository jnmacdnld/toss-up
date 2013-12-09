#ifndef AUTONOMOUS
#define AUTONOMOUS

#include "arm.c"
#include "drive.c"
#include "intake.c"
#include "interface.c"

#define START_TO_BARRIER_TICKS 880
#define START_TO_BARRIER_INCHES 28.21
#define START_TO_BARRIER_INCHES_MINUS_3 START_TO_BARRIER_INCHES - 10

#define FIRST_TO_SECOND_BIG_BALL_INCHES 32.25

#define FIELD_TILE_WIDTH_INCHES 23.42

void AutonTest() {
  writeDebugStream("Should move forward 20 inches");
  driveMoveInches(20);
  waitForTouch();

  writeDebugStreamLine("Should move backward 20 inches");
  driveMoveInches(-20);
  waitForTouch();

  writeDebugStreamLine("Should turn to position 90 degrees left");
  driveTurnToDegrees(-90.0);
  waitForTouch();

  writeDebugStreamLine("Should turn to position 90 degrees right");
  driveTurnToDegrees(90.0);

  writeDebugStreamLine("Done.");
}

void AutonBlueMiddleZone() {
	writeDebugStreamLine("started auton");
  armMoveToPos(ARM_BARRIER_POS);

  // Knock the first big ball into the goal zone and return 3 inches from the starting position
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches( -FIELD_TILE_WIDTH_INCHES);

  // Turn left and move to the second large ball
  driveTurnToDegrees(-90.0);
  driveMoveInches(FIRST_TO_SECOND_BIG_BALL_INCHES);

  // Turn towards the ball and knock it into the goal zone
  driveTurnToDegrees(0);
  driveMoveInches( START_TO_BARRIER_INCHES_MINUS_3);

  // Don't use the following for now

  return;
  // Move back from the barrier
  driveMoveInches( - START_TO_BARRIER_INCHES_MINUS_3 );

  // Align the robot with the bucky goal
  driveTurnToDegrees(90.0);
  driveMoveInches( FIELD_TILE_WIDTH_INCHES / 2 );

  // Turn towards the bucky goal
  driveTurnToDegrees(0.0);

  // Move 2/3 the way to the bucky goal, raise the arm
  driveMoveInches( (FIELD_TILE_WIDTH_INCHES * 2) - 3);
  armMoveToPos(ARM_UP_POS);

  // Move to the goal and score the bucky
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  intakeSetPower(INTAKE_OUT_SLOW_PWR);
  wait1Msec(1000);
  intakeSetPower(0);
}

void AutonBlueHangingZone() {
  // Pick up the two buckies in front of the robot
  intakeSetPower(INTAKE_IN_PWR);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES - 2);
  wait1Msec(500);
  intakeSetPower(0);

  // Drive to the first big ball
  driveTurnToDegrees(90.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);

  // Push the first big ball into the middle zone and return
  driveTurnToDegrees(180.0);
  armMoveToPos(ARM_BIG_BALL_POS);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches(-FIELD_TILE_WIDTH_INCHES);

  // Drive to the second big ball
  driveTurnToDegrees(90.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);

  // Push the second big ball into the middle zone
  driveTurnToDegrees(180.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches(-FIELD_TILE_WIDTH_INCHES);

  intakeSetPower(INTAKE_OUT_FAST_PWR);
}

void AutonRedMiddleZone() {
  driveMirrorTurning = true;
  AutonBlueMiddleZone();
}

void AutonRedHangingZone() {
  driveMirrorTurning = true;
  AutonBlueHangingZone();
}

#endif /* AUTONOMOUS */
