#ifndef AUTON
#define AUTON

#include "arm.c"
#include "intake.c"
#include "drive.c"

#define kStartToBarrierTicks 671
#define kBarrierToStartTicks -369
#define kToInsideBigTicks 851

#define kNumAutonTurns 1

typedef enum { InsideBigBall } autonTurn;
typedef enum { Red, Blue } teamColor;
typedef enum { HangingZone, MiddleZone } zone;

int autonTurnsTicks[kNumAutonTurns][2];

void AutonInit() {
  autonTurnsTicks[InsideBigBall][Red] = 231;
  autonTurnsTicks[InsideBigBall][Blue] = -184;
}

int AutonGetTurnTicks(autonTurn turn, teamColor color) {
  return autonTurnsTicks[turn][color];
}

void AutonTurn(autonTurn turn, teamColor color) {
  driveTurnTicks( AutonGetTurnTicks(turn, color) );
}

void AutonMiddleZone(teamColor color) {
  // Move the arm to the barrier height
  armMoveToPos(ARM_BARRIER_POS);

  // Knock the outside big ball in to the goal zone
  driveMoveTicks(kStartToBarrierTicks);
  wait1Msec(500);

  // Move back partway to the starting tile
  driveMoveTicks(kBarrierToStartTicks);
  wait1Msec(500);

  // Turn towards the inside big ball
  AutonTurn(InsideBigBall, color);
  wait1Msec(500);

  // Knock the inside big ball into the goal zone
  driveMoveTicks(kToInsideBigTicks);
  wait1Msec(500);

  // Outtake the bucky into the goal zone
  intakeSetPower(INTAKE_OUT_SLOW_PWR);
  wait1Msec(1000);
  intakeSetPower(0);
}

void AutonHangingZone(teamColor color) {

}

/*#define START_TO_BARRIER_TICKS 880
#define START_TO_BARRIER_INCHES 28.21
#define START_TO_BARRIER_INCHES_MINUS_3 START_TO_BARRIER_INCHES - 10

#define FIRST_TO_SECOND_BIG_BALL_INCHES 32.25

#define FIELD_TILE_WIDTH_INCHES 23.42

#define TICKS_PER_PIVOT_90 431
#define TICKS_PER_PIVOT_MINUS_90 -369*/

/*void AutonBlueMiddleZone() {
	writeDebugStreamLine("started auton");
  armMoveToPos(ARM_BARRIER_POS);

  // Knock the first big ball into the goal zone and return 3 inches from the starting position
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches( -FIELD_TILE_WIDTH_INCHES);

  // Turn left and move to the second large ball
  AutonTurnToDegrees(-90.0);
  driveMoveInches(FIRST_TO_SECOND_BIG_BALL_INCHES);

  // Turn towards the ball and knock it into the goal zone
  AutonTurnToDegrees(0);
  driveMoveInches( START_TO_BARRIER_INCHES_MINUS_3);

  // Don't use the following for now

  return;
  // Move back from the barrier
  driveMoveInches( - START_TO_BARRIER_INCHES_MINUS_3 );

  // Align the robot with the bucky goal
  AutonTurnToDegrees(90.0);
  driveMoveInches( FIELD_TILE_WIDTH_INCHES / 2 );

  // Turn towards the bucky goal
  AutonTurnToDegrees(0.0);

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
  AutonTurnToDegrees(90.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);

  // Push the first big ball into the middle zone and return
  AutonTurnToDegrees(180.0);
  armMoveToPos(ARM_BIG_BALL_POS);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches(-FIELD_TILE_WIDTH_INCHES);

  // Drive to the second big ball
  AutonTurnToDegrees(90.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);

  // Push the second big ball into the middle zone
  AutonTurnToDegrees(180.0);
  driveMoveInches(FIELD_TILE_WIDTH_INCHES);
  driveMoveInches(-FIELD_TILE_WIDTH_INCHES);

  intakeSetPower(INTAKE_OUT_FAST_PWR);
}
*/

#endif /* AUTON */
