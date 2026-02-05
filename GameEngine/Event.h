//
// Event.h
//

#ifndef __EVENT_H__
#define __EVENT_H__

// system Includes
#include <string>

// engine includes


namespace df {

	const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {

	private:
		
		//static LogManager& log;
		const std::string CLASS_NAME = "Event";

		std::string m_event_type;

	public:
		// Create base event
		Event();

		// Destructor
		virtual ~Event();

		void setType(std::string new_type);

		std::string getType() const;


	};
}

#endif // __EVENT_H__
