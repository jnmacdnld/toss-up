#ifndef AUTON
#define AUTON

#include "LiftControl.c"
#include "Intake.c"
#include "Drive.c"

#define kStartToBarrierTicks 671
#define kBarrierToStartTicks -369
#define kToInsideBigBallTicks 851

#define kStartToWall 622
#define kWallToLargeBall -1337

#define kStartUnderBarrierTicks 1679
#define kInFrontOfStashDistance 28
#define kStashUnderBarrier 0
#define kUnderBarrier 0

#define kNumAutonTurns 9

#define kFacingForwardsRed 0
#define kFacingForwardsBlue 0
#define kStashToBarrier 0

#define kWallToStashRed 932 + 20
#define kWallToStashBlue 932 - 40

#define kPush 0
#define kBlockAndPush 1

#define kStash 0
#define kStashAndBlock 1
#define kStashThree 2
#define kBlock 3

#define kNumMiddleRoutines 1
#define kNumHangingRoutines 2

typedef enum
{
  kInsideBigBall, kHangingLargeBall, kPivotForwards, kPivotInside,
  kPivotStash, kStashInsideLargeBall, kPushBuckies, kOpponentStash,
  kOpponentStashParalell
} Turn;
typedef enum { kRed, kBlue } TeamColor;
typedef enum { kHangingZone, kMiddleZone } Zone;

typedef struct
{
  Zone zone;
  TeamColor color;
  short routine;

  short turns[kNumAutonTurns][2];
} Auton;

static Auton auton = { kMiddleZone, kBlue };

void AutonStashThreeHanging(TeamColor color);
void AutonTurn(Turn turn, TeamColor color, float percent = 0.7);

void AutonSetZone(Zone zone);
void AutonSetColor(TeamColor color);

void AutonStepRoutine();

#include "AutonHangingPush.c"
#include "AutonHangingBlockPush.c"
#include "AutonMiddleStash.c"
#include "AutonMiddleBlock.c"

void AutonInit()
{
  // Middle Zone autonomous
  auton.turns[kInsideBigBall][kRed] = 231;
  auton.turns[kInsideBigBall][kBlue] = -184;

  // Middle Zone stash autonomous
  auton.turns[kStashInsideLargeBall][kRed] = -330;
  auton.turns[kStashInsideLargeBall][kBlue] = 430;

  auton.turns[kOpponentStash][kRed] = 100;
  auton.turns[kOpponentStash][kBlue] = -300 / 2;

  auton.turns[kOpponentStashParalell][kRed] = 230;
  auton.turns[kOpponentStashParalell][kBlue] = -300 / 2;

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

  // Hanging Zone block and push autonomous
  auton.turns[kPushBuckies][kBlue] = -300;
  auton.turns[kPushBuckies][kRed] = 460;

  // Set default auton
  AutonSetZone(kMiddleZone);
  AutonSetColor(kBlue);
}

int AutonGetTurnTicks(Turn turn, TeamColor color)
{
  return auton.turns[turn][color];
}

void AutonTurn(Turn turn, TeamColor color, float percent)
{
  DriveTurnTicks( AutonGetTurnTicks(turn, color), percent );
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

void AutonSetRoutine(short routine)
{
  auton.routine = routine;
}

short AutonGetRoutine()
{
  return auton.routine;
}

void AutonStepRoutine()
{
  writeDebugStreamLine("Call to AutonStepRoutine");

  short routine_id = AutonGetRoutine();
  short num_routines;

  // Set num_routines to the number of routines avaliable for the selected zone
  if ( AutonGetZone() == kMiddleZone )
    num_routines = kNumMiddleRoutines;
  else
    num_routines = kNumHangingRoutines;

  // If the last routine is selected, select the first routine, otherwise,
  // select the next routine
  if ( routine_id == num_routines - 1)
    AutonSetRoutine(0);
  else
    AutonSetRoutine(routine_id + 1);
}

void AutonRun()
{
  LiftControlReset();

  // Print a message that says AutonRun was called
  writeDebugStreamLine("Call to AutonRun\n");

  // Get the team color
  TeamColor color = AutonGetColor();

  // Print the color of the autonomous
  if (color == kRed)
    writeDebugStreamLine("Autonomous color is red");
  else
    writeDebugStreamLine("Autonomous color is blue");

  // Run the appropriate autonomous routine
  if ( AutonGetZone() == kHangingZone )
  {
    if ( AutonGetRoutine() == kPush)
      AutonHangingPush(color);
    if ( AutonGetRoutine() == kBlockAndPush)
      AutonHangingBlockPush(color);
  }
  else
  {
    if ( AutonGetRoutine() == kStash)
      AutonMiddleStash(color);
    if ( AutonGetRoutine() == kBlock)
      AutonMiddleBlock(color);
  }
}

#endif /* AUTON */

/*void AutonStashThreeHanging(TeamColor color)
{
  // Start counting the time
  ClearTimer(T1);

  // Set the intake in to flip it out and get ready to intake the two buckies, leave it on
  // to keep buckies from falling out
  IntakeSetPower(kIntakeInPower);

  // Keep the lift down
  LiftSetPower(-15);

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

  // Raise the lift in the background
  LiftControlMoveToPosAsync(kLiftUpPos);

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
}*/
