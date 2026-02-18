//
// ResourceManager.h
// 

#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// Engine includes
#include "Manager.h"
#include "LogManager.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"

#define RM df::ResourceManager::getInstance()

namespace df {

	const int MAX_SPRITES = 500;

	const int MAX_SOUNDS = 50;
	const int MAX_MUSICS = 50;

	class ResourceManager : public Manager {

	private:

		std::string CLASS_NAME = "ResourceManager";

		ResourceManager();							// Private (a singleton)	
		ResourceManager(ResourceManager const&);	// Don't allow copy.	
		void operator=(ResourceManager const&);		// Don't allow assignment.
		Sprite* m_p_sprite[MAX_SPRITES];            // Array of pointers to sprites.	
		int m_sprite_count;							// Number of sprites currently in array.	

		Sound *m_sound[MAX_SOUNDS];
		int m_sound_count;
		Music* m_music[MAX_MUSICS];
		int m_music_count;

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

		// Load Sound from file.
		// Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		// Remove Sound with indicated label.
		// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		// Find Sound with indicated label.
		// Return point to it if found, else NULL.
		Sound* getSound(std::string label);

		/// Associated file with Music.
		// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		// Remove label for Music with indicated label.
		// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		// Find Music with indicated label.
		// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);

	}; // end class ResourceManager

} // end namespace df

#endif // __RESOURCE_MANAGER_H__