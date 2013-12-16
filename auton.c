#ifndef AUTON
#define AUTON

#include "arm.c"
#include "intake.c"
#include "drive.c"

#define kStartToBarrierTicks 671
#define kBarrierToStartTicks -369
#define kToInsideBigBallTicks 851

#define kNumAutonTurns 1

typedef enum { kInsideBigBall } Turn;
typedef enum { kRed, kBlue } TeamColor;
typedef enum { kHangingZone, kMiddleZone } Zone;

int autonTurnsTicks[kNumAutonTurns][2];

void AutonInit() {
  autonTurnsTicks[kInsideBigBall][kRed] = 231;
  autonTurnsTicks[kInsideBigBall][kBlue] = -184;
}

int AutonGetTurnTicks(Turn turn, TeamColor color) {
  return autonTurnsTicks[turn][color];
}

void AutonTurn(Turn turn, TeamColor color) {
  DriveTurnTicks( AutonGetTurnTicks(turn, color) );
}

void AutonMiddleZone(TeamColor color) {
  // Move the arm to the barrier height
  ArmMoveToPos(kArmBarrierPos);

  // Knock the outside big ball in to the goal Zone
  DriveMoveTicks(kStartToBarrierTicks);
  wait1Msec(500);

  // Move back partway to the starting tile
  DriveMoveTicks(kBarrierToStartTicks);
  wait1Msec(500);

  // Turn towards the inside big ball
  AutonTurn(kInsideBigBall, color);
  wait1Msec(500);

  // Knock the inside big ball into the goal Zone
  DriveMoveTicks(kToInsideBigBallTicks);
  wait1Msec(500);

  // Outtake the bucky into the goal Zone
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(1000);
  IntakeSetPower(0);
}

void AutonHangingZone(TeamColor color) {

}

/*#define kStartToBarrierTicks 880
#define kStartToBarrierInches 28.21
#define START_TO_BARRIER_INCHES_MINUS_3 kStartToBarrierInches - 10

#define kFirstToSecondBigBallInches 32.25

#define kFieldTileWidthInches 23.42

#define TICKS_PER_PIVOT_90 431
#define TICKS_PER_PIVOT_MINUS_90 -369*/

/*void AutonBlueMiddleZone() {
	writeDebugStreamLine("started auton");
  ArmMoveToPos(kArmBarrierPos);

  // Knock the first big ball into the goal Zone and return 3 inches from the starting position
  DriveMoveInches(kFieldTileWidthInches);
  DriveMoveInches( -kFieldTileWidthInches);

  // Turn left and move to the second large ball
  AutonTurnToDegrees(-90.0);
  DriveMoveInches(kFirstToSecondBigBallInches);

  // Turn towards the ball and knock it into the goal Zone
  AutonTurnToDegrees(0);
  DriveMoveInches( START_TO_BARRIER_INCHES_MINUS_3);

  // Don't use the following for now

  return;
  // Move back from the barrier
  DriveMoveInches( - START_TO_BARRIER_INCHES_MINUS_3 );

  // Align the robot with the bucky goal
  AutonTurnToDegrees(90.0);
  DriveMoveInches( kFieldTileWidthInches / 2 );

  // Turn towards the bucky goal
  AutonTurnToDegrees(0.0);

  // Move 2/3 the way to the bucky goal, raise the arm
  DriveMoveInches( (kFieldTileWidthInches * 2) - 3);
  ArmMoveToPos(kArmUpPos);

  // Move to the goal and score the bucky
  DriveMoveInches(kFieldTileWidthInches);
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(1000);
  IntakeSetPower(0);
}

void AutonBlueHangingZone() {
  // Pick up the two buckies in front of the robot
  IntakeSetPower(kIntakeInPower);
  DriveMoveInches(kFieldTileWidthInches - 2);
  wait1Msec(500);
  IntakeSetPower(0);

  // Drive to the first big ball
  AutonTurnToDegrees(90.0);
  DriveMoveInches(kFieldTileWidthInches);

  // Push the first big ball into the middle Zone and return
  AutonTurnToDegrees(180.0);
  ArmMoveToPos(kArmBigBallPos);
  DriveMoveInches(kFieldTileWidthInches);
  DriveMoveInches(-kFieldTileWidthInches);

  // Drive to the second big ball
  AutonTurnToDegrees(90.0);
  DriveMoveInches(kFieldTileWidthInches);

  // Push the second big ball into the middle Zone
  AutonTurnToDegrees(180.0);
  DriveMoveInches(kFieldTileWidthInches);
  DriveMoveInches(-kFieldTileWidthInches);

  IntakeSetPower(kIntakeOutFastPower);
}
*/

#endif /* AUTON */
