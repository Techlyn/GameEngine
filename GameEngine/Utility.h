//
// Utility.h
//

// system includes
#include <string>

// engine includes
#include "Vector.h"
#include "Colour.h"



namespace Utility {

	// Return current time as string in format "hh:mm:ss".
	char* getTimeString();

	// Return true if two positions intersect, else false.
	bool positionsIntersect(df::Vector p1, df::Vector p2);

	// Helps trim whitespace from the beginning and end of a string.
	std::string trimString(std::string& str);

	// Convert string to colour. Return COLOUR_UNDEFINED if not valid colour.
	df::Colour getColourFromString(std::string colour_str);

} // end namespace Utility

