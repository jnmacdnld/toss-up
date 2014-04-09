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

#define kNumAutonTurns 6

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

#define kNumMiddleRoutines 3
#define kNumHangingRoutines 2

typedef enum { kInsideBigBall, kHangingLargeBall, kPivotForwards, kPivotInside, kPivotStash, kStashInsideLargeBall } Turn;
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

void AutonHangingZoneStash(TeamColor color);
void AutonTurn(Turn turn, TeamColor color, float percent = 0.7);

void AutonSetZone(Zone zone);
void AutonSetColor(TeamColor color);

void AutonStepRoutine();

void AutonInit()
{
  // Middle Zone autonomous
  auton.turns[kInsideBigBall][kRed] = 231;
  auton.turns[kInsideBigBall][kBlue] = -184;

  // Middle Zone stash autonomous
  auton.turns[kStashInsideLargeBall][kRed] = -300;
  auton.turns[kStashInsideLargeBall][kBlue] = 391;

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

void AutonMiddleZone(TeamColor color)
{
  // Flip out the intake
  IntakeSetPower(kIntakeInPower);
  wait1Msec(250);
  IntakeSetPower(0);

  // Move the lift to the barrier height
  LiftControlMoveToPosSync(kLiftBarrierPos);

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
  
  // Store the initial position of the robot
  short initial = nMotorEncoder[backLeftDrive];

  // Keep driving forwards
  DriveSetPower(kFullPower);

  // Wait until the robot has moved under the barrier
  while (nMotorEncoder[backLeftDrive] < initial + 1315 - 300);

  // Stop the intake
  IntakeSetPower(0);

  // Raise the lift in the background
  LiftControlMoveToPosAsync(kLiftUpPos);

  // Store the initial position of the robot
  initial = nMotorEncoder[backLeftDrive];

  // Keep driving forwards
  DriveSetPower(kFullPower);

  // Wait until the robot has moved close to the stash
  while (nMotorEncoder[backLeftDrive] < initial + 679);

  // Drive up to the stash
  DriveSetPower(kFullPower * 0.85);

  // Set the timeout to reach the stash
  ClearTimer(T1);

  // Keep driving until the robot reaches the stash or one second has passed
  while (SensorValue[stashSonar] > 30 && time1[T1] < 750);

  // Stop moving forward
  DriveSetPower(0);

  // Eject the preload
  IntakeSetPower(kIntakeOutSlowPower);
  wait1Msec(1000);
  IntakeSetPower(0);
  
  // Store the initial position of the robot
  initial = nMotorEncoder[backLeftDrive];

  // Keep driving backwards
  DriveSetPower(-kFullPower);

  // Wait until the robot has moved away from the stash
  while (nMotorEncoder[backLeftDrive] > initial - 50);

  // Lower the lift in the background
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Drive backwards to the starting tile
  DriveMoveTicks(-1712, 1.0);

  // Wait until the repositioning button is pressed
  while (!SensorValue[touch]);
  writeDebugStreamLine("Repositioning button pressed");

  // Wait until the button is released, indicating the robot has been repositioned
  while (SensorValue[touch]);
  writeDebugStreamLine("Repositioning button released");

  // Move the lift to barrier height in the background
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  // Drive forwards even with the second large ball
  DriveMoveTicks(963, 1.0);

  // Pivot to face the large ball
  AutonTurn(kStashInsideLargeBall, color, 0.85);

  // Drive forwards to knock the large ball into the goal zone
  DriveMoveTicks(600, 1.0);

  // Drive backwards away from the barrier
  DriveMoveTicks(-300, 1.0);

  // Lower the lift
  while (true)
    LiftControlMoveToPosAsync(kLiftDownPos);
}

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
    if ( AutonGetRoutine() == kPush)
      AutonHangingZone(color);
  else
    if ( AutonGetRoutine() == kStash)
      AutonMiddleZoneStash(color);
}

#endif /* AUTON */
