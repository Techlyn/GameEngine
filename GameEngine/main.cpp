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
#include "EventOut.h"
#include "EventCollision.h"
#include "EventStep.h"
#include "EventView.h"
#include "ResourceManager.h"
#include "Circle.h"
#include "Sound.h"
#include "ViewObject.h"
#include "QuitButton.h"
#include "NameEntry.h"

int displayTest();
void displayManagerTest();

#define RETICLE_CHAR '+'
#define POINTS_STRING "Points"

class Reticle : public df::Object {
	int points;
	df::ViewObject* p_vo;
public:
	Reticle();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};

Reticle::Reticle() {
	setType("Reticle");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::SPECTRAL);
	df::Vector p(0, 0);
	registeredInterest(df::MSE_EVENT);
	registeredInterest(df::STEP_EVENT);
	setPosition(p);

	points = 0;

	p_vo = new df::ViewObject;
	p_vo->setViewString(POINTS_STRING);
	p_vo->setValue(points);
	p_vo->setLocation(df::TOP_RIGHT);
	p_vo->setColour(df::YELLOW);

	
}

int Reticle::draw(void) {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}



int Reticle::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}
	if (p_e->getType() == df::STEP_EVENT) {

		if (dynamic_cast<const df::EventStep*> (p_e)->getStepCount() % 30 == 0) {
			p_vo->setValue(points);
			points++;
		}
		return 1;
	}

	return 0;
}

class TestSaucer : public df::Object {	
private: 
	df::Sound m_sound;
	bool t;
public:
	TestSaucer();
	
	void moveToStart();
	void out();

	int eventHandler(const df::Event* p_e);
};

TestSaucer::TestSaucer() {
	setType("TestSaucer");
	setSprite("saucer");

	setSolidness(df::HARD);
	
	df::Vector p(15, 8);

	m_sound.loadSound("beep.wav");

	setPosition(p);

	bool t = false;
}



int TestSaucer::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}


	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event->getKey() == df::Keyboard::B) {
			LM.writeLog("key state is: %d", p_keyboard_event->getKeyboardAction());
			
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED && t == false) {
				m_sound.play();
				t = true;
			}
			if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
				t = false;
			}
		}
	}
}


void TestSaucer::moveToStart() {
	df::Vector temp_pos;

	temp_pos.setX(15);
	temp_pos.setY(84);

	WM.moveObject(this, temp_pos);
}

void TestSaucer::out() {
	if (getPosition().getX() >= 0) {
		return;
	}

	moveToStart();

}

int main() {
	df::LogManager& log_manager = df::LogManager::getInstance();

	log_manager.setGlobalLevel(log_manager.LOG_TRACE);
	log_manager.setFlush();

	df::GameManager& game_manager = df::GameManager::getInstance();
	
	RM.startUp();

	RM.loadSprite("saucer.txt", "saucer");
	game_manager.startUp();

	new NameEntry();

	new Reticle();
	new TestSaucer();
	TestSaucer* saucer = new TestSaucer();
	saucer->setPosition(df::Vector(35, 8));
	saucer->setVelocity(df::Vector( - 0.25, 0));
	new QuitButton();


	game_manager.run();

	game_manager.shutDown();
	RM.shutDown();
	
	

	
}


void displayManagerTest() {
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