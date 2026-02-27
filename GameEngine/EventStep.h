//
// EventStep.h
//

#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

#include "Event.h"


namespace df {

	const std::string STEP_EVENT = "df::step";
	
	class EventStep : public Event {
	private:

		
		const std::string CLASS_NAME = "EventStep";

		long long m_step_count;

	public:

		// Default constructor.
		EventStep();

		EventStep(long long init_step_count);

		// Set step count.
		void setStepCount(long long new_step_count);

		// Get step count.
		long long getStepCount() const;


	};
}


#endif // __EVENT_STEP_H__