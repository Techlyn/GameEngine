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
#include "Circle.h"

int displayTest();
void displayManagerTest();

#define RETICLE_CHAR '+'

class TestReticle : public df::Object {
public:
	TestReticle();
	int draw() override;
	int eventHandler(const df::Event* p_e) override;
	void collision(const df::EventCollision* p_c);
};

TestReticle::TestReticle() {
	setType("TestReticle");
	setAltitude(df::MAX_ALTITUDE);
	setSolidness(df::HARD);
	df::Vector p(0, 0);

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

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_col_event = dynamic_cast<const df::EventCollision*> (p_e);
		collision(p_col_event);
		return 1;
	}
	return 0;
	
	//if (p_e->getType() == df::OUT_EVENT) {
	//	const df::EventOut* p_out_e = dynamic_cast<const df::EventOut*>(p_e);
	//	if (p_out_e->getType() == df::OUT_EVENT) {
	//		df::LogManager::getInstance().writeLog("%s: received OUT_EVENT", __func__);
	//		out();
	//	}
	//}
	return 0;
}
void TestReticle::collision(const df::EventCollision* p_c) {
	if ((p_c->getObject1()->getType() == "TestReticle") && (p_c->getObject2()->getType() == "TestReticle")) {
		return;
	}
	if ((p_c->getObject1()->getType() == "TestSaucer") || (p_c->getObject2()->getType() == "TestSaucer")) {
		LM.writeLog("Reticle and saucer interacted with each other!");
	}
}

//void TestObject::out(){
//	df::WorldManager::getInstance().markForDelete(this);
//}

class TestSaucer : public df::Object {	
public:
	TestSaucer();
	
	void collision(const df::EventCollision* p_c);
	void moveToStart();
	void out();

	int eventHandler(const df::Event* p_e);
};

TestSaucer::TestSaucer() {
	setType("TestSaucer");
	setSprite("saucer");

	setSolidness(df::HARD);
	
	

	df::Vector p(15, 8);

	setPosition(p);
}



int TestSaucer::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		collision(p_collision_event);
		return 1;
	}
}

void TestSaucer::collision(const df::EventCollision* p_c) {
	if ((p_c->getObject1()->getType() == "TestSaucer") && (p_c->getObject2()->getType() == "TestSaucer")) {
		return;
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

	new TestReticle();
	new TestSaucer();
	TestSaucer* saucer = new TestSaucer();
	saucer->setPosition(df::Vector(35, 8));
	saucer->setVelocity(df::Vector( - 0.25, 0));

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