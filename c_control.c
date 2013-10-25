#ifndef C_CONTROL
#define C_CONTROL

typedef struct {
	short original;
	short target;
	bool reachedTarget;
	short posCorrection;
	short negCorrection;
} cController;

int cControllerUpdate(cController* c, short actual) {
	if (c->target < c->original && actual > c->target) {
		c->reachedTarget = false;
		return c->negCorrection;
	} else if (c->target > c->original && actual < c->target) {
		c->reachedTarget = false;
		return (int) c->posCorrection;
	} else {
		c->reachedTarget = true;
		return 0;
	}
}

void cControllerSetTarget(cController* c, short target, short actual) {
	c->target = target;
	c->original = actual;
}

cController* cControllerInit(short posCorrection, short negCorrection) {
	cController c;
	c.posCorrection = posCorrection;
	c.negCorrection = negCorrection;

	return &c;
}

#endif /* C_CONTROL */
