//
// TextEntry.h
//

#ifndef __TEXT_ENTRY_H__
#define __TEXT_ENTRY_H__

#include "EventMouse.h"
#include "ViewObject.h"

namespace df {

	class TextEntry : public ViewObject {
	private:
		std::string m_text;			// Text entered.
		int m_limit;				// Character limit in text.
		bool m_numbers_only;		// True if only numbers.
		int m_cursor;				// Cursor location.
		char m_cursor_char;			// Cursor chacater.
		int m_blink_rate;			// Cursor blink rate.

		bool m_leftShiftPressed;
		bool m_rightShiftPressed;

		bool m_hasFocus;
		bool m_cursorVisible;
		int m_blinkCounter;
		

	public:
		TextEntry();

		// Set text entered.
		void setText(std::string new_text);

		// Get text entered.
		std::string getText() const;

		// Handle "keyboard" events.
		// Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e) override;

		// Called when TextEntry enter hit.
		// Must be defined by derived class.
		virtual void callback() = 0;

		// Set limit number of characters allowed.
		void setLimit(int new_limit);

		// Get limit number of character allowed.
		int getLimit() const;

		// Set cursor to location.
		void setCursor(int new_cursor);

		// Get cusor location.
		int getCursor() const; 

		// Set blink rate for cursor (in ticks).
		void setBlinkRate(int new_blink_rate);

		// Get blink rate for cursor (in ticks).
		int getBlinkRate() const;

		// Focus management, used when object is clicked or activated.
		void setFocus(bool focus = false);

		// Get focus currently set, returns true if focus set.
		bool hasFocus() const;

		// set visibility of the cursor (default set to true)
		void setCursorVisibility(bool visibility = true);

		// get cursor visibility.
		bool getCursorVisibility() const;

		// Return true if only numbers can be entered.
		bool numbersOnly() const;

		// Set to allow only numbers to be entered.
		void setNumbersOnly(bool new_numbers_only = true);

		// Set cursor character.
		void setCursorChar(char new_cursor_char);

		// Get cursor character.
		char getCursorChar() const;

		// Draw viewstring + text entered.
		virtual int draw() override;

	}; // end of class TextEntry

} // end of namespace

#endif // __TEXT_ENTRY_H__