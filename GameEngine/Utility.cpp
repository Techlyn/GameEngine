//
// Utility.cpp
//

// system includes
#include <ctime>
#include <stdio.h>
#include <math.h>


// engine includes
#include "Utility.h"


namespace df {


	char* getTimeString() {
		static char time_str[30];

		time_t now;
		time(&now);
		struct tm p_time;
		localtime_s(&p_time, &now);

		sprintf_s(time_str, "%02d:%02d:%02d", p_time.tm_hour, p_time.tm_min, p_time.tm_sec);

		return time_str;

	}

	bool positionsIntersect(df::Vector p1, df::Vector p2) {
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

	bool boxIntersectsBox(Box A, Box B) {
		// Test horizontal overlap (x_overlap).
		bool x_overlap = false;
		if (B.getCorner().getX() <= A.getCorner().getX() && A.getCorner().getX() <= B.getCorner().getX() + B.getHorizontal()) {
			if (A.getCorner().getX() <= B.getCorner().getX() && B.getCorner().getX() <= A.getCorner().getX() + A.getHorizontal()) {
				x_overlap = true;
			}
		}

		bool y_overlap = false;
		if (B.getCorner().getY() <= A.getCorner().getY() && A.getCorner().getY() <= B.getCorner().getY() + B.getVertical()) {
			if (A.getCorner().getY() <= B.getCorner().getY() && B.getCorner().getY() <= A.getCorner().getY() + A.getVertical()) {
				y_overlap = true;
			}
		}

		if (x_overlap && y_overlap) {
			return true;
		}
		return false;
	}


	Box getWorldBox(const Object* p_o) {

		Box box = p_o->getBox();
		Vector corner = box.getCorner();

		corner.setX(corner.getX() + p_o->getPosition().getX());
		corner.setY(corner.getY() + p_o->getPosition().getY());
		box.setCorner(corner);

		return box;

	}

	Box getWorldBox(const Object* p_o, Vector where) {
		
		Box box = getWorldBox(p_o);
		Vector corner = box.getCorner();

		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		box.setCorner(corner);

		return box;
	}
	
} // namespace df