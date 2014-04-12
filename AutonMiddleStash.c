#ifndef AUTON_MIDDLE_STASH
#define AUTON_MIDDLE_STASH

void AutonMiddleStash(TeamColor color)
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
  while (nMotorEncoder[backLeftDrive] < initial + 579);

  // Drive up to the stash
  DriveSetPower(kFullPower * 0.50);

  // Set the timeout to reach the stash
  ClearTimer(T1);

  // Keep driving until the robot reaches the stash or the timeout is reached
  while (SensorValue[stashSonar] > 30 && time1[T1] < 1250);

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

  // Wait until the button is released, indicating the robot has been repositioned
  while (SensorValue[touch]);

  // Move the lift to barrier height in the background
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  // Drive forwards even with the second large ball
  DriveMoveTicks(963, 1.0);

  // Pivot to face the large ball
  AutonTurn(kStashInsideLargeBall, color, 0.85);

  // Drive forwards to knock the large ball into the goal zone
  DriveMoveTicks(600, 1.0);

  // Wait so we don't grind gears
  wait1Msec(100);

  // Drive backwards away from the barrier
  DriveMoveTicks(-300, 1.0);

  // Lower the lift
  while (true)
    LiftControlMoveToPosAsync(kLiftDownPos);

  /*
  // Turn towards the opponent's stash
  AutonTurn(kOpponentStash, color, 0.85);

  // Drive up to the opponent's stash
  DriveMoveTicks(1770, 1.0);

  // Turn to face paralell to the opponent's stash
  AutonTurn(kOpponentStashParalell, color, 0.85);

  // Drive forwards to block the stash
  DriveMoveTicks(477, 1.0);*/
}

#endif