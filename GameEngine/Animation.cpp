//
// Animation.cpp
//

#include "Animation.h"
#include "DisplayManager.h"

namespace df {

	LogManager& Animation::log = LogManager::getInstance();

	Animation::Animation() {
		m_index = 0;
		m_slowdown_count = 0;
		
	}

	void Animation::setSprite(Sprite* p_new_sprite) {
		m_p_sprite = p_new_sprite;
	}

	Sprite* Animation::getSprite() const {
		return m_p_sprite;
	}

	void Animation::setName(std::string new_name) {
		m_name = new_name;
	}

	std::string Animation::getName() const {
		return m_name;
	}

	void Animation::setIndex(int new_index) {
		m_index = new_index;
	}

	int Animation::getIndex() const {
		return m_index;
	}

	void Animation::setSlowdownCount(int new_slowdown_count) {
		m_slowdown_count = new_slowdown_count;
	}

	int Animation::getSlowdownCount() const {
		return m_slowdown_count;
	}

	int Animation::draw(Vector position) {
		if (m_p_sprite == nullptr) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! no sprite loaded, sprite nullptr");
			return -1;
		}

		// Ask Sprite to draw current frame.
		int index = getIndex();
		m_p_sprite->draw(index, position);

		// If slowdown count is -1 then aniamtion is frozen.
		if (getSlowdownCount() == -1)
			return 0;

		// increment counter.
		int count = getSlowdownCount();
		count++;

		if(count >= m_p_sprite->getSlowdown()){
			count = 0;
			index++;

			if (index >= m_p_sprite->getFrameCount()) {
				index = 0;
			}

			setIndex(index);
		}
		setSlowdownCount(count);
		return 0;
		
	}

	void Animation::setTransform(Transform new_transform) {
		m_transform = new_transform;
	}

	Transform Animation::getTransform() const {
		return m_transform;
	}
	

	Box Animation::getBox() const {

		//If no sprite, return Box centered at (0,0).
		if (!m_p_sprite) {
			Box box(Vector(-0.5, -0.5), 0.99, 0.99);
			return box;
		}

		// Create Box around centered Sprite.
		Vector corner(-1 * m_p_sprite->getWidth() / 2.0,
			-1 * m_p_sprite->getHeight() / 2.0);

		Box box(corner, m_p_sprite->getWidth(),
			m_p_sprite->getHeight());

		return box;
	}

}