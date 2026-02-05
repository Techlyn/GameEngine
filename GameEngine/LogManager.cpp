//
// LogManager.cpp
//

#include <stdarg.h>
#include <stdio.h>


#include "LogManager.h"
#include "Utility.h"


namespace df {

#define LM df::LogManager::getInstance();

	LogManager::LogManager() {
		setType("LogManager");

		globalLevel = LOG_INFO;

		m_do_flush = false;
		m_p_f = NULL;

		
	}

	LogManager::~LogManager() {
		if (m_p_f != NULL) {
			fclose(m_p_f);
			m_p_f = NULL;
		}
	}

	void LogManager::operator=(LogManager const&) {


	}

	LogManager& LogManager::getInstance() {
		static LogManager instance;
		return instance;
	}

	void LogManager::setGlobalLevel(LogLevel level) {
		globalLevel = level;
		writeLog(LOG_INFO, "Global log level set to %s", levelToString(level));
	}

	bool LogManager::setClassLevel(const std::string& className, LogLevel level) {
		// Check that the level is valid
		if (globalLevel < LOG_NONE || globalLevel > LOG_TRACE) {
			writeLog(LOG_ERROR, "Attempt made to set log level %d for class %s", level, className.c_str());
			return false;
		}

		// checks to make sure className string has been entered writes error if true.
		if (className.empty()) {
			writeLog(LOG_ERROR, "class name empty on attempt");
			return false;
		}

		//adds class and level to unordered_map
		classLevels[className] = level;

		const char* levelStr = levelToString(level);

		writeLog(LOG_INFO, "class [%s] set to level [%s]: SUCCESS", className.c_str(), levelToString(level));
		return true;
	}

	int LogManager::startUp() {
		if (isStarted()) return 0;
		Manager::startUp();

		const char* cstr = LOGFILE_NAME.c_str();

		//opens logfile to be written
		
		fopen_s(&m_p_f, cstr, "w");

		if (m_p_f == NULL) {
			return 1;
		}
		else {
			return 0;
		}

	}

	void LogManager::shutDown() {
		fclose(m_p_f);

		Manager::shutDown();
	}

	void LogManager::setFlush(bool do_flush) {
		m_do_flush = do_flush;
	}

	const char* LogManager::levelToString(LogLevel level) {
		switch (level) {
		case LOG_NONE: return "NONE";
		case LOG_ERROR: return "ERROR";
		case LOG_WARNING: return "WARNING";
		case LOG_INFO: return "INFO";
		case LOG_DEBUG: return "DEBUG";
		case LOG_TRACE: return "TRACE";
		default:		return "UNKNOWN";
		}
	}

	bool LogManager::shouldLogClass(const std::string& className, LogLevel level){
		// Check to see if class has specific level set.
		 auto sp = classLevels.find(className);
		if (sp != classLevels.end()) {
			return level <= sp->second;
		}

		return level <= globalLevel;

	}



	void LogManager::writeLog(const char* fmt, ...){
		
		if (m_p_f != NULL) {
			fprintf(m_p_f, "%s:: ", Utility::getTimeString());
		}
		fprintf(stderr, "%s:: ", Utility::getTimeString());

		va_list args;
		va_start(args, fmt);
		if (m_p_f != NULL) {
			vfprintf(m_p_f, fmt, args);
		}
		vfprintf(stderr, fmt, args);
		va_end(args);
		if (m_p_f != NULL) {
			fputs("\n", m_p_f);
		}
		fputs("\n", stderr);

		if (m_do_flush == true) {
			if (m_p_f != NULL) {
				fflush(m_p_f);
			}
			fflush(stderr);
		}
		
	}

	void LogManager::writeLog(LogLevel level, const char* fmt, ...){
		if (level > globalLevel) return;

		const char* levelStr = levelToString(level);

		char buffer[1028];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buffer, sizeof(buffer), fmt, args);
		va_end(args);
	/*	fputs("\n", stderr);*/

		writeLog("[%s] %s", levelStr, buffer);
	}

	void LogManager::writeLog(const std::string& className, LogLevel level, const char* fmt, ...){
		
		if (!shouldLogClass(className, level)) return;

		char message[1028];
		va_list args;
		va_start(args, fmt);
		vsnprintf(message, sizeof(message), fmt, args);
		va_end(args);

		const char* levelStr = levelToString(level);

		writeLog("[%s] [%s] %s", levelStr, className.c_str(), message);
		
	}


}

