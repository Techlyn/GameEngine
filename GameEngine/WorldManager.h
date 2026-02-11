//
// WorldManager.h
//

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

// Engine includes
#include "Manager.h"
#include "LogManager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()


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

		Box m_boundary;			// World boundary.
		Box m_view;				// Player view of game world.
		
		Object* p_view_following; // Object view is following.

		


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

		// Return list of Objects collided with at position 'where'.
		// Collisions only with solid objects.
		// Does not consider if p_o is solid or not.
		ObjectList getCollisions(const Object* p_o, Vector where);

		// Move Object.
		// If collision with solid, send collision events.
		// If no collsion with solid, move ok else don't move Object.
		// If Object Spectral, move ok.
		// Return 0 if move ok, else -1 if collision with solid.
		int moveObject(Object* p_o, Vector where);

		// Set game world boundary.
		void setBoundary(Box new_boundary);

		// Get game world boundary.
		Box getBoundary() const;

		// Set player view of game world.
		void setView(Box new_view);

		// Get player view of game world.
		Box getView() const;

		// Set view to center window on position view_pos.
		// View edge will not go boyond world boundary.
		void setViewPosition(Vector view_pos);

		// Set view to center window on Object.
		// Set to NULL to stop following.
		// if p_new_view_follow not legit, return -1 else return 0.
		int setViewFollowing(Object* p_new_view_following);

	};

}


#endif //__WORLD_MANAGER_H__