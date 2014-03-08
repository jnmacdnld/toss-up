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
#define kInFrontOfStashDistance 28
#define kStashUnderBarrier 0
#define kUnderBarrier 0

#define kNumAutonTurns 5

#define kFacingForwardsRed 0
#define kFacingForwardsBlue 0
#define kStashToBarrier 0

#define kWallToStashRed 932 + 20
#define kWallToStashBlue 932 - 40

typedef enum { kInsideBigBall, kHangingLargeBall, kPivotForwards, kPivotInside, kPivotStash } Turn;
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
void AutonTurn(Turn turn, TeamColor color, float percent = 0.7);

void AutonInit()
{
  // Middle Zone autonomous
  auton.turns[kInsideBigBall][kRed] = 231;
  auton.turns[kInsideBigBall][kBlue] = -184;

  // Hanging Zone autonomous
  auton.turns[kHangingLargeBall][kBlue] = -290;
  auton.turns[kHangingLargeBall][kRed] = 205; // FIX ME

  // Hanging Zone stash autonomous
  auton.turns[kPivotForwards][kBlue] = 723;
  auton.turns[kPivotForwards][kRed] = -810;

  auton.turns[kPivotInside][kBlue] = -301;
  auton.turns[kPivotInside][kRed] = 447;

  auton.turns[kPivotStash][kBlue] = 444 - 10;
  auton.turns[kPivotStash][kRed] = -404 + 30;
}

int AutonGetTurnTicks(Turn turn, TeamColor color)
{
  return auton.turns[turn][color];
}

void AutonTurn(Turn turn, TeamColor color, float percent)
{
  DriveTurnTicks( AutonGetTurnTicks(turn, color), percent );
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
  // Start counting the time
  ClearTimer(T1);

  // Set the intake in to flip it out and get ready to intake the two buckies, leave it on
  // to keep buckies from falling out
  IntakeSetPower(kIntakeInPower);

  // Keep the arm down
  ArmSetPower(-15);

  // Drive forward to pick up the two buckies
  DriveMoveTicks(kStartToWall, 0.7);

  // Drive back to the start
  DriveMoveTicks(-kStartToWall, 1.0);

  // Drive backwards over the bump (breaking this into two parts evens out the robot)
  DriveMoveTicks(-1005, 1.0);

  // Stop the intake
  IntakeSetPower(0);

  // Pivot to face forwards
  AutonTurn(kPivotForwards, color, 0.85);

  // Drive up to the barrier
  while (SensorValue[leftFrontLine] > 2700)
    DriveSetPower(kFullPower);
  writeDebugStreamLine("Saw line, continuing");

  // Drive under the barrier, knocking a large ball into the goal zone
  DriveMoveTicks(639 + 60, 1.0);

  // Pivot to face paralell to the stash
  AutonTurn(kPivotInside, color, 0.85);

  // Raise the arm in the background
  ArmControlSetTarget(kArmUpPos);

  // Back into the wall to even out the robot
  DriveSetPower(-kFullPower * 0.85);
  wait1Msec(750);

  // Drive paralell to the stash
  if (color == kRed)
    DriveMoveTicks(kWallToStashRed);
  else
    DriveMoveTicks(kWallToStashBlue);

  // Pivot to face the stash
  AutonTurn(kPivotStash, color, 0.85);

  // Drive up to the stash
  while (SensorValue[stashSonar] > kInFrontOfStashDistance)
  {
    // If the robot is almost out of time, eject the buckies
    if (time1[T1] > 13000)
      break;

    // Keep driving toward the stash
    DriveSetPower(kFullPower * 0.85);
  }

  // Stop driving up to the stash
  DriveSetPower(0);

  // Eject the three buckyballs into the stash
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(2000);
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

  if (color == kRed)
    writeDebugStreamLine("Color is red.");
  else
    writeDebugStreamLine("Color is blue.")

  if ( AutonGetZone() == kHangingZone )
    AutonHangingZone(color);
  else
    AutonMiddleZone(color);
}

#endif /* AUTON */
