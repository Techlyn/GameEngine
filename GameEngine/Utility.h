//
// Utility.h
//

#ifndef __UTILITY_H__
#define __UTILITY_H__

// system includes
#include <string>

// engine includes
#include "Vector.h"
#include "Colour.h"
#include "Box.h"
#include "Line.h"
#include "Object.h"
#include "Circle.h"



namespace df {

	
		// Return current time as string in format "hh:mm:ss".
		char* getTimeString();

		// Return true if two positions intersect, else false.
		bool positionsIntersect(df::Vector p1, df::Vector p2);

		// Helps trim whitespace from the beginning and end of a string.
		std::string trimString(std::string& str);

		// Convert string to colour. Return COLOUR_UNDEFINED if not valid colour.
		df::Colour getColourFromString(std::string colour_str);

		// Returns true if boxes intersect, else false.
		bool boxIntersectsBox(Box A, Box B);

		// Convert relative bounding Box for Object to absolute world Box.
		Box getWorldBox(const Object* p_o);
		Box getWorldBox(const Object* p_o, Vector where);

		// Return true value between min and max (inclusive).
		bool valueInRange(float value, float min, float max);

		// Return true if Box comaints Position
		bool boxContainsPosition(Box b, Vector p);

		// Return true if Box 1 complete contains Box 2.
		bool boxContainsBox(Box b1, Box b2);

		// Return true if line seqments intersect.
		// (Parallel line seqments don't intersect).
		bool lineIntersectsLine(Line line1, Line line2);

		// Find clockwise order, used to find lineIntersect.

		bool ccw(Vector A, Vector B, Vector C);

		// Return true if Line intersects Box.
		bool lineIntersectsBox(Line line, Box b);

		// Return true if Circle intersects or contains Box.
		bool circleIntersectsBox(Circle circle, Box b);

		// Return distance between any two positions.
		float distance(Vector p1, Vector p2);
		


} // end namespace Utility

#endif // __UTILITY_H__


