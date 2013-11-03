  // Flip out the intake
  driveFlipOutIntake();

  // Drive forward to score the first big ball
  armControlMoveToPos(BARRIER_HEIGHT);
  driveControlMoveInches(35);
  WAIT_UNTIL { armControlFinished() && driveControlFinished() }

  // Drive back to the starting square
  driveControlMoveInches(-35);
  WAIT_UNTIL { driveControlFinished() }

  // Turn to face diagonally to the right
  driveControlTurnToAngle(450);
  WAIT_UNTIL { driveControlFinished() }

  // Move diagonally to score the second big ball  
  driveControlMoveInches(/* distance to barrier diagonally from starting square*/);
  WAIT_UNTIL { driveControlFinsihed() }

  // Drive backwards until the robot sees the line leading to the bucky tube

  // Turn to face straight towards the bucky tube and bring the arm down

  // Drive under the barrier

  // Raise the arm and drive up to the bucky tube

  // Score the bucky

  driveControlDisable();
  driveSetPower(FULL_POWER);
  WAIT_UNTIL { lineSensorMiddleSeeLine() }

  driveControlTurnToAngle(900);
