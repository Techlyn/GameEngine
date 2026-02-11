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
		Box b = getWorldBox(p_o, where);

		// Iterate through all Objects.
		for (int i = 0; i < m_updates.getCount(); i++) {
			Object* p_temp_o = m_updates[i];
			
			Box b_temp = getWorldBox(p_temp_o);
			if (p_temp_o != p_o) {
				if(boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()){
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

					// Send to both Objects
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

		Box orig_box = getWorldBox(p_o);  // original bounding box
		p_o->setPosition(where);		  // move object
		Box new_box = getWorldBox(p_o);

		if (boxIntersectsBox(orig_box, m_boundary) && !boxIntersectsBox(new_box, m_boundary)) {
			EventOut ov;
			p_o->eventHandler(&ov);
		}

		// if here, no collision between two HARD objects so allow move.
		//p_o->setPosition(where);
		return 0;
	}

	void WorldManager::setBoundary(Box new_boundary) {
		m_boundary = new_boundary;
	}

	Box WorldManager::getBoundary() const {
		return m_boundary;
	}

	void WorldManager::setView(Box new_view) {
		m_view = new_view;
	}

	Box WorldManager::getView() const {
		return m_view;
	}

	void WorldManager::setViewPosition(Vector view_pos) {

		// Make sure horizontal not out of world boundary.
		float x = view_pos.getX() - m_view.getHorizontal() / 2;
		if (x + m_view.getHorizontal() > m_boundary.getHorizontal()) {
			x = m_boundary.getHorizontal() - m_view.getHorizontal();
		}
		if (x < 0) {
			x = 0;
		}

		// Make sure vertical not out of world boundary.
		float y = view_pos.getY() - m_view.getVertical() / 2;
		if (y + m_view.getVertical() > m_boundary.getVertical()) {
			y = m_boundary.getVertical() - m_view.getVertical();
		}
		if (y < 0) {
			y = 0;
		}

		Vector new_corner(x, y);
		m_view.setCorner(new_corner);
	}

	int WorldManager::setViewFollowing(Object* p_new_view_following) {

		// Set to NULL to turn 'off' following.
		if (p_new_view_following == NULL) {
			p_view_following = NULL;
			return 0;
		}
	
		for (int i = 0; i < m_updates.getCount(); i++) {
			if (m_updates[i] == p_new_view_following) {
				p_view_following = p_new_view_following;
				setViewPosition(p_view_following->getPosition());
				return 0;
			}

			// if get here, was not legit. Don't change current view.
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! object set for viewing not found no changes made");

		}
	}

}