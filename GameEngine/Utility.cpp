//
// Utility.cpp
//

// system includes
#include <ctime>
#include <stdio.h>
#include <math.h>


// engine includes
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

	std::string trimString(std::string& str) {
		
		size_t start = str.find_first_not_of(" \t\n\r");
		if (start == std::string::npos)
			return ""; // String is all whitespace
		size_t end = str.find_last_not_of(" \t\n\r");
			return str.substr(start, end - start + 1);
	}

	df::Colour getColourFromString(std::string colour_str) {
		
		if (colour_str == "black") {
			return df::BLACK;
		}
		else if (colour_str == "red") {
			return df::RED;
		}
		else if (colour_str == "green") {
			return df::GREEN;
		}
		else if (colour_str == "yellow") {
			return df::YELLOW;
		}
		else if (colour_str == "blue") {
			return df::BLUE;
		}
		else if (colour_str == "magenta") {
			return df::MAGENTA;
		}
		else if (colour_str == "cyan") {
			return df::CYAN;
		}
		else if (colour_str == "white") {
			return df::WHITE;
		}
		else {
			return df::UNDEFINED_COLOUR;
		}
	
	}
}