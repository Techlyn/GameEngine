//
// Object.h
// 

#ifndef __OBJECT_H__
#define __OBJECT_H__

// System includes
#include <string>

// Engine includes
#include "Event.h"
#include "Vector.h"
#include "Animation.h"
#include "Box.h"

namespace df {

	enum Solidness {
		HARD,		// Object causes collisions, and impedes. (object default)
		SOFT,		// Object causes collisions, but does not impede.
		SPECTRAL,	// Object doesn't cause collisions.
	};

	const int MAX_OBJ_EVENTS = 100;


	class Object {

		std::string CLASS_NAME = "Object";

		int m_id;				// Object unique identifier
		std::string m_type;		// Object type
		Vector m_position;		// Position of object
		int m_altitude;			// 0 to MAX supported (lower drawn first)
		Vector m_direction;		// Direction vector
		float m_speed;			// Object speed in direction.
		Solidness m_solidness;	// Solidness of object, used for collision detection.
		bool m_no_soft;			// True if object should not cause soft collisions (default is false).
		Animation m_animation;   // Animation associated with Object.
		Box m_box;				// Box for sprite boundary & collisions

		int event_count;
		std::string event_name[MAX_OBJ_EVENTS];

		bool is_active;


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

		// True if HARD or SOFT, else false.
		bool isSolid() const;

		// Set object solidness, which checks for consistency.
		// Return 0 if ok, else -1.
		int setSolidness(Solidness new_solid);

		// Return objects solidness
		Solidness getSolidness() const;

		// Set 'no soft' setting (true -- cannot move onto SOFT object).
		void setNoSoft(bool new_no_soft = true);

		// Get 'no soft' setting (true -- cannot move onto SOFT Objects).
		bool getNoSoft() const;

		// Set Sprite for this Object to animate.
		// Return 0 if ok, else -1.
		int setSprite(std::string sprite_label);

		// Set Animation for this Object to new one.
		// Set bounding box to size of associated Sprite.
		void setAnimation(Animation new_animation);

		// Get Animation for this Object.
		Animation getAnimation() const;

		// Set Object's bounding box.
		void setBox(Box new_box);

		// Get Object's bounding box.
		Box getBox() const;
		
		// Register for interest in event.
		// Keeps track of manager an event.
		// Returns 0 if ok, else -1.
		int registeredInterest(std::string event_type);

		// Unregister for interest in event.
		// Return 0 if ok, else -1.
		int unregisterInterest(std::string event_type);

		// Set activeness of Object. Objects not active are not acted upon
		// by engine.
		// Return 0 if ok, else -1.
		int setActive(bool active = true);

		// Return activeness of Object. Objects not active are not acted upon
		// by engine.
		bool isActive() const;



	}; // end class Object
} // end namespace df
#endif // __OBJECT_H__