//
// Utility.h
//
#include "Vector.h"

namespace Utility {


	char* getTimeString();

	// Return true if two positions intersect, else false.
	bool positionsIntersect(df::Vector p1, df::Vector p2);


} // end namespace Utility

