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
#include "Object.h"



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
		


} // end namespace Utility

#endif // __UTILITY_H__


