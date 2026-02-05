//
// WorldManager.h
//

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

// Engine includes
#include "Manager.h"
#include "LogManager.h"
#include "ObjectList.h"



namespace df {

	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager {

	private:

		static LogManager& log;
		const std::string CLASS_NAME = "WorldManager";
		int logAndReturn(LogManager::LogLevel level, const char* message);




		WorldManager();			// Private (a singleton)
		WorldManager(WorldManager const&);		// Don't allow a copy.
		void operator=(WorldManager const&);    // Don't allow assignment

		ObjectList m_updates;	// All Objects in world to update.
		ObjectList m_deletions;  // All Objects in world to delete.


	public:

		static WorldManager& getInstance();

		//Startup game world (initialize everything to empty).
		// Return 0.
		int startUp();

		// Shutdown game world (delete all game world Objects).
		void shutDown();

		// Insert Object into world. Return 0 if ok, else -1
		int insertObject(Object* p_o);

		// Remove Object from world. Return 0 if ok, else -1.
		int removeObject(Object* p_o);

		int removeAllObjects();

		// Return list of all Objects in world.
		ObjectList getAllObjects() const;

		// Return list of all Objects in world matching type.
		ObjectList objectsOfType(std::string type);

		// Update world.
		// Delete Objects marked for deletion.
		void update();

		void draw();

		// Indicate Object is to be deleted at end of current game loop.
		// Return 0 if ok, else -1
		int markForDelete(Object* p_o);

	};

}


#endif //__WORLD_MANAGER_H__