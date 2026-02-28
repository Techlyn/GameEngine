//
// Button.h
//

#ifndef __BUTTON_H__
#define __BUTTON_H__

// Engine includes
#include "ViewObject.h"
#include "EventMouse.h"

namespace df {

	class Button : public ViewObject {

	private:
		Colour m_highlight_colour;	// Colour when highlighted.
		Colour m_default_colour;	// Colour when not highlighted.

	public:
		Button();

		// Handle "mouse" events.
		// Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e) override;

		// Set highlight (when mouse over) colour for Button.
		void setHighlightColour(Colour new_highlight_colour);

		// Get highlight (when mouse over) colour for Button.
		Colour getHighlightColour() const;

		// Set Colour of Button
		void setDefaultColour(Colour new_default_colour);

		// Get colour of Button
		Colour getDefaultColour() const;

		// Return true if mouse over Button, else false.
		bool mouseOverButton(const EventMouse* p_e) const;

		// Called when Button is clicked.
		// Must be defined by derived class.
		virtual void callback() = 0;

	};
}

#endif // __BUTTON_H__