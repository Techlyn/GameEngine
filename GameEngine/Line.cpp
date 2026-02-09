//
// Line.cpp
//

#include "Line.h"


namespace df {

	Line::Line() {
		m_startPoint = Vector(0, 0);
		m_endPoint = Vector(0, 0);
	}

	Line::Line(Vector init_startPoint, Vector init_endPoint) {
		m_startPoint = init_startPoint;
		m_endPoint = init_endPoint;
	}

	void Line::setStartPoint(Vector new_startPoint) {
		m_startPoint = new_startPoint;
	}

	Vector Line::getStartPoint() const {
		return m_startPoint;
	}

	void Line::setEndPoint(Vector new_endPoint) {
		m_endPoint = new_endPoint;
	}

	Vector Line::getEndPoint() const {
		return m_endPoint;
	}
}