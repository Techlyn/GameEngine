//
// ResourceManager.cpp
//

// system includes
#include <iostream>
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
			m_p_sprite[i] = nullptr;
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
			m_p_sprite[i] = nullptr;
			m_sprite_count--;
		}
		Manager::shutDown();
		
	}

	int ResourceManager::loadSprite(std::string filename, std::string label) {
		if (m_sprite_count >= MAX_SPRITES) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite array is full");
			return -1;
		}
		if (getSprite(label) != nullptr) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite with label %s already exists", label);
			return -1;
		}

		std::ifstream file(filename);

		if (!file.is_open()) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Could not open file %s", filename);
			return -1;
		}

		// intialise Header attributes
		int frames{ 0 };
		int width{ 0 };
		int height{ 0 };
		Colour colour{ df::UNDEFINED_COLOUR };
		int slowdown{ 0 };

		std::string line;
		std::string trimmedLine;
		std::string currentSection;
		Frame* new_frame = new Frame();
		bool inFrame = false;

		while (line != "<HEADER>") {
			getline(file, line);
			trimmedLine = Utility::trimString(line);
		}

		while (trimmedLine != "</HEADER>")
		{
			getline(file, line);
			trimmedLine = Utility::trimString(line);

			std::istringstream iss(trimmedLine);
			std::string key;
			std::string value;

			if (iss >> key) {

				std::getline(iss, value);
				value = Utility::trimString(value);

				if (key == "frames") {
					frames = std::stoi(value);

				}
				else if (key == "width") {
					width = std::stoi(value);

				}
				else if (key == "height") {
					height = std::stoi(value);

				}
				else if (key == "colour") {
					colour = Utility::getColourFromString(value);

				}
				else if (key == "slowdown") {
					slowdown = std::stoi(value);

				}
			}
		}

		Sprite* new_sprite = new Sprite(frames);
		new_sprite->setWidth(width);
		new_sprite->setHeight(height);
		new_sprite->setColour(colour);
		new_sprite->setSlowdown(slowdown);

		while (trimmedLine != "<BODY>") {
			trimmedLine = Utility::trimString(line);
			getline(file, line);
		}

		while (trimmedLine != "</BODY>") {

			trimmedLine = Utility::trimString(line);

			if (trimmedLine == "</BODY>")
				continue;

			// Checks if line is end, if end add frame to sprite, clear frame string.
			if (trimmedLine == "end") {
				if (new_frame->getString() != "") {
					new_sprite->addFrame(*new_frame);
					new_frame->setString("");
					// maybe delete new frame after adding?
				}
				inFrame = false;
			}
			// else add line to frame string.
			else {
				std::string frame_str = new_frame->getString();
				frame_str += line + "\n";
				new_frame->setString(frame_str);
				inFrame = true;
			}
			getline(file, line);
		}

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
				m_p_sprite[m_sprite_count - 1] = nullptr;
				m_sprite_count--;

				return 0; // Found sprite and unloaded.
			}
		}
		return -1; // Sprite with label not found.
	}


	Sprite* ResourceManager::getSprite(std::string label) const {
		if (m_sprite_count == 0) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! No sprites loaded");
			return nullptr;
		}
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				return m_p_sprite[i];
			}
		}
		log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite with label %s not found", label);
		return nullptr;
	}


	void ResourceManager::printSprite() {
		for (int i = 0; i < m_p_sprite[0]->getFrameCount(); i++) {
			Frame test = m_p_sprite[0]->getFrame(i);
			log.writeLog("frame: %d\n", i + 1);
			std::cout << test.getString() << std::endl;
		}
	}

} // end namespace df