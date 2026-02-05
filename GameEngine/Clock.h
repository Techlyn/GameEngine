// 
// Clock.h
//

#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "LogManager.h"

namespace df {

	class Clock {

	private:

		static df::LogManager& log;
		const std::string CLASS_NAME = "Clock";

		long int m_previous_time; // Previous time delta() called (in microsecs).

	public:
		// Sets previous_time to current time.
		Clock();

		// Return time elapsed since delta() was last called, -1 if error
		// Resets previous time.
		// Units are micoseconds.
		long int delta();

		// Return time elapsed since delta was last called, -1 if error.
		// does not reset previous time,
		// Units are microseconds.
		long int split() const;


	};

}
#endif // end of __CLOCK_H__