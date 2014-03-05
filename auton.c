#ifndef AUTON
#define AUTON

#include "arm.c"
#include "intake.c"
#include "drive.c"

#define kStartToBarrierTicks 671
#define kBarrierToStartTicks -369
#define kToInsideBigBallTicks 851

#define kStartToWall 622
#define kWallToLargeBall -1337

#define kStartUnderBarrierTicks 0
#define kInFrontOfStashDistance 0
#define kStashUnderBarrier 0
#define kUnderBarrier 0

#define kNumAutonTurns 2

#define kFacingForwardsRed 0
#define kFacingForwardsBlue 0
#define kStashToBarrier 0

typedef enum { kInsideBigBall, kHangingLargeBall } Turn;
typedef enum { kRed, kBlue } TeamColor;
typedef enum { kHangingZone, kMiddleZone } Zone;

typedef struct
{
  Zone zone;
  TeamColor color;

  short turns[kNumAutonTurns][2];
} Auton;

static Auton auton = { kMiddleZone, kBlue };

void AutonHangingZoneStash(TeamColor color);

void AutonInit()
{
  auton.turns[kInsideBigBall][kRed] = 231;
  auton.turns[kInsideBigBall][kBlue] = -184;
  auton.turns[kHangingLargeBall][kBlue] = -290;
  auton.turns[kHangingLargeBall][kRed] = 205; // FIX ME
}

int AutonGetTurnTicks(Turn turn, TeamColor color)
{
  return auton.turns[turn][color];
}

void AutonTurn(Turn turn, TeamColor color)
{
  DriveTurnTicks( AutonGetTurnTicks(turn, color) );
}

void AutonMiddleZone(TeamColor color)
{
  // Flip out the intake
  IntakeSetPower(kIntakeInPower);
  wait1Msec(250);
  IntakeSetPower(0);

  // Move the arm to the barrier height
  ArmMoveToPos(kArmBarrierPos);

  // Knock the outside big ball into the goal zone and push the preload in
  DriveMoveTicks(kStartToBarrierTicks);

  // Move back partway to the starting tile
  DriveMoveTicks(kBarrierToStartTicks);
  wait1Msec(500);

  // Turn towards the inside big ball
  AutonTurn(kInsideBigBall, color);
  wait1Msec(500);

  // Set the intake to sweep the ball
  if (color == kRed)
    IntakeSetSweepLeft();
  else
    IntakeSetSweepRight();

  // Knock the inside big ball into the goal Zone
  DriveMoveTicks(kToInsideBigBallTicks, 0.7);

  // Stop the intake
  wait1Msec(1000);
  IntakeSetPower(0);
}

void AutonMiddleZoneStash(TeamColor color)
{
  // Flip out the intake
  IntakeSetPower(kIntakeInPower);

  // Drive under the barrier, knocking a large ball into the goal zone
  DriveMoveTicks(kStartUnderBarrierTicks, 1.0);

  // Stop the intake
  IntakeSetPower(0);

  // Raise the lift
  ArmMoveToPos(kArmUpPos);

  // Drive up to the stash
  while (SensorValue[stashSonar] > kInFrontOfStashDistance)
    DriveSetPower(kFullPower * 0.7);
  DriveSetPower(0);

  // Turn the robot until it's facing forwards
  if (color == kRed)
  {
    while (SensorValue[gyro] > kFacingForwardsRed) 
      DriveSetRight(kFullPower * 0.7);
  }
  else
  {
    while (SensorValue[gyro] < kFacingForwardsBlue)
      DriveSetLeft(kFullPower * 0.7);
  }

  // Eject the preload
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(500);
  IntakeSetPower(0);

  // Drive backwards up to the barrier
  DriveMoveTicks(kStashToBarrier, 1.0);

  // Lower the lift
  ArmMoveToPos(kArmDownPos);

  // Drive backwards under the barrier
  DriveMoveTicks(kStashUnderBarrier, 1.0);

  // Drive forwards under the barrier to knock a large ball into the goal zone
  DriveMoveTicks(kUnderBarrier, 1.0);
}

/*
void AutonHangingZone(TeamColor color)
{
  DriveTurnToDegrees(104.0);
}
*/

void AutonHangingZone(TeamColor color)
{
  // Set the intake in to flip it out and get ready to intake the two buckies
  IntakeSetPower(kIntakeInPower);

  // Drive forward to pick up the two buckies
  DriveMoveTicks(kStartToWall);
  wait1Msec(500);


  // Stop intaking
  IntakeSetPower(0);

  // Turn into position to push a big ball over the bump and knock the three buckies off the bump
  AutonTurn(kHangingLargeBall, color);

  // Push the large ball over the bump and the three buckies with it
  DriveMoveTicks(kWallToLargeBall, 1.0);
}

void AutonHangingZoneStash(TeamColor color)
{
  // Set the intake in to flip it out and get ready to intake the two buckies
  IntakeSetPower(kIntakeInPower);

  // Drive forward to pick up the two buckies
  DriveMoveTicks(kStartToWall, 0.7);

  // Stop the intake
  IntakeSetPower(0);
  
  // Drive backwards to the start
  DriveMoveTicks(-kStartToWall, 1.0);

  // Drive over the bump
  DriveMoveTicks(-1205, 1.0);

  // Pivot to face forwards
  DriveTurnTicks(823);

  // Drive under the barrier
  DriveMoveTicks(966, 1.0);

  // Pivot to face paralell to the stash
  DriveTurnTicks(-381);

  // Back into the wall to even out the robot
  DriveSetPower(kFullPower * 0.7);
  wait1Msec(500);

  // Raise the arm
  ArmMoveToPos(kArmUpPos);

  // Drive paralell to the stash
  DriveMoveTicks(932);

  // Pivot to face the stash
  DriveTurnTicks(394);

  // Drive up to the stash
  while (SensorValue[stashSonar] > kInFrontOfStashDistance)
    DriveSetPower(kFullPower * 0.7);
  DriveSetPower(0);

  // Eject the three buckyballs into the stash
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(3000);
  IntakeSetPower(0);
}

void AutonSetZone(Zone zone) {
  auton.zone = zone;
}

void AutonSetColor(TeamColor color) {
  auton.color = color;
}

TeamColor AutonGetColor()
{
  return auton.color;
}

Zone AutonGetZone()
{
  return auton.zone;
}

void AutonToggleZone()
{
  if ( AutonGetZone() == kHangingZone )
    AutonSetZone(kMiddleZone);
  else
    AutonSetZone(kHangingZone);
}

void AutonToggleColor()
{
  if ( AutonGetColor() == kRed )
    AutonSetColor(kBlue);
  else
    AutonSetColor(kRed);
}

void AutonRun()
{
  writeDebugStreamLine("Call to AutonRun");

  TeamColor color = AutonGetColor();

  if ( AutonGetZone() == kHangingZone )
    AutonHangingZoneStash(color);
  else
    AutonMiddleZone(color);
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
