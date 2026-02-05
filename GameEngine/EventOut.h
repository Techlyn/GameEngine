//
// EventOut.h
//

#ifndef __EVENT_OUT_H__
#define __EVENT_OUT_H__

// Engine includes
#include "Event.h"

namespace df {

	const std::string OUT_EVENT = "df::out";

	class EventOut : public Event {
	public:
		// Create EventOut with default values.
		EventOut();
	};
}

#endif // __EVENT_OUT_H__