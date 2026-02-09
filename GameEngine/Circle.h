//
// Circle.h
//

#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Vector.h"

namespace df {

	class Circle {
	private:
		Vector m_center;	// Center point of the circle.
		float m_radius;		// Radius of the circle.

	public:
		// Create circle with (0,0) for the center, and 0 for radius.
		Circle();

		// Create circle with a center point and radius.
		Circle(Vector init_center, float init_radius);

		// Set center of circle.
		void setCenter(Vector new_center);

		// Get center of circle.
		Vector getCenter() const;

		// Set radius of circle.
		void setRadius(float new_radius);

		// Get radius of circle.
		float getRadius() const;

		

	};

}

#endif // __CIRCLE_H__