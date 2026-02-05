//
// Vector.h
//

#ifndef __VECTOR_H__
#define __VECTOR_H__



namespace df {
	class Vector {

	private:

		float m_x; // Horizontal component.
		float m_y; // Vertical component.

	public:

		// Create Vector with (x,y).
		Vector(float init_x, float init_y);

		Vector(int init_x, int init_y);

		Vector();

		// Set horizontal component
		void setX(float new_x);
		float getX() const;

		// Set vertical component
		void setY(float new_y);
		float getY() const;

		// Set horizontal and vertical components.
		void setXY(float new_x, float new_y);

		// Return magnitude of vector.
		float getMagnitude() const;

		// Normalize vector
		Vector normalize();

		// Scale vector
		Vector scale(float s);

		// Add two Vectors. return new vector.
		Vector operator+(const Vector& other) const;
		// Subtracts two vectors, return new vector
		Vector operator-(const Vector& other) const;
		// Multiplies two vectors, returns new vector.
		Vector operator*(const Vector& other) const;
		// Divides two vectors, returns new vector.
		Vector operator/(const Vector& other) const;
		// Asign the value of
		Vector operator=(const Vector& other) ;
		// Is not equal to..
		bool operator!=(const Vector& other);
		// is equal to..
		bool operator==(const Vector& other);
	};
}
#endif // __VECTOR_H__

