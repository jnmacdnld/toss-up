#define ARM_UP_POS   3060
#define ARM_DOWN_POS 1400

#define ARM_UP_PWR    MAX_PWR
#define ARM_DOWN_PWR -MAX_PWR / 3
#define ARM_HOLD_PWR  10

#define armPos         SensorValue[armPot]

#define armDownPressed    vexRT[Btn6D]
#define armUpPressed      vexRT[Btn6U]
#define armUpMacroPressed vexRT[Btn7U]
#define armDownMacroPressed vexRT[Btn7D]

int armControlTarget = -1;
int armControlPwr = 0;
bool armControlActive = false;

void setArmPwr(int value);

bool armIsDown();
bool armIsUp();

void armUpPressedCb();
void armDownPressedCb();

void armControlSetTarget(int target);
void armControlStep();

void holdArmPos();
void updateArm();
