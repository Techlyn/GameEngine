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
		float A_left = A.getCorner().getX();
		float A_right = A_left + A.getHorizontal();
		float A_top = A.getCorner().getY();
		float A_bottom = A_top + A.getVertical();

		float B_left = B.getCorner().getX();
		float B_right = B_left + B.getHorizontal();
		float B_top = B.getCorner().getY();
		float B_bottom = B_top + B.getVertical();

		bool x_overlap = !(A_right <= B_left || A_left >= B_right);
		bool y_overlap = !(A_bottom <= B_top || A_top >= B_bottom);

		return x_overlap && y_overlap;
	}


	Box getWorldBox(const Object* p_o) {
		return getWorldBox(p_o, p_o->getPosition());
	}

	Box getWorldBox(const Object* p_o, Vector where) {
		
		Box box = p_o->getBox();
		Vector corner = box.getCorner();

		corner.setX(corner.getX() + where.getX());
		corner.setY(corner.getY() + where.getY());
		box.setCorner(corner);

		return box;
	}

	bool valueInRange(float value, float min, float max) {
		if (value > min && value < max) {
			return true;
		}
		return false;
	}

	bool boxContainsPosition(Box b, Vector p) {
		Vector corner = b.getCorner();
		Vector opCorner = Vector(b.getCorner().getX() + b.getHorizontal(),
			b.getCorner().getY() + b.getVertical());

		if (p.getX() > corner.getX() && p.getX() < opCorner.getX()) {
			if (p.getY() > corner.getY() && p.getY() < opCorner.getY()) {
				return true;
			}
		}
		return false;
	}

	bool boxContainsBox(Box b1, Box b2) {
		
		//Note: does not account for rotation only parrellel boxes.


		float b1Length = (static_cast<float>(b1.getHorizontal()) * b1.getHorizontal()) + (b1.getVertical() * b1.getVertical());
		float b2Length = (static_cast<float>(b2.getHorizontal()) * b2.getHorizontal()) + (b2.getVertical() * b2.getVertical());

		// checks the length between the two furthest points
		if (b1Length > b2Length) {
			if (b1.getCorner().getX() < b2.getCorner().getX()) {
				if (b1.getCorner().getY() < b2.getCorner().getY()) {
					return true;
				}
			}
		}
		return false;
	}

	bool lineIntersectsLine(Line line1, Line line2) {
		Vector A = line1.getStartPoint();
		Vector B = line1.getEndPoint();
		Vector C = line2.getStartPoint();
		Vector D = line2.getEndPoint();

		return (ccw(A, B, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D));
	}

	bool ccw(Vector A, Vector B, Vector C) {
		return (A.getY() - C.getY()) * (B.getX() - A.getX() > B.getY() - A.getY()) * C.getX() - A.getX();
	}

	bool lineIntersectBox(Line line, Box b) {
		Line A(b.getCorner(), Vector(b.getCorner().getX() + b.getHorizontal(), b.getCorner().getY()));
		Line B(Vector(b.getCorner().getX() + b.getHorizontal(), b.getCorner().getY()),
			Vector(b.getCorner().getX() + b.getHorizontal(), b.getCorner().getY() + b.getVertical()));
		Line C(Vector(b.getCorner().getX() + b.getHorizontal(), b.getCorner().getY() + b.getVertical()),
			Vector(b.getCorner().getX(), b.getCorner().getY() + b.getVertical()));
		Line D(Vector(b.getCorner().getX(), b.getCorner().getY() + b.getVertical()), b.getCorner());

		if (lineIntersectsLine(line, A) 
			|| lineIntersectsLine(line, B) 
			|| lineIntersectsLine(line, C) 
			|| lineIntersectsLine(line, D)){

			return true; // if any cases are true.
		}
	
	}

	bool CircleContainsPosition(Circle circle, Vector position) {
		float dx = position.getX() - circle.getCenter().getX();
		float dy = position.getY() - circle.getCenter().getY();
		return(dx * dx + dy * dy) <= (circle.getRadius() * circle.getRadius());
	}

	bool CircleIntersectBox(Circle circle, Box b) {
		Vector circleDistance;
		circleDistance.setX(abs(circle.getCenter().getX() - b.getCorner().getX()));
		circleDistance.setY(abs(circle.getCenter().getY() - b.getCorner().getY()));

		if (circleDistance.getX() > (b.getHorizontal() / 2 + circle.getRadius())) { return false; }
		if (circleDistance.getY() > (b.getVertical() / 2 + circle.getRadius())) { return false; }

		if (circleDistance.getX() <= (b.getHorizontal() / 2)) { return true; }
		if (circleDistance.getY() <= (b.getVertical() / 2)) { return true; }

		float cornerDistance_sq = pow(circleDistance.getX() - b.getHorizontal() / 2, 2) + pow(circleDistance.getY() - b.getVertical() / 2, 2);

		return (cornerDistance_sq <= pow(circle.getRadius(), 2));
	}
	
} // namespace df