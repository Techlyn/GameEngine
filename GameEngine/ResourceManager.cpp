//
// ResourceManager.cpp
//

#include "ResourceManager.h"

namespace df { 

	LogManager& ResourceManager::log = LogManager::getInstance();

	ResourceManager::ResourceManager() {
		log.writeLog(CLASS_NAME, log.LOG_INFO, "%s created at %p", __func__, this);
		setType("ResourceManager");

		for (int i = 0; i < MAX_SPRITES; i++) {
			m_p_sprite[i] = NULL;
		}
		m_sprite_count = 0;
	}

	void ResourceManager::operator=(ResourceManager const&) {

	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager instance;
		return instance;
	}

	int ResourceManager::startUp() {

		Manager::startUp();
		log.writeLog(CLASS_NAME, log.LOG_INFO, "Resource Manager Start");
		return 0;
	}

	void ResourceManager::shutDown() {
		for (int i = 0; i < m_sprite_count; i++) {
			delete m_p_sprite[i];
			m_p_sprite[i] = NULL;
			m_sprite_count--;
		}
		Manager::shutDown();
		
	}

	int ResourceManager::loadSprite(std::string filename, std::string label) {
		if (m_sprite_count >= MAX_SPRITES) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite array is full");
			return -1;
		}
		if (getSprite(label) != NULL) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite with label %s already exists", label);
			return -1;
		}

		const char* cstr = filename.c_str();

		FILE* p_f;
		if (!fopen_s(&p_f, cstr, "r")) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Unable to open file %s", filename.c_str());
			return -1;
		}
		int fcount, width, height, slowdown;
		std::string colour_key;
		
		//Read Sprite Header.
		

		
		
	}

} // end namespace df