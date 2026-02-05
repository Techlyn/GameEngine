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

		int m_step_count;

	public:

		// Default constructor.
		EventStep();

		EventStep(int init_step_count);

		// Set step count.
		void setStepCount(int new_step_count);

		// Get step count.
		int getStepCount() const;


	};
}


#endif // __EVENT_STEP_H__