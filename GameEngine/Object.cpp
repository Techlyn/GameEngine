//
// Object.cpp
//

#include "Object.h"
#include "WorldManager.h"



namespace df {

	
	LogManager& Object::log = LogManager::getInstance();

	

	Object::Object()
	{
		
		log.writeLog(CLASS_NAME, LogManager::LOG_DEBUG, "%s: created at %p", __func__, this);

		static int id_count = 0;
		m_id = id_count;
		m_type = "Object";
		m_position = Vector(0, 0);

		m_altitude = 1;

		WorldManager::getInstance().insertObject(this);

		
	}

	Object::~Object() {
		log.writeLog(CLASS_NAME, LogManager::LOG_DEBUG, "%s, Object id %p, destroyed", __func__, this);
	
		WorldManager::getInstance().removeObject(this);
	}

	void Object::setId(int new_id) {
		m_id = new_id;
	}

	int Object::getId() const {
		return m_id;
	}

	void Object::setType(std::string new_type) {
		m_type = new_type;
	}

	std::string Object::getType() const {
		return m_type;
	}

	int Object::draw() {
		return 1;
	}

	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	Vector Object::getPosition() const {
		return m_position;
	}

	int Object::setAltitude(int new_altitude) {
		if (new_altitude < 0 || new_altitude > MAX_ALTITUDE) {
			log.writeLog(CLASS_NAME, LogManager::LOG_ERROR, "Error! incorrect altitude set");
			return -1;
		}
		m_altitude = new_altitude;
		return 0; 

	}

	int Object::getAltitude() const {
		return m_altitude;
	}

	int Object::eventHandler(const Event* p_e) {
		return 0;
	}

}
