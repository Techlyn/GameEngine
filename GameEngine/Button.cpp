//
// Button.cpp
//

#include "Button.h"
#include "Utility.h"


namespace df {

	Button::Button() {

		m_highlight_colour = RED;
		m_default_colour = COLOUR_DEFAULT;

		registeredInterest(MSE_EVENT);

	}

	int Button::eventHandler(const Event* p_e) {

		if (p_e->getType() != MSE_EVENT) {
			return 0; // not handled
		}

		const EventMouse* p_mouse_event = dynamic_cast<const EventMouse*> (p_e);
		if (mouseOverButton(p_mouse_event)) {

			setColour(m_highlight_colour);

			if (p_mouse_event->getMouseAction() == CLICKED) {
				callback();
			}
		}
		else {
			setColour(m_default_colour);
		}

		

		// Event handled.
		return 1;

	}

	void Button::setHighlightColour(Colour new_highlight_colour) {
		m_highlight_colour = new_highlight_colour;
	}

	Colour Button::getHighlightColour() const {
		return m_highlight_colour;
	}

	void Button::setDefaultColour(Colour new_default_colour) {
		m_default_colour = new_default_colour;
	}

	Colour Button::getDefaultColour() const {
		return m_default_colour;
	}

	bool Button::mouseOverButton(const EventMouse* p_e) const{

		// Create Box for Button.
		int width = getViewString().size();
		int height = 1;

		if (getBorder()) {
			width = width + 4;
			height = height + 2;
		}
		Vector corner(getPosition().getX() - width / 2,
			getPosition().getY() - height / 2);
		Box b(corner, width, height);

		if (boxContainsPosition(b, p_e->getMousePosition())) {
			return true;
		}
		return false;
	}
}