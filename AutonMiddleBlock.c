#ifndef AUTON_MIDDLE_BLOCK
#define AUTON_MIDDLE_BLOCK

void AutonMiddleBlock(TeamColor color)
{
  // Move the lift to barrier height in the background
  LiftControlMoveToPosAsync(kLiftBarrierPos);

  // Drive forwards even with the second large ball
  DriveMoveTicks(963 + 240, 1.0);

  // Pivot to face the large ball
  // AutonTurn(kStashInsideLargeBall, color, 0.85);

  // Drive forwards to knock the large ball into the goal zone
  DriveMoveTicks(600, 1.0);

  // Wait so we don't grind gears
  wait1Msec(100);

  // Drive backwards away from the barrier
  DriveMoveTicks(-300, 1.0);

  // Lower the lift
  LiftControlMoveToPosAsync(kLiftDownPos);

  // Turn towards the opponent's stash
  // AutonTurn(kOpponentStash, color, 0.85);

  // Drive up to the opponent's stash
  DriveMoveTicks(1770, 1.0);

  // Turn to face paralell to the opponent's stash
  // AutonTurn(kOpponentStashParalell, color, 0.85);

  // Drive forwards to block the stash
  DriveMoveTicks(477, 1.0);
}

#endif