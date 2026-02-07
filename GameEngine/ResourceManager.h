//
// ResourceManager.h
// 

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "Manager.h"
#include "LogManager.h"
#include "Sprite.h"

#define RM df::ResourceManager::getInstance()

namespace df {

	const int MAX_SPRITES = 500;

	class ResourceManager : public Manager {

	private:

		std::string CLASS_NAME = "ResourceManager";

		ResourceManager();							// Private (a singleton)	
		ResourceManager(ResourceManager const&);	// Don't allow copy.	
		void operator=(ResourceManager const&);		// Don't allow assignment.
		Sprite* m_p_sprite[MAX_SPRITES];            // Array of pointers to sprites.	
		int m_sprite_count;							// Number of sprites currently in array.	

	public:

		// Get the one and only instance of ResourceManager.
		static ResourceManager& getInstance();

		// Get ResourceManager ready to manage resources.
		int startUp();

		// Shut down ResourceManager, freeing up any allocated Sprites.
		void shutDown();

		// Load Sprite from file.
		// Assign indicated label to sprite.
		// Return 0 if ok, else -1.
		int loadSprite(std::string filename, std::string label);

		// Unload Sprite with indicated label
		// Return 0 if ok, else -1.
		int unloadSprite(std::string label);

		// Find Sprite with indicated label.
		// Return pointer to it if found, else NULL.
		Sprite* getSprite(std::string label) const;

		void printSprite();

	}; // end class ResourceManager

} // end namespace df

#endif // __RESOURCE_MANAGER_H__