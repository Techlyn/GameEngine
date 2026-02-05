#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "Colour.h"
#include "GameManager.h"
#include "Object.h"
#include "EventMouse.h"
#include "EventKeyboard.h"

int displayTest();
void displayManagerTest();
void gameManagerTest();

class TestObject : public df::Object {
public:
	TestObject();
	int draw(void) override;
	int eventHandler(const df::Event* p_e) override;
};

TestObject::TestObject() {
	setType("TestObject");
	setAltitude(df::MAX_ALTITUDE);

	df::Vector p(15, 20);
	setPosition(p);
}

int TestObject::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*>(p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position.
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}
		
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_kbd_e = dynamic_cast<const df::EventKeyboard*>(p_e);
		if (p_kbd_e->getKey() == df::Keyboard::SPACE) {
			if (p_kbd_e->getKeyboardAction() == df::KEY_PRESSED) {
				df::LogManager::getInstance().writeLog("%s: space key pressed", __func__);


			}
		}
		return 1;
	}
	return 0;
}
	

int TestObject::draw(void) {
	return df::DisplayManager::getInstance().drawCh(getPosition(), 'x', df::RED);
}

int main() {
	df::LogManager& log_manager = df::LogManager::getInstance();

	log_manager.setGlobalLevel(log_manager.LOG_TRACE);
	log_manager.setFlush();

	

	gameManagerTest();
	
}

void gameManagerTest() {
	df::GameManager& game_manager = df::GameManager::getInstance();
	game_manager.startUp();

	TestObject* p_TestObject = new TestObject;
	p_TestObject->draw();

	game_manager.run();
	game_manager.shutDown();
	
}

void displayManagerTest() {
	df::DisplayManager& DM = df::DisplayManager::getInstance();
	DM.startUp();
	DM.drawCh(df::Vector(1, 5), '*', df::GREEN);
	DM.drawCh(df::Vector(84, 5), '*', df::GREEN);

	DM.swapBuffer();
	Sleep(2000);
	DM.shutDown();

}

int displayTest() {
	int window_horizontal = 1024;
	int window_vertical = 768;





	sf::Font font;

	if (font.openFromFile("df-font.ttf") == false) {
		df::LogManager::getInstance().writeLog("Error finding font");
	}
	sf::Text text(font);
	text.setString("Hello, World");

	text.setCharacterSize(24);

	text.setFillColor(sf::Color::Red);

	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	text.setPosition({ 100, 50 });

	sf::Vector2u size = sf::Vector2u(window_horizontal, window_vertical);
	sf::RenderWindow* p_window = new sf::RenderWindow(sf::VideoMode(size), "Title - Dragonfly", sf::Style::Close);

	if (!p_window) {
		std::cout << "Error! Unable to allocate RenderWindow." << std::endl;
		return -1;
	}

	p_window->setMouseCursorVisible(false);

	p_window->setVerticalSyncEnabled(true);

	while (1) {
		p_window->clear();
		p_window->draw(text);
		p_window->display();

		while (const std::optional<sf::Event> p_event = p_window->pollEvent()) {
			if (p_event->is < sf::Event::Closed>()) {
				p_window->close();
				delete p_window;
				return 0;
			}
		}
	}
}