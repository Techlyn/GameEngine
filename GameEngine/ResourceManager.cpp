//
// ResourceManager.cpp
//

// system includes
#include <fstream>
#include <sstream>

// engine includes
#include "ResourceManager.h"
#include "Utility.h"


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

		std::ifstream file(filename);

		if (!file.is_open()) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Could not open file %s", filename);
			return -1;
		}

		std::string line;
		std::string currentSection;
		Sprite* new_sprite;
		Frame* new_frame;
		bool inFrame = false;

		while (getline(file, line))
		{
			std::string trimmedLine = Utility::trimString(line);

			if (trimmedLine.empty())
				continue;

			if (trimmedLine == "<HEADER>") {
				currentSection = "HEADER";
				continue;
			}
			else if (trimmedLine == "</HEADER>") {
				currentSection = "";
				continue;

			}
			else if (trimmedLine == "<BODY>") {
				currentSection = "BODY";
				continue;
			}
			else if (trimmedLine == "</BODY>") {
				currentSection = "";
				continue;
			}

			if (currentSection == "HEADER") {
				std::istringstream iss(trimmedLine);
				std::string key;
				std::string value;

				if (iss >> key) {

					std::getline(iss, value);
					value = Utility::trimString(value);

					if (key == "frames") {
						int frame = std::stoi(value);
						new_sprite = new Sprite(frame);
					}
					else if (key == "width") {
						int width = std::stoi(value);
						new_sprite->setWidth(width);
					}
					else if (key == "height") {
						int height = std::stoi(value);
						new_sprite->setHeight(height);
					}
					else if (key == "colour") {
						Colour colour = Utility::getColourFromString(value);
						new_sprite->setColour(colour);
					}
					else if (key == "slowdown") {
						int slowdown = std::stoi(value);
						new_sprite->setSlowdown(slowdown);
					}
				}
				else if (currentSection == "BODY") {
					// Checks if line is end, if end add frame to sprite, clear frame string.
					if (trimmedLine == "end") {
						if (new_frame->getString() == "") {
							new_sprite->addFrame(*new_frame);
							new_frame->setString("");
							// maybe delete new frame after adding?
						}
						inFrame = false;
					}
					// else add line to frame string.
					else {
						std::string frame_str = new_frame->getString();
						frame_str += trimmedLine + "\n";
						new_frame->setString(frame_str);
						inFrame = true;
					}
				}
			}
		} // end while

		// Handle case where file ends without "end" marker.
		if (inFrame && !new_frame->getString().empty()) {
			new_sprite->addFrame(*new_frame);
		}
		file.close();

		// add sprite to resource manager array.
		m_p_sprite[m_sprite_count] = new_sprite;
		m_p_sprite[m_sprite_count]->setLabel(label);
		m_sprite_count++;

		return 0;

	}

	int ResourceManager::unloadSprite(std::string label) {
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label){
				delete m_p_sprite[i];
				for (int j = i; j < m_sprite_count - 1; j++) {
					m_p_sprite[j] = m_p_sprite[j + 1];
				}
				m_p_sprite[m_sprite_count - 1] = NULL;
				m_sprite_count--;
			}
		}
	}


	Sprite* ResourceManager::getSprite(std::string label) const {
		if (m_sprite_count == 0) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! No sprites loaded");
			return NULL;
		}
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				return m_p_sprite[i];
			}
		}
		log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite with label %s not found", label);
		return NULL;
	}

} // end namespace df