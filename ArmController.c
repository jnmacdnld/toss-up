#ifndef ARM_CONTROLLER_C
#define ARM_CONTROLLER_C

#include "PidLib.c"
#include "Arm.c"

#define kP 0.0
#define kI 0.0
#define kD 0.0
#define kBias 0.0

typedef struct {
  pidController* pid;
  bool enabled
} ArmController;

static ArmController arm_controller;

void ArmControllerInit()
{
  // Initialize the PID controller structure
  arm_controller.pid = PidControllerInit(kP, kI, kD, kBias, armPot);
}

void ArmControllerSetTarget(short target)
{
  // Enable the arm controller in case it has been disabled
  ArmControllerEnable();

  arm_controller.pid->target_value = target;
}

void ArmControllerUpdate()
{
  short power = PidControllerUpdate(arm_controller.pid);
  ArmSetPower(power);
}

void ArmControllerDisable()
{
  arm_controller.enabled = false;

  // Disable the PID controller
  arm_controller.pid->enabled = false;
}

void ArmControllerEnable()
{
  arm_controller.enabled = true;
  arm_controller.pid->enabled = true;
}

bool ArmControllerEnabled()
{
  return arm_controller.enabled;
}

task ArmController()
{
  // Update the arm controller every 25 ms
  while (true)
  {
    if (arm_controller.enabled)
      ArmControllerUpdate();

    wait1Msec(25);
  }
}

#endif
