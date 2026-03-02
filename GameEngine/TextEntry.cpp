//
// TextEntry.cpp
//


#include "DisplayManager.h"
#include "TextEntry.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "Utility.h"

namespace df {

	TextEntry::TextEntry() {


		// TextEntry Inits.
		m_text = "";
		m_limit = 0;
		m_numbers_only = false;
		m_cursor = 0;
		m_cursor_char = '|';
		m_blink_rate = 16;

		m_hasFocus = false;
		m_cursorVisible = true;
		m_blinkCounter = 0;

		// ViewObject Inits.
		setDrawValue(false);


		registeredInterest(STEP_EVENT);
		registeredInterest(KEYBOARD_EVENT);
	}

	void TextEntry::setText(std::string new_text) {
		m_text = new_text;
	}

	std::string TextEntry::getText() const {
		return m_text;
	}

	int TextEntry::eventHandler(const Event* p_e) {

		// If step event, blink cursor
		if (p_e->getType() == STEP_EVENT) {

			// Only blink if this object has focus
			if (m_hasFocus) {
				m_blinkCounter++;
				if (m_blinkCounter >= getBlinkRate()) {
					m_blinkCounter = 0;
					m_cursorVisible = !m_cursorVisible;
				}
			}
			else {
				// When not focused, ensure cursor is not visible.
				m_cursorVisible = false;
			}

			return 1;
		}

		// If keyboard event, handle.
		if (p_e->getType() == KEYBOARD_EVENT) {
			const EventKeyboard* p_kbd_event = dynamic_cast<const EventKeyboard*> (p_e);
			if (!p_kbd_event) {
				return 0;
			}

			EventKeyboardAction action = p_kbd_event->getKeyboardAction();
			Keyboard::Key key = p_kbd_event->getKey();

			// Track shift keys.
			if (key == Keyboard::LSHIFT) {
				m_leftShiftPressed = (action == KEY_PRESSED);
			}
			else if (key == Keyboard::RSHIFT) {
				m_rightShiftPressed = (action == KEY_PRESSED);

			}

			// Only handle key pressed for input and only if focused.
			if (action != KEY_PRESSED || !m_hasFocus) {
				return 0;
			}


			// If return key pressed, then callback.
			if (p_kbd_event->getKey() == Keyboard::RETURN) {
				callback();
				return 1;
			}

			if (key == Keyboard::BACKSPACE) {
				if (m_cursor > 0) {
					m_text.erase(m_cursor - 1, 1);
					m_cursor--;
				}
			}

			// if no room, cannot add character.
			if (m_cursor >= m_limit) {
				return 1;
			}

			bool shiftPressed = m_leftShiftPressed || m_rightShiftPressed;
			char ch = keyToChar(key, shiftPressed);

			// Ignore non-printable keys.
			if (ch == '\0') {
				return 1;
			}

			// checks if entry is a number.
			if (m_numbers_only && !isdigit(static_cast<unsigned char>(ch))) {
				return 1;
			}

			m_text.insert(m_cursor, 1, ch);
			m_cursor++;

			return 1;

		}

		// Event not handled if here.
		return 0;

	}

	void TextEntry::setLimit(int new_limit) {
		m_limit = new_limit;
	}

	int TextEntry::getLimit() const {
		return m_limit;
	}

	void TextEntry::setCursor(int new_cursor) {
		m_cursor = new_cursor;
	}

	int TextEntry::getCursor() const {
		return m_cursor;
	}

	void TextEntry::setBlinkRate(int new_blink_rate) {
		m_blink_rate = new_blink_rate;
	}

	int TextEntry::getBlinkRate() const {
		return m_blink_rate;
	}

	void TextEntry::setFocus(bool focus) {
		m_hasFocus = focus;

		if (focus) {
			m_cursorVisible = true;
			m_blinkCounter = 0;
		}
	}

	bool TextEntry::hasFocus() const {
		return m_hasFocus;
	}

	void TextEntry::setCursorVisibility(bool visibility) {
		m_cursorVisible = visibility;
	}

	bool TextEntry::getCursorVisibility() const {
		return m_cursorVisible;
	}

	bool TextEntry::numbersOnly() const {
		return m_numbers_only;
	}

	void TextEntry::setNumbersOnly(bool new_numbers_only) {
		m_numbers_only = new_numbers_only;
	}

	void TextEntry::setCursorChar(char new_cursor_char) {
		m_cursor_char = new_cursor_char;
	}

	char TextEntry::getCursorChar() const {
		return m_cursor_char;
	}

	int TextEntry::draw() {

		// Get original view string
		std::string view_str = getViewString();

		// Add text.
		setViewString(view_str + m_text);

		// Draw
		ViewObject::draw();

		// Restore original view string.
		setViewString(view_str);

		// If focused and cursor should be visible, draw it.
		if (m_hasFocus && m_cursorVisible) {
			Vector pos = getPosition();

			// Calculate cursors' X offset: width of text before cursor.
			pos.setX(pos.getX() + m_cursor);
			

			

			// Draw tghe cursor character
			DM.drawCh(pos, getCursorChar(), this->getColour());
		}

		return 0;
	}

}
