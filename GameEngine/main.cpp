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
#include "ResourceManager.h"

int displayTest();
void displayManagerTest();

#define RETICLE_CHAR '+'

class TestReticle : public df::Object {
public:
	TestReticle();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
};

TestReticle::TestReticle() {
	setType("TestReticle");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::SPECTRAL);
	df::Vector p(15, 8);

	setPosition(p);

	
}

int TestReticle::draw(void) {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}



int TestReticle::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			setPosition(p_mouse_event->getMousePosition());
			return 1;
		}
	}


	
	//if (p_e->getType() == df::OUT_EVENT) {
	//	const df::EventOut* p_out_e = dynamic_cast<const df::EventOut*>(p_e);
	//	if (p_out_e->getType() == df::OUT_EVENT) {
	//		df::LogManager::getInstance().writeLog("%s: received OUT_EVENT", __func__);
	//		out();
	//	}
	//}
	return 0;
}

//void TestObject::out(){
//	df::WorldManager::getInstance().markForDelete(this);
//}

class TestCircle : public df::Object {
public:
	TestCircle();
	int draw() override;
	int eventHandler(const df::Event* p_e);
};

TestCircle::TestCircle() {
	setType("TestBox");

	setSolidness(df::HARD);

	df::Vector p(15, 8);

	setPosition(p);
}

int TestCircle::draw(){
	sf::CircleShape circle;

	circle.setRadius(50.f);

	circle.setFillColor(sf::Color::Green);

	circle.setOutlineThickness(5.f);
	circle.setOutlineColor(sf::Color::White);

	circle.setPosition(sf::Vector2f(getPosition().getX(), getPosition().getY()));

	DM.drawCircle(circle);
	return 0;

}

int TestCircle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast<const df::EventMouse*> (p_e);

	}
	return 0;
}

int main() {
	df::LogManager& log_manager = df::LogManager::getInstance();

	log_manager.setGlobalLevel(log_manager.LOG_TRACE);
	log_manager.setFlush();

	df::GameManager& game_manager = df::GameManager::getInstance();
	
	RM.startUp();
	game_manager.startUp();

	new TestReticle();
	new TestBox();

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