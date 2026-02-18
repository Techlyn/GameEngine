//
// Sound.cpp
//

// Engine includes
#include "Sound.h"
#include "LogManager.h"

namespace df {

	Sound::Sound() {
		m_p_sound = NULL;
		m_sound_buffer;
		std::string m_label = "";
	}
	Sound::~Sound() {
		delete m_p_sound;
	}

	int Sound::loadSound(std::string filename) {
		if (m_sound_buffer.loadFromFile(filename) == false) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Sound file not found");
			return -1;
		}
		
		m_p_sound = new sf::Sound(m_sound_buffer);
		
		return 0;
	}

	void Sound::setLabel(std::string new_label) {
		m_label = new_label;
	}

	std::string Sound::getLabel() const {
		return m_label;
	}

	void Sound::play(bool loop) {
		
		m_p_sound->setLooping(loop);
		m_p_sound->play();
		
	}

	void Sound::stop() {
		m_p_sound->stop();
	}

	void Sound::pause() {
		m_p_sound->pause();
	}

	sf::Sound Sound::getSound() const {
		return *m_p_sound;
	}

	
}