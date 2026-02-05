#include <Windows.h>

#include "Clock.h"



namespace df {

	LogManager& Clock::log = LogManager::getInstance();

	Clock::Clock() {

		log.writeLog(CLASS_NAME, LogManager::LOG_INFO, "%s created at %p",__func__, this);

		// on initialization collects time as of now and stores in SYSTEMTIME now
		SYSTEMTIME now;
		GetSystemTime(&now);
		//calculates time and stores in Clock data member m_previous_time which initializes the data member
		m_previous_time = (now.wHour * 3600000) + (now.wMinute * 60000)
			+ (now.wSecond * 1000)
			+ (now.wMilliseconds);


	}


	long int Clock::delta() {
		// when delta() called collects time and stores in *before*
		SYSTEMTIME before;
		GetSystemTime(&before);
		//stores *before* in data member m_previous_time 
		// used at the start of a loop to get it's start time
		m_previous_time = (before.wHour * 3600000) + (before.wMinute * 60000)
			+ (before.wSecond * 1000)
			+ (before.wMilliseconds);

		return m_previous_time;


	}

	long int Clock::split() const {
		// when split() called collects time and stores in *after*
		SYSTEMTIME after;
		long int after_time;
		GetSystemTime(&after);
		// calculates the same values that m_previous_time is used with the same calculation.
		after_time = (after.wHour * 3600000) + (after.wMinute * 60000)
			+ (after.wSecond * 1000)
			+ (after.wMilliseconds);

		//returns the elapsed time between delta() and split().
		// example:
		// delta();
		// ~do actions~
		// split();
		// returns time taken to complete actions in milliseconds
		return  after_time - m_previous_time;

	}
}