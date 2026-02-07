//
// LogManager.h
//
#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// System includes
#include <iostream>
#include <unordered_map>
#include <string>

// Engine inclues
#include "Manager.h"

#define LM df::LogManager::getInstance()

namespace df {


	const std::string LOGFILE_NAME = "testlog.log";


	class LogManager : public Manager {


	public:

		// enum declaring different log levels 
		enum LogLevel {
			LOG_NONE = 0,
			LOG_ERROR,
			LOG_WARNING,
			LOG_INFO,
			LOG_DEBUG,
			LOG_TRACE
		};

		// If logfile is open, close it.
		~LogManager();

		// Get the one and only instance of the LogManager.

		static LogManager& getInstance();

		// Used to set the level logged, levels are - LOG_NONE
		// LOG_ERROR, LOG_WARNING, LOG_INFO, LOG_DEBUG, LOG_TRACE
		void setGlobalLevel(LogLevel level);
		bool setClassLevel(const std::string& className, LogLevel level);
		//LogLevel getClassLevel(const std::string& className) const;



		// Start up the LogManager (opening logfile "DECLARED_FILE_NAME.log")

		int startUp();


		// Shut down the LogManager (closes the logfile).
		void shutDown();

		// Set flush of logfile after each write.
		void setFlush(bool do_flush = true);


		// Write to logfile. Supports printf() formatting of strings.
		// Return number of bytes written, -1 if error.

		const char* levelToString(LogLevel level);

		bool shouldLogClass(const std::string& className, LogLevel level);

		void writeLog(const char* fmt, ...);

		void writeLog(LogLevel level, const char* fmt, ...);

		void writeLog(const std::string& className, LogLevel level, const char* format, ...);

	private:
		LogManager();
		LogManager(LogManager const&);		// Don't allow copy
		void operator=(LogManager const&);	// Don't allow assignment.
		bool m_do_flush;				// True if flush to disk after each write.
		FILE* m_p_f;					// Pointer to logfile struct.


		LogLevel globalLevel;
		std::unordered_map<std::string, LogLevel> classLevels;

	}; // end class LogManager
} // end namespace df
#endif //end of __LOG_MANAGER_H__