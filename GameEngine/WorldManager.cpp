//
// WorldManager.h
//

// engine includes
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Utility.h"
#include "EventCollision.h"
#include "EventOut.h"

namespace df {

	LogManager& WorldManager::log = LogManager::getInstance();
	

	WorldManager::WorldManager() {
		
		

		log.writeLog(CLASS_NAME, LogManager::LOG_INFO, "%s: created at %p", __func__, this);

		setType("WorldManager");
		

		//initialize world lists
		m_updates;
		m_deletions;

	

	}

	void WorldManager::operator=(WorldManager const&) {

	}

	WorldManager& WorldManager::getInstance() {
		static WorldManager instance;
		return instance;
	}

	int WorldManager::startUp() {
		if (isStarted()) return logAndReturn(LogManager::LOG_ERROR, "WorldManager already started");
		
		Manager::startUp();
		log.writeLog(LogManager::LOG_INFO, "%s: WorldManager has started", __func__);
		return 0;
		
	}

	void WorldManager::shutDown() {
		ObjectList ol = m_updates;
		for (int i = 0; i < ol.getCount(); i++) {
			delete ol[i];
		}

		m_updates.clear();
		m_deletions.clear();
	
		Manager::shutDown();
	}

	int WorldManager::insertObject(Object* p_o) {
		//Guard ifs
		if (!isStarted()) return logAndReturn(LogManager::LOG_ERROR, "WorldManager not started");
		if (p_o == nullptr) return logAndReturn(LogManager::LOG_ERROR, "Null object pointer");
		if (m_updates.isFull()) return logAndReturn(LogManager::LOG_ERROR, "Update list is full");

//success path, updates the list with the object
return m_updates.insert(p_o);
	}

	int WorldManager::removeObject(Object* p_o) {
		//Guard ifs
		if (!isStarted()) return logAndReturn(LogManager::LOG_ERROR, "WorldManager not started");
		if (p_o == nullptr) return logAndReturn(LogManager::LOG_ERROR, "Null object pointer");
		if (m_updates.isEmpty()) return logAndReturn(LogManager::LOG_ERROR, "Updates list is empty");

		// success path
		return m_updates.remove(p_o);;
	}

	int WorldManager::removeAllObjects() {
		//Guard ifs
		if (!isStarted()) return logAndReturn(LogManager::LOG_ERROR, "WorldManager not started.");
		if (m_deletions.isFull()) return logAndReturn(LogManager::LOG_ERROR, "Deletions list is full");

		for (int i = 0; i < m_updates.getCount(); i++) {
			markForDelete(m_updates[i]);

		}
		return 0;
	}


	ObjectList WorldManager::getAllObjects() const {
		return m_updates;
	}

	ObjectList WorldManager::objectsOfType(std::string type) {

		ObjectList list;
		for (int i = 0; i < m_updates.getCount(); i++) {
			if (m_updates[i]->getType() == type) {
				list.insert(m_updates[i]);
			}
		}
		return list;
	}


	void WorldManager::update() {

		for (int i = 0; i < m_updates.getCount(); i++) {
			Vector new_pos = m_updates[i]->predictPosition();
			if (new_pos != m_updates[i]->getPosition()) {
				moveObject(m_updates[i], new_pos);
			}
		}

		for (int i = 0; i < m_deletions.getCount(); i++) {
			delete m_deletions[i];
		}
		m_deletions.clear();

	}

	void WorldManager::draw() {

		

		for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {
			for (int i = 0; i < m_updates.getCount(); i++) {
				if (m_updates[i]->getAltitude() == alt) {
					m_updates[i]->draw();
				}
			}
		}
	}

	int WorldManager::markForDelete(Object* p_o) {
		//guards
		if (!isStarted()) return logAndReturn(LogManager::LOG_ERROR, "WorldManager not started");
		if (p_o == nullptr) return logAndReturn(LogManager::LOG_ERROR, "Null object pointer");
		if (m_deletions.isFull()) return logAndReturn(LogManager::LOG_ERROR, "Deletions list is full --- IF REACHED HERE check if update() is added");

		for (int i = 0; i < m_deletions.getCount(); i++) {
			if (m_deletions[i] == p_o) { // found
				return 1;
			}
		}
		//adds the object to the delete list.
		m_deletions.insert(p_o);
		return 0;
	}


	int WorldManager::logAndReturn(LogManager::LogLevel level, const char* message) {
		log.writeLog(CLASS_NAME, level, "%s: %s", __func__, message);
		return -1;
	}

	ObjectList WorldManager::getCollisions(const Object* p_o, Vector where) {
		// creates empty list
		ObjectList collision_list;

		// Iterate through all Objects.
		for (int i = 0; i < m_updates.getCount(); i++) {
			Object* p_temp_o = m_updates[i];
			if (p_temp_o != p_o) {
				if(Utility::positionsIntersect(p_temp_o->getPosition(), where) && p_temp_o->isSolid()){
					collision_list.insert(p_temp_o);
				}
			}
		}
		return collision_list;
	}

	int WorldManager::moveObject(Object* p_o, Vector where) {
		if (p_o->isSolid()) {
			ObjectList list = getCollisions(p_o, where);
			if (!list.isEmpty()) {
				bool do_move = true;
				for (int i = 0; i < list.getCount(); i++) {
					Object* p_temp_o = list[i];
					// Create Collision event.
					EventCollision c(p_o, p_temp_o, where);

					// Send both to Objects
					p_o->eventHandler(&c);
					p_temp_o->eventHandler(&c);

					// if either object is HARD, do not move.
					if (p_o->getSolidness() == Solidness::HARD || p_temp_o->getSolidness() == Solidness::HARD) {
						do_move = false;
					}
					// if Object does not want to move onto soft objects, don't move.
					if (p_o->getNoSoft() && p_temp_o->getSolidness() == Solidness::SOFT) {
						do_move = false;
					}
				}
				if (do_move == false)
					return -1;
			}
		}

		// if here, no collision between two HARD objects so allow move.
		p_o->setPosition(where);
		//temp boundary check, if object goes out of bounds, send out event to object.
		Vector p = p_o->getPosition();
		if (p.getX() < 0 || p.getX() >= df::DisplayManager::getInstance().getHorizontal() ||
			p.getY() < 0 || p.getY() >= df::DisplayManager::getInstance().getVertical()) {
			
			EventOut ov;
			p_o->eventHandler(&ov);
		}
		
		return 0;
	}

}