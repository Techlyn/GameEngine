#include <ctime>
#include <stdio.h>
#include <math.h>

#include "Utility.h"

namespace Utility {

	char* Utility::getTimeString() {
		static char time_str[30];

		time_t now;
		time(&now);
		struct tm p_time;
		localtime_s(&p_time, &now);

		sprintf_s(time_str, "%02d:%02d:%02d", p_time.tm_hour, p_time.tm_min, p_time.tm_sec);

		return time_str;

	}

	bool Utility::positionsIntersect(df::Vector p1, df::Vector p2) {
		if (fabsf(p1.getX() - p2.getX()) <= 1 &&
			fabsf(p1.getY() - p2.getY()) <= 1) {
			return true;
		}
		return false;
	}
}