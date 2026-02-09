//
// Line.h
//

#ifndef __LINE_H__
#define __LINE_H__

#include "Vector.h"

namespace df {

	class Line {
	private:
		Vector m_startPoint;	// Where the line starts
		Vector m_endPoint;		// Where the line ends

	public:
		// Create line with (0,0) for both vector points.
		Line();

		// Create line with both vector points declared on init
		Line(Vector init_startPoint, Vector init_endPoint);

		// Set the starting point of the line.
		void setStartPoint(Vector new_startPoint);
		
		// Get the starting point of the line
		Vector getStartPoint() const;

		// Set the end point of the line.
		void setEndPoint(Vector new_endPoint);

		// Get the end point of the line.
		Vector getEndPoint() const;

	};



	

}



#endif // __LINE_H__