//
// Sprite.cpp
//

#include "Sprite.h"

namespace df {

	LogManager& Sprite::log = LogManager::getInstance();

	Sprite::Sprite() {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_frame = new Frame[0];
		m_max_frame_count = 0;
		m_colour = COLOUR_DEFAULT;
	}

	Sprite::Sprite(int max_frames) {
		m_frame_count = 0;
		m_width = 0;
		m_height = 0;
		m_frame = new Frame[max_frames];
		m_max_frame_count = max_frames;
		m_colour = COLOUR_DEFAULT;
	}

	Sprite::~Sprite() {
		if (m_frame != NULL) {
			delete[] m_frame;
		}
	}

	void Sprite::setWidth(int new_width) {
		m_width = new_width;
	}

	int Sprite::getWidth() const {
		return m_width;
	}

	void Sprite::setHeight(int new_height) {
		m_height = new_height;
	}

	int Sprite::getHeight() const {
		return m_height;
	}

	void Sprite::setColour(Colour new_colour) {
		m_colour = new_colour;
	}

	Colour Sprite::getColour() const {
		return m_colour;
	}

	int Sprite::getFrameCount() const {
		return m_max_frame_count;
	}

	int Sprite::addFrame(Frame new_frame) {
		if (m_frame_count == m_max_frame_count) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite frame array full");
			return -1;
		}

		m_frame[m_frame_count] = new_frame;
		m_frame_count++;
		return 0;
	}

	Frame Sprite::getFrame(int frame_number) const {
		if ((frame_number < 0 || frame_number >= m_frame_count)) {
			Frame empty_frame;
			return empty_frame;
		}
		return m_frame[frame_number];
	}

	void Sprite::setLabel(std::string new_label) {
		m_label = new_label;
	}

	std::string Sprite::getLabel() const {
		return m_label;
	}

	void Sprite::setSlowdown(int new_sprite_slowdown) {
		m_slowdown = new_sprite_slowdown;
	}

	int Sprite::getSlowdown() const {
		return m_slowdown;
	}

	int Sprite::draw(int frame_number, Vector position) const {
		if (frame_number < 0 || frame_number >= m_frame_count) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Sprite frame number out of range");
			return -1;
		}

		for (int y = 0; y < m_height - 1; y++) {
			for (int x = 0; x < m_width - 1; x++) {
			
			}
		}
	}

	void Sprite::setTransparency(char new_transparency) {
		m_transparency = new_transparency;
	}

	char Sprite::getTransparency() const {
		return m_transparency;
	}
}