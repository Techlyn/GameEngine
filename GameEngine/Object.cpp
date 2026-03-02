//
// Object.cpp
//

#include "Object.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "SceneGraph.h"




namespace df {

	SceneGraph& scene_graph = WM.getSceneGraph();

	Object::Object()
	{
		
		LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "%s: created at %p", __func__, this);

		// initialized variables
		static int id_count = 0;
		m_id = id_count;
		m_type = "Object";
		m_position = Vector(0, 0);

		m_altitude = 1;
		m_direction = Vector(0,0);
		m_speed = 0.0;
		m_solidness = Solidness::HARD;
		m_no_soft = false;

		event_count = 0;

		WorldManager::getInstance().insertObject(this);

		
	}

	Object::~Object() {
		LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "%s, Object id %p, destroyed", __func__, this);
	
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
		Vector pos = getPosition();
		return m_animation.draw(pos);
	}

	void Object::setPosition(Vector new_pos) {
		m_position = new_pos;
	}

	Vector Object::getPosition() const {
		return m_position;
	}

	int Object::setAltitude(int new_altitude) {
		if (new_altitude < 0 || new_altitude > MAX_ALTITUDE) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! incorrect altitude set");
			return -1;
		}
		
		scene_graph.updateAltitude(this, new_altitude);
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
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Incorrect solidness set");
			return -1;
		}

		scene_graph.updateSolidness(this, new_solid);
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

	// Set Sprite for this Object to animate.
	int Object::setSprite(std::string sprite_label) {
		Sprite* p_sprite = RM.getSprite(sprite_label);
		if (p_sprite == nullptr) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error sprite pointer NULL");
			return -1;
		}

		m_animation.setSprite(p_sprite);
		setBox(m_animation.getBox());
		return 0;
	}

	void Object::setAnimation(Animation new_animation) {
		m_animation = new_animation;
	}

	Animation Object::getAnimation() const {
		return m_animation;
	}

	void Object::setBox(Box new_box) {
		m_box = new_box;
	}

	Box Object::getBox() const {
		return m_box;
	}

	int Object::registeredInterest(std::string event_type) {
		if (event_count == MAX_OBJ_EVENTS) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! object event full");
			return -1;
		}

		if (event_type == STEP_EVENT) {
			GM.registerInterest(this, event_type);
		}
		else if (event_type == KEYBOARD_EVENT) {
			IM.registerInterest(this, event_type);
		}
		else if (event_type == MSE_EVENT) {
			IM.registerInterest(this, event_type);
		}
		else if (event_type == COLLISION_EVENT) {
			WM.registerInterest(this, event_type);
		}
		else if (event_type == OUT_EVENT) {
			WM.registerInterest(this, event_type);
		}
		else
			WM.registerInterest(this, event_type);
	

		return 0;
	}

	int Object::unregisterInterest(std::string event_type) {
		
		if (event_type == STEP_EVENT) {
			GM.unregisterInterest(this, event_type);
		}
		else if (event_type == KEYBOARD_EVENT || event_type == MSE_EVENT) {
			IM.unregisterInterest(this, event_type);
		}
		else if (event_type == COLLISION_EVENT || event_type == OUT_EVENT) {
			WM.unregisterInterest(this, event_type);
		}
		else
			WM.unregisterInterest(this, event_type);

		return 0;
	}

	int Object::setActive(bool active) {

		// Update scene graph.
		scene_graph.updateActive(this, active);
		
		// Set active value
		is_active = active;
	}

	bool Object::isActive() const {
		return is_active;
	}

}
