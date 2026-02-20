//
// Music.cpp
//

#include "Music.h"
#include "LogManager.h"

namespace df {
	Music::Music() {
		m_label = "";
	}

	void Music::operator=(Music const&) {

	}

	int Music::loadMusic(std::string filename) {
		if (m_music.openFromFile(filename) == false) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! music file not found");
			return -1;
		}
		return 0;
	}

	void Music::setLabel(std::string new_label) {
		m_label = new_label;
	}

	std::string Music::getLabel() const {
		return m_label;
	}

	void Music::play(bool loop) {
		m_music.setLooping(loop);
		m_music.play();
	}

	void Music::stop() {
		m_music.stop();
	}

	void Music::pause() {
		m_music.pause();
	}

	sf::Music* Music::getMusic() {
		return &m_music;
	}
}