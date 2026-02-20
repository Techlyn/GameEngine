//
// Manager.h
//

#ifndef __MANAGER_H__
#define __MANAGER_H__

// System includes
#include <string>

// Engine includes
//#include "Event.h"
#include "ObjectList.h"





namespace df {

	const int MAX_EVENTS = 100;

	class Event;
	class Object;

	class Manager {

	private:
		const std::string CLASS_NAME = "Manager";

		std::string m_type;			// Manager type identifier.
		bool m_is_started;			// True when started successfully.

		int event_count;					// Number of events
		std::string event[MAX_EVENTS];		// List of events
		ObjectList obj_list[MAX_EVENTS];	// Objects interested in event.

		
		


	protected:
		// Set type identifier of Manager.
		void setType(std::string type);

		// Check if event is handled by this Manager.
		// If handled, return true else false.
		// (Base Manager always returns false.
		virtual bool isValid(std::string event_name) const;

	public:
		Manager();
		virtual ~Manager();

		//Get type identifier of Manager
		std::string getType() const;

		// Startup Manager.
		// Return 0 if ok, else negative number.

		virtual int startUp();

		// Shutdown Manager
		virtual void shutDown();

		// Return true when startUp() was executed ok, else false.
		bool isStarted() const;

		// Send event to all interest Objects.
		// Return count of number of events sent
		int onEvent(const Event* p_e) const;

		// Indicate interest in event.
		// Return 0 if ok, else -1.
		// (Note, doesn't check to see if Object is already registered.).
		int registerInterest(Object* p_o, std::string event_type);

		// Indicate no more interest in event.
		// Return 0 if ok, else -1.
		int unregisterInterest(Object* p_o, std::string event_type);

		

	};

} // end of namespace df
#endif // end of __MANAGER_H__