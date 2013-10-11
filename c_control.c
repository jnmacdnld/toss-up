#ifndef C_CONTROL
#define C_CONTROL

typedef struct {
	int original,
	int actual,
	int target,
	bool reachedTarget,
	int posCorrection,
	int negCorrection
} cController;

int cControllerUpdate(cController* c) {
	if (c->target < c->original && actual > target) {
		c->reachedTarget = false;
		return c->negCorrection;
	} else if (c->taget > c->original && c->actual < c->target) {
		c->reachedTarget = false;
		return c->posCorrection;
	} else {
		reachedTarget = true;
		return 0;
	}
}
 
#endif /* C_CONTROL */