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

	

	ResourceManager::ResourceManager() {
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "%s created at %p", __func__, this);
		setType("ResourceManager");

		for (int i = 0; i < MAX_SPRITES; i++) {
			m_p_sprite[i] = nullptr;
		}

		m_sound_count = 0;
		m_music_count = 0;

		for (int i = 0; i < MAX_SOUNDS; i++) {
			m_sound[i] = nullptr;
		}
		
	}

	void ResourceManager::operator=(ResourceManager const&) {

	}

	ResourceManager& ResourceManager::getInstance() {
		static ResourceManager instance;
		return instance;
	}

	int ResourceManager::startUp() {
		if (Manager::isStarted()) {
			LM.writeLog(CLASS_NAME, LM.LOG_INFO, "Warning! ResourceManager already started");
			return -1;
		}
		Manager::startUp();
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "Resource Manager Start");
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
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Sprite array is full");
			return -1;
		}
		if (getSprite(label) != nullptr) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Sprite with label %s already exists", label);
			return -1;
		}

		std::ifstream file(filename);

		if (!file.is_open()) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Could not open file %s", filename);
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
			trimmedLine = df::trimString(line);
		}

		while (trimmedLine != "</HEADER>")
		{
			getline(file, line);
			trimmedLine = df::trimString(line);

			std::istringstream iss(trimmedLine);
			std::string key;
			std::string value;

			if (iss >> key) {

				std::getline(iss, value);
				value = df::trimString(value);

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
					colour = df::getColourFromString(value);

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
			trimmedLine = df::trimString(line);
			getline(file, line);
		}

		while (trimmedLine != "</BODY>") {

			trimmedLine = df::trimString(line);

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
				frame_str.append(line);
				new_frame->setString(frame_str);
				new_frame->setHeight(height);
				new_frame->setWidth(width);
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
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! No sprites loaded");
			return nullptr;
		}
		for (int i = 0; i < m_sprite_count; i++) {
			if (m_p_sprite[i]->getLabel() == label) {
				return m_p_sprite[i];
			}
		}
		LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Sprite with label %s not found", label);
		return nullptr;
	}


	void ResourceManager::printSprite() {
		for (int i = 0; i < m_p_sprite[0]->getFrameCount(); i++) {
			Frame test = m_p_sprite[0]->getFrame(i);
			LM.writeLog("frame: %d\n", i + 1);
			std::cout << test.getString() << std::endl;
		}
	}

	int ResourceManager::loadSound(std::string filename, std::string label) {
		if (m_sound_count == MAX_SOUNDS) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Sound array full.");
			return -1;
		}
		if (m_sound[m_sound_count]->loadSound(filename) == -1) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Unable to add file to resource manager.");
			return -1;
		}

		m_sound[m_sound_count]->setLabel(label);
		++m_sound_count;
		return 0;
	}

	int ResourceManager::unloadSound(std::string label) {
		for (int i = 0; i < m_sound_count - 1; i++) {
			if (label == m_sound[i]->getLabel()) {
				for (int j = 0; j < m_sound_count - 2; j++) {
					m_sound[j]->~Sound(); 
					m_sound[j] = m_sound[j + 1];
				}
				--m_sound_count;
				return 0;
			}
		}
		return -1;
	}

	Sound* ResourceManager::getSound(std::string label) {
		for (int i = 0; i < m_sound_count - 1; i++) {
			if (label == m_sound[i]->getLabel()) {
				return m_sound[i];
			}
		}
		return NULL;
	}

	int ResourceManager::loadMusic(std::string filename, std::string label) {
		if (m_music_count == MAX_MUSICS) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Music array full");
			return -1;
		}
		if (m_music[m_music_count]->loadMusic(filename) == -1) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Unable to add file to Resource manager");
			return -1;
		}

		m_music[m_music_count]->setLabel(label);
		++m_music_count;
		return 0;
	}

	int ResourceManager::unloadMusic(std::string label) {
		for (int i = 0; i < m_music_count - 1; i++) {
			if (label == m_music[i]->getLabel()) {
				for (int j = 0; j < m_music_count - 2; j++) {
					m_music[j] = m_music[j + 1];
				}
				--m_music_count;
				return 0;
			}
		}
		return -1;
	}

	Music* ResourceManager::getMusic(std::string label) {
		for (int i = 0; i < m_music_count - 1; i++) {
			if (label == m_music[i]->getLabel()) {
				return m_music[i];
			}
		}
		return NULL;
	}

	

} // end namespace df