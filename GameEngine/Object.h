//
// Object.h
// 

#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes
#include <string>

// Engine includes
#include "LogManager.h"
#include "Event.h"
#include "Vector.h"

namespace df {

	

	class Object {
		int m_altitude;		//0 to MAX supported (lower drawn first)
		Vector m_direction; // Direction vector
		float m_speed;		// Object speed in direction.

	public:
		// Construct Object. Set default parameters and
		// add to game world (WorldManager).
		Object();

		// Destroy Object.
		// Remove from game world (WorldManager).
		virtual ~Object();

		// Set Object id.
		void setId(int new_id);

		// Get Object id.
		int getId() const;

		// Set type identifier of Object.
		void setType(std::string new_type);

		// Get type identifier of Object.
		std::string getType() const;

		// Draw Object, animation and/or shape.
		// Return 0 if ok, else -1.
		virtual int draw();

		// Set position of Object.
		void setPosition(Vector new_pos);

		// Get position of Object.
		Vector getPosition() const;

		// Set altitude of Object, with checks for range [0, MAX_ALTITUDE]
		// return 0 if ok, else -1.
		int setAltitude(int new_altitude);

		// Return altitude of Object.
		int getAltitude() const;

		// Handle event (default is to ignore everything).
		// Return 0 if ignored, else 1 if handled.
		virtual int eventHandler(const Event* p_e);

		// Set speed of Object.
		void setSpeed(float speed);

		// Get speed of Object.
		float getSpeed() const;

		// Set Direction of Object.
		void setDirection(Vector new_direction);

		// Get Direction of Object.
		Vector getDirection() const;

		// Set direction and speed of Object.
		void setVelocity(Vector new_velocity);

		// Get velocity of Object based on direction and speed.
		Vector getVelocity() const;

		// Predict Object position based on speed and direction.
		// Return predicted position
		Vector predictPosition() const;

		


	private:

		static LogManager& log;
		std::string CLASS_NAME = "Object";

		int m_id;
		std::string m_type;
		Vector m_position;
		

	}; // end class Object
} // end namespace df
#endif // __OBJECT_H__