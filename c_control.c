#ifndef C_CONTROL
#define C_CONTROL

typedef struct {
	int original;
	int target;
	bool reachedTarget;
	int posCorrection;
	int negCorrection;
} cController;

int cControllerUpdate(cController* c, int actual) {
	if (c->target < c->original && actual > c->target) {
		c->reachedTarget = false;
		return c->negCorrection;
	} else if (c->target > c->original && actual < c->target) {
		c->reachedTarget = false;
		return c->posCorrection;
	} else {
		c->reachedTarget = true;
		return 0;
	}
}

#endif /* C_CONTROL */
