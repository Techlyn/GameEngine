//
// EventMouse.h
//

#ifndef __EVENT_MOUSE_H__
#define __EVENT_MOUSE_H__
// Engine includes.
#include "Event.h"
#include "Vector.h"

namespace df {

	const std::string MSE_EVENT = "df::mouse";

	enum EventMouseAction {
		UNDEFINE_MOUSE_ACTION = -1,
		CLICKED,
		MOVED,
	};

	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	}

	class EventMouse : public Event {
	private:
		EventMouseAction m_mouse_action; // Mouse action.
		Mouse::Button m_mouse_button;    // Mouse button.
		Vector m_mouse_xy;				 // Mouse (x,y) coordinates.

	public:
		EventMouse();

		// Load mouse event's actions.
		void setMouseAction(EventMouseAction new_mouse_action);

		// Get mouse event's button.
		EventMouseAction getMouseAction() const;

		// Set mouse event's button.
		void setMouseButton(Mouse::Button new_mouse_button);

		// Get mouse event's button.
		Mouse::Button getMouseButton() const;

		// Set mouse event's position.
		void setMousePosition(Vector new_mouse_xy);

		// Set mouse event's position.
		Vector getMousePosition() const;
	}; // end class EventMouse

} // end namespace df

#endif // __EVENT_MOUSE_H__