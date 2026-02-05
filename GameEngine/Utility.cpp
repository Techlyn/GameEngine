#include <ctime>
#include <stdio.h>

#include "Utility.h"

char* Utility::getTimeString() {
	static char time_str[30];

	time_t now;
	time(&now);
	struct tm p_time;
	localtime_s(&p_time, &now);

	sprintf_s(time_str, "%02d:%02d:%02d", p_time.tm_hour, p_time.tm_min, p_time.tm_sec);

	return time_str;

}