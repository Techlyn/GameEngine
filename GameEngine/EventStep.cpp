#include "EventStep.h"

namespace df {

	

	EventStep::EventStep() {

		

		setType(STEP_EVENT);
		m_step_count = 0;
	}

	EventStep::EventStep(long long init_step_count) {

		setType(STEP_EVENT);
		m_step_count = init_step_count;
	}

	void EventStep::setStepCount(long long new_step_count) {
		m_step_count = new_step_count;
	}

	long long EventStep::getStepCount() const {
		return m_step_count;
	}

}