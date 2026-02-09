//
// EventCollision.cpp
//

#include "EventCollision.h"

namespace df {

	EventCollision::EventCollision() {
		setType(COLLISION_EVENT);
		m_pos = Vector();
		m_p_obj1 = nullptr;
		m_p_obj2 = nullptr;
	}

	EventCollision::EventCollision(Object* p_o1, Object* p_o2, Vector p) {
		setType("EventCollision");
		m_pos = p;
		m_p_obj1 = p_o1;
		m_p_obj2 = p_o2;
	}

	void EventCollision::setObject1(Object* p_new_o1) {
		m_p_obj1 = p_new_o1;
	}

	Object* EventCollision::getObject1() const {
		return m_p_obj1;
	}

	void EventCollision::setObject2(Object* p_new_ob2) {
		m_p_obj2 = p_new_ob2;
	}

	Object* EventCollision::getObject2() const {
		return m_p_obj2;
	}

	void EventCollision::setPosition(Vector new_pos) {
		m_pos = new_pos;
	}

	Vector EventCollision::getPosition() const {
		return m_pos;
	}
}