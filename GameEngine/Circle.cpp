//
// Circle.cpp
//

#include "Circle.h"

namespace df {

	Circle::Circle() {
		m_center = Vector(0, 0);
		m_radius = 0;
	}

	Circle::Circle(Vector init_center, float init_radius) {
		m_center = init_center;
		m_radius = init_radius;
	}

	void Circle::setCenter(Vector new_center) {
		m_center = new_center;
	}

	Vector Circle::getCenter() const {
		return m_center;
	}

	void Circle::setRadius(float new_radius) {
		m_radius = new_radius;
	}

	float Circle::getRadius() const {
		return m_radius;
	}
}