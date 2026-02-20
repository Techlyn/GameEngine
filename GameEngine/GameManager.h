//
// GameManager.h
//

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

// Engine includes
#include "Manager.h"
#include "LogManager.h"

#define GM df::GameManager::getInstance()

const int FRAME_TIME_DEFAULT = 33;

namespace df {

	class GameManager : public Manager {

	private:

		static LogManager& log;
		const std::string CLASS_NAME = "GameManager";

		GameManager();						// private since a singelton.
		GameManager(GameManager const&);    // Don't allow copy.
		void operator=(GameManager const&); // Don't allow assignment.
		bool game_over;			// True, then game loop should stop.
		int frame_time;			// Target time per game loop, in milliseconds.

	public:
		// Get the singleton instance of the GameManager.
		static GameManager& getInstance();

		// Startup all GameManager services
		int startUp();

		// Shut down GameManager services
		void shutDown();

		// Run game loop.
		void run();

		// Set game over status to indicate value.
		// if true (default), will stop game loop.
		void setGameOver(bool new_game_over = true);

		// Get game over status.
		bool getGameOver() const;

		// Return frame time.
		// Frame time is target time for game loop, in milliseconds.
		int getFrameTime() const;

		// Accepts GameManager Events
		bool isValid(std::string event_type) const;
	}; // end class GameManager
} // end namespace df
#endif // end of __GAME_MANAGER_H__