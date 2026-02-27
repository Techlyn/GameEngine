//
// GameManager.cpp
//

#include <Windows.h>


#include "GameManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "LogManager.h"
#include "EventStep.h"
#include "Clock.h"





namespace df {


	LogManager& GameManager::log = LogManager::getInstance();
	

	GameManager::GameManager() {
		log.writeLog(CLASS_NAME, LogManager::LOG_INFO, "%s created at %p", __func__, this);

		setType("GameManager");
		game_over = false;
		frame_time = FRAME_TIME_DEFAULT;

	}

	void GameManager::operator=(GameManager const&) {


	}

	GameManager& GameManager::getInstance() {
		static GameManager instance;
		return instance;
	}

	int GameManager::startUp() {
		log.startUp();
		WorldManager& world_manager = WorldManager::getInstance();
		DisplayManager& display_manager = DisplayManager::getInstance();
		world_manager.startUp();
		display_manager.startUp();

		Box* boundary = new Box();
		boundary->setHorizontal(DM.getHorizontal());
		boundary->setVertical(DM.getVertical());
		WM.setBoundary(*boundary);
		WM.setView(WM.getBoundary());
	
	
		Manager::startUp();

		timeBeginPeriod(1);

		log.writeLog(LogManager::LOG_INFO, "Game Manager Start");
		return 0;

	}

	void GameManager::shutDown() {
		
		WorldManager& world_manager = WorldManager::getInstance();
		DisplayManager& display_manager = DisplayManager::getInstance();
		display_manager.shutDown();
		world_manager.shutDown();
		log.shutDown();
		
		Manager::shutDown();


		setGameOver();

		timeEndPeriod(1);
		
		
		

	}

	void GameManager::run() {
		WorldManager& world_manager = WorldManager::getInstance();
		DisplayManager& display_manager = DisplayManager::getInstance();
		InputManager& input_manager = InputManager::getInstance();
		Clock clock;
		
		int long adjust_time{ 0 };

		
		
		

		while (!game_over) {
		//start time
			clock.delta();

			EventStep es;
			onEvent(&es);
			IM.getInput();
			WM.update();
			WM.draw();
			DM.swapBuffer();

			long int loop_time = clock.split();
			long int intended_sleep_time = frame_time - loop_time - adjust_time;
			clock.delta();
			// whatever frame-time is left sleep for that time till next frame.
			if(intended_sleep_time > 0)
				Sleep(intended_sleep_time);

			int long actual_sleep_time = clock.split();
			adjust_time = actual_sleep_time - intended_sleep_time;
			if (adjust_time < 0) {
				adjust_time = 0;
			}
		}
	}

	void GameManager::setGameOver(bool new_game_over) {
		log.writeLog(LogManager::LOG_DEBUG, "Game Over set to %d", new_game_over);
		game_over = new_game_over;
	}

	bool GameManager::getGameOver() const {
		return game_over;
	}

	int GameManager::getFrameTime() const {
		return frame_time;
	}

	bool GameManager::isValid(std::string event_type) const {
		if (event_type == STEP_EVENT) {
			return true;
		}
		
		return false;
	}

	


}