//
// EventCollision.h
// 

#ifndef __EVENT_COLLISION_H__
#define __EVENT_COLLISION_H__

// engine includes
#include "Event.h"
#include "Object.h"

namespace df {

	class EventCollision : public Event {
	public:
		Vector m_pos;	// Where collision occured.
		Object* m_p_obj1; // Object moving, causing collisions.
		Object* m_p_obj2; // Object being collided with.

	public:
		// Create collision event at 0,0 with null objects 1&2.
		EventCollision();


		// Create collision event between o1 and o2 at pos p.
		// Object o1 'caused' collision by moving into object o2
		EventCollision(Object* p_o1, Object* p_o2, Vector p);

		// set object causing the collision
		void setObject1(Object* p_new_o1);

		// Get object causing the collision
		Object* getObject1() const;

		// Set object being collided with
		void setObject2(Object* p_new_o2);

		// Get object being collided with
		Object* getObject2() const;

		// Set position of collision.
		void setPosition(Vector new_pos);

		// Return position of collision.
		Vector getPosition() const;
		
	}; // end class EventCollision

} // end namespace df


#endif // __EVENT_COLLISION_H__