#ifndef AUTONOMOUS
#define AUTONOMOUS

#include "arm.c"
#include "drive.c"
#include "intake.c"

#define START_TO_BARRIER_TICKS 880
#define START_TO_BARRIER_INCHES 28.21
#define FIRST_TO_SECOND_BIG_BALL_INCHES 32.25

#define FIELD_TILE_WIDTH_INCHES 23.42

void AutonBlueMiddle() {
  armMoveToPos(ARM_BARRIER_POS);

  // Knock the first big ball into the goal zone and return 3 inches from the starting position
  driveMoveInches(START_TO_BARRIER_INCHES);
  driveMoveInches( (START_TO_BARRIER_INCHES - 3) * -1 );

  // Turn left and move to the second large ball
  driveTurnToDegrees(-90.0);
  driveMoveInches(FIRST_TO_SECOND_BIG_BALL_INCHES);

  // Turn towards the ball and knock it into the goal zone
  driveTurnToDegrees(0.0);
  driveMoveInches( START_TO_BARRIER_INCHES - 3);
}
 
void AutonBlueHanging() {
  // Pick up the two buckies in front of the robot
  setIntakePwr(INTAKE_IN_PWR);
  driveMoveInches(21.5);

  // Drive to the first big ball
  driveTurnToDegrees(90.0);

}

#endif /* AUTONOMOUS */
