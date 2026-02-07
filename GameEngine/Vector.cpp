//
// Vector.cpp
//


#include "Vector.h"

#include <math.h>

namespace df {



	Vector::Vector() {
		
		m_x = 0.0f;
		m_y = 0.0f;
	}

	Vector::Vector(float init_x, float init_y) {
		
		m_x = init_x;
		m_y = init_y;
	}

	/*Vector::Vector(int init_x, int init_y) {
		m_x = static_cast<float>(init_x);
		m_y = static_cast<float>(init_y);
	}*/

	
	void Vector::setX(float new_x) {
		m_x = new_x;

	}

	float Vector::getX() const {
		return m_x;
	}


	void Vector::setY(float new_y) {
		m_y = new_y;

	}

	float Vector::getY() const {
		return m_y;
	}

	void Vector::setXY(float new_x, float new_y) {
		m_x = new_x;
		m_y = new_y;
	}

	float Vector::getMagnitude() const {
		return sqrt(m_x * m_x + m_y * m_y);

	}

	Vector Vector::normalize() {
		Vector v = *this;
		float length = getMagnitude();
		if (length > 0) {
			v.m_x = m_x / length;
			v.m_y = m_y / length;
		}
		return v;
	}

	Vector Vector::scale(float s) {
		m_x = m_x * s;
		m_y = m_y * s;
		return *this;
	}

	Vector Vector::operator+(const Vector& other) const {
		Vector v;
		v.m_x = m_x + other.m_x;
		v.m_y = m_y + other.m_y;
		return v;
	}

	Vector Vector::operator-(const Vector& other) const {
		Vector v;
		v.m_x = m_x - other.m_x;
		v.m_y = m_y - other.m_y;
		return v;
	}

	Vector Vector::operator*(const Vector& other) const {
		Vector v;
		v.m_x = m_x * other.m_x;
		v.m_y = m_y * other.m_y;
		return v;
	}
	
	Vector Vector::operator/(const Vector& other) const {
		Vector v;
		v.m_x = m_x / other.m_x;
		v.m_y = m_y / other.m_y;
		return v;
	}

	Vector Vector::operator=(const Vector& other) {
		if (this != &other) {
			m_x = other.m_x;
			m_y = other.m_y;
		}
		return *this;
	}

	bool Vector::operator!=(const Vector& other) {
		return (m_x != other.m_x) || (m_y != other.m_y);
	}

	bool Vector::operator==(const Vector& other) {
		return (m_x == other.m_x) && (m_y == other.m_y);
	}

}
