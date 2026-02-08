#include "Saucer.h"

Saucer::Saucer() {
	df::LogManager::getInstance().writeLog("%s: created at %p", __func__, this);
	setType("Saucer");
}

int Saucer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		return 1;
	}
	return 0;
}