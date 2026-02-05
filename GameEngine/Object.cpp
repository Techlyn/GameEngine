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

		// initialized variables
		static int id_count = 0;
		m_id = id_count;
		m_type = "Object";
		m_position = Vector(0, 0);

		m_altitude = 1;
		m_direction = Vector();
		m_speed = 0.0;
		m_solidness = Solidness::HARD;
		m_no_soft = false;

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

	void Object::setSpeed(float speed) {
		m_speed = speed;
	}

	float Object::getSpeed() const{
		return m_speed;
	}

	void Object::setDirection(Vector new_direction) {
		m_direction = new_direction;
	}

	Vector Object::getDirection() const {
		return m_direction;
	}

	void Object::setVelocity(Vector new_velocity) {
		// Set speed and direction based on velocity.
		m_speed = new_velocity.getMagnitude();
		m_direction = new_velocity.normalize();
	}

	Vector Object::getVelocity() const {
		// Set velocity based on speed and direction
		Vector v = m_direction;
		v.scale(m_speed);
		return v;
	}

	Vector Object::predictPosition() const {

		// Adds velocity to position
		Vector new_pos = m_position + getVelocity();
		// Returns new position
		return new_pos;
	}

	bool Object::isSolid() const {
		if (Solidness::HARD || Solidness::SOFT) {
			return true;
		}
		return false;
	}

	int Object::setSolidness(Solidness new_solid) {
		if (new_solid != Solidness::HARD && new_solid != Solidness::SOFT && new_solid != Solidness::SPECTRAL) {
			log.writeLog(CLASS_NAME, log.LOG_ERROR, "Error! Incorrect solidness set");
			return -1;
		}

		m_solidness = new_solid;
		return 0;
	}

	Solidness Object::getSolidness() const {
		return m_solidness;
	}

	void Object::setNoSoft(bool new_no_soft) {
		m_no_soft = new_no_soft;
	}

	bool Object::getNoSoft() const {
		return m_no_soft;
	}



}
