//
// InputManager.h
//

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

// System includes
#include <SFML/Graphics.hpp>

// Engine includes
#include "Manager.h"
#include "LogManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#define IM df::InputManager.getInstance();


namespace df {
	
	class InputManager : public Manager {

	private:

		static LogManager& log;
		const std::string CLASS_NAME = "InputManager";

		InputManager();						// Private (a singleton)
		InputManager(InputManager const&);  // Don't allow copy.
		void operator=(InputManager const&); // Don't allow assignment

	public:
		// Get the one and only instance of the InputManager.
		static InputManager& getInstance();

		// Get window ready to capture input.
		// Return 0 if ok. else return -1.
		int startUp();

		// Revert back to normal window mode.
		void shutDown();

		// Get input from the keyboard and mouse.
		// Passevent along to all Objects.
		void getInput() const;

		Keyboard::Key getDfKey(sf::Keyboard::Key key) const;

		Mouse::Button getDfButton(sf::Mouse::Button button) const;


	};


}

#endif // __INPUT_MANAGER_H__