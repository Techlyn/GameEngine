//
// InputManager.cpp
//

#include "InputManager.h"
#include "DisplayManager.h"
#include "GameManager.h"

#include "EventKeyboard.h"
#include "EventMouse.h"

namespace df {

	InputManager::InputManager() {
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "%s: started at %p", __func__, this);
		setType("InputManager");
	}

	void InputManager::operator=(InputManager const&) {

	}

	InputManager& InputManager::getInstance() {
		static InputManager instance;
		return instance;
	}

	int InputManager::startUp() {
		if (!DisplayManager::getInstance().isStarted()) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! DisplayManager not started");
			return -1;
		}

		DisplayManager& display_manager = DisplayManager::getInstance();

		sf::RenderWindow* window = display_manager.getWindow();

		window->setKeyRepeatEnabled(false);

		Manager::startUp();
		return 0;
	}

	void InputManager::shutDown() {
		sf::RenderWindow* window = DisplayManager::getInstance().getWindow();
		window->setKeyRepeatEnabled(true);
		Manager::shutDown();
	}

	void InputManager::getInput() const {

		DisplayManager& display_manager = DisplayManager::getInstance();
		sf::RenderWindow* window = display_manager.getWindow();
		while (const std::optional<sf::Event> p_e = window->pollEvent()) {

			sf::Event e = p_e.value();

			if (p_e->is <sf::Event::Closed>()) {
				GameManager::getInstance().setGameOver();
				break;
			}

			if (p_e->is <sf::Event::KeyPressed>()) {
				sf::Event::KeyPressed* p_sfkb_event = reinterpret_cast<sf::Event::KeyPressed*> (&e);

				sf::Keyboard::Key key;
				key = p_sfkb_event->code;

				EventKeyboard* p_kb_event = new EventKeyboard;

				p_kb_event->setKeyboardAction(KEY_PRESSED);
				p_kb_event->setKey(getDfKey(key));
				onEvent(p_kb_event);
			}
			else if (p_e->is <sf::Event::KeyReleased>()) {
				sf::Event::KeyReleased* p_sfkb_event = reinterpret_cast<sf::Event::KeyReleased*> (&e);

				sf::Keyboard::Key key;
				key = p_sfkb_event->code;

				EventKeyboard* p_kb_event = new EventKeyboard;
				
				p_kb_event->setKeyboardAction(KEY_RELEASED);
				p_kb_event->setKey(getDfKey(key));
				onEvent(p_kb_event);

			}
			else if (p_e->is <sf::Event::MouseMoved>()) {
				sf::Event::MouseMoved* p_mse_event = reinterpret_cast<sf::Event::MouseMoved*> (&e);
				sf::Vector2i pixel_pos = p_mse_event->position;

				// Convert over to engine Vector 
				Vector conv(pixel_pos.x / DisplayManager::getInstance().charWidth(), pixel_pos.y / DisplayManager::getInstance().charHeight());

				// Init a EventMouse
				EventMouse mouse;
				
				mouse.setMousePosition(conv);
				mouse.setMouseAction(MOVED);
				onEvent(&mouse);
			}
			else if (p_e->is <sf::Event::MouseButtonPressed>()) {
				sf::Event::MouseButtonPressed* p_mse_event = 
					reinterpret_cast<sf::Event::MouseButtonPressed*> (&e);

				sf::Mouse::Button button;
				button = p_mse_event->button;
				
				EventMouse* mouse = new EventMouse;

				mouse->setMouseButton(getDfButton(button));
				mouse->setMouseAction(CLICKED);
				onEvent(mouse);

			}
			if (GameManager::getInstance().getGameOver()) {
				break;
			}
		}

	}


	Keyboard::Key InputManager::getDfKey(sf::Keyboard::Key key) const {
	
		switch (key) {
		case sf::Keyboard::Key::Space:
			return Keyboard::Key::SPACE;
		case sf::Keyboard::Key::Backspace:
			return Keyboard::Key::RETURN;
		case sf::Keyboard::Key::Escape:
			return Keyboard::Key::ESCAPE;
		case sf::Keyboard::Key::Tab:
			return Keyboard::Key::TAB;
		case sf::Keyboard::Key::Left:
			return Keyboard::Key::LEFTARROW;
		case sf::Keyboard::Key::Right:
			return Keyboard::Key::RIGHTARROW;
		case sf::Keyboard::Key::Up:
			return Keyboard::Key::UPARROW;
		case sf::Keyboard::Key::Down:
			return Keyboard::Key::DOWNARROW;
		case sf::Keyboard::Key::Pause:
			return Keyboard::Key::PAUSE;
		case sf::Keyboard::Key::Subtract:
			return Keyboard::Key::MINUS;
		case sf::Keyboard::Key::Add:
			return Keyboard::Key::PLUS;
		case sf::Keyboard::Key::Grave:
			return Keyboard::Key::GRAVE;
		case sf::Keyboard::Key::Period:
			return Keyboard::Key::PERIOD;
		case sf::Keyboard::Key::Comma:
			return Keyboard::Key::COMMA;
		case sf::Keyboard::Key::Slash:
			return Keyboard::Key::SLASH;
		case sf::Keyboard::Key::LControl:
			return Keyboard::Key::LCONTROL;
		case sf::Keyboard::Key::RControl:
			return Keyboard::Key::RCONTROL;
		case sf::Keyboard::Key::LShift:
			return Keyboard::Key::LSHIFT;
		case sf::Keyboard::Key::RShift:
			return Keyboard::Key::RSHIFT;
		case sf::Keyboard::Key::F1:
			return Keyboard::Key::F1;
		case sf::Keyboard::Key::F2:
			return Keyboard::Key::F2;
		case sf::Keyboard::Key::F3:
			return Keyboard::Key::F3;
		case sf::Keyboard::Key::F4:
			return Keyboard::Key::F4;
		case sf::Keyboard::Key::F5:
			return Keyboard::Key::F5;
		case sf::Keyboard::Key::F6:
			return Keyboard::Key::F6;
		case sf::Keyboard::Key::F7:
			return Keyboard::Key::F7;
		case sf::Keyboard::Key::F8:
			return Keyboard::Key::F8;
		case sf::Keyboard::Key::F9:
			return Keyboard::Key::F9;
		case sf::Keyboard::Key::F10:
			return Keyboard::Key::F10;
		case sf::Keyboard::Key::F11:
			return Keyboard::Key::F11;
		case sf::Keyboard::Key::F12:
			return Keyboard::Key::F12;
		case sf::Keyboard::Key::A:
			return Keyboard::Key::A;
		case sf::Keyboard::Key::B:
			return Keyboard::Key::B;
		case sf::Keyboard::Key::C:
			return Keyboard::Key::C;
		case sf::Keyboard::Key::D:
			return Keyboard::Key::D;
		case sf::Keyboard::Key::E:
			return Keyboard::Key::E;
		case sf::Keyboard::Key::F:
			return Keyboard::Key::F;
		case sf::Keyboard::Key::G:
			return Keyboard::Key::G;
		case sf::Keyboard::Key::H:
			return Keyboard::Key::H;
		case sf::Keyboard::Key::I:
			return Keyboard::Key::I;
		case sf::Keyboard::Key::J:
			return Keyboard::Key::J;
		case sf::Keyboard::Key::K:
			return Keyboard::Key::K;
		case sf::Keyboard::Key::L:
			return Keyboard::Key::L;
		case sf::Keyboard::Key::M:
			return Keyboard::Key::M;
		case sf::Keyboard::Key::N:
			return Keyboard::Key::N;
		case sf::Keyboard::Key::O:
			return Keyboard::Key::O;
		case sf::Keyboard::Key::P:
			return Keyboard::Key::P;
		case sf::Keyboard::Key::Q:
			return Keyboard::Key::Q;
		case sf::Keyboard::Key::R:
			return Keyboard::Key::R;
		case sf::Keyboard::Key::S:
			return Keyboard::Key::S;
		case sf::Keyboard::Key::T:
			return Keyboard::Key::T;
		case sf::Keyboard::Key::U:
			return Keyboard::Key::U;
		case sf::Keyboard::Key::V:
			return Keyboard::Key::V;
		case sf::Keyboard::Key::W:
			return Keyboard::Key::W;
		case sf::Keyboard::Key::X:
			return Keyboard::Key::X;
		case sf::Keyboard::Key::Y:
			return Keyboard::Key::Y;
		case sf::Keyboard::Key::Z:
			return Keyboard::Key::Z;
		case sf::Keyboard::Key::Num1:
			return Keyboard::Key::NUM1;
		case sf::Keyboard::Key::Num2:
			return Keyboard::Key::NUM2;
		case sf::Keyboard::Key::Num3:
			return Keyboard::Key::NUM3;
		case sf::Keyboard::Key::Num4:
			return Keyboard::Key::NUM4;
		case sf::Keyboard::Key::Num5:
			return Keyboard::Key::NUM5;
		case sf::Keyboard::Key::Num6:
			return Keyboard::Key::NUM6;
		case sf::Keyboard::Key::Num7:
			return Keyboard::Key::NUM7;
		case sf::Keyboard::Key::Num8:
			return Keyboard::Key::NUM8;
		case sf::Keyboard::Key::Num9:
			return Keyboard::Key::NUM9;
		case sf::Keyboard::Key::Num0:
			return Keyboard::Key::NUM0;
		default:
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Undefined key pressed.");
			return Keyboard::Key::UNDEFINED_KEY;

		}
	} // end InputManager::getDfKey()

	Mouse::Button InputManager::getDfButton(sf::Mouse::Button button) const {
		switch (button) {
		case sf::Mouse::Button::Left:
			return Mouse::Button::LEFT;
		case sf::Mouse::Button::Middle:
			return Mouse::Button::MIDDLE;
		case sf::Mouse::Button::Right:
			return Mouse::Button::RIGHT;
		default:
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Undefined mouse input pressed");
			return Mouse::Button::UNDEFINED_MOUSE_BUTTON;
		}
	}

	bool InputManager::isValid(std::string event_type) const {
		if (event_type == MSE_EVENT) {
			return true;
		}
		if (event_type == KEYBOARD_EVENT) {
			return true;
		}
		
		return false;
	}

} // namespace df