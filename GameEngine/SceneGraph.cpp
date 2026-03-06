//
// SceneGraph.cpp
//

// Engine includes
#include "LogManager.h"
#include "SceneGraph.h"
#include "Utility.h"

namespace df {
	SceneGraph::SceneGraph() {
		active_objects;
		inactive_objects;

		m_solid_objects;
		for (int i = 0; i < MAX_ALTITUDE + 1; i++) {
			m_visible_objects[i];

		}

	}
	SceneGraph::~SceneGraph() {

		active_objects.clear();
		inactive_objects.clear();
		m_solid_objects.clear();
		for (int i = 0; i < MAX_ALTITUDE + 1; i++) {
			m_visible_objects[i].clear();
		}

	}

	int SceneGraph::insertObject(Object* p_o) {

		if (p_o->isActive()) {
			active_objects.insert(p_o);
		}
		else {
			inactive_objects.insert(p_o);
		}
		

		if (p_o->isSolid()) {
			m_solid_objects.insert(p_o);
		}

		if (!valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE)) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Altitude range invalid.");
			return -1;
		}

		m_visible_objects[p_o->getAltitude()].insert(p_o);
		
		return 0;
	}

	int SceneGraph::removeObject(Object* p_o) {
		if (p_o->isActive()) {
			active_objects.remove(p_o);
		}
		else {
			inactive_objects.remove(p_o);
		}

		if (p_o->isSolid()) {
			m_solid_objects.remove(p_o);
		}

		m_visible_objects[p_o->getAltitude()].remove(p_o);

		return 0;
	}

	ObjectList SceneGraph::activeObjects() const {
		ObjectList list;
		if (active_objects.isEmpty()) {
			return list;
		}
		return active_objects;
	}

	ObjectList SceneGraph::solidObjects() const {
		ObjectList list;
		if (m_solid_objects.isEmpty()) {
			return list;
		}
		return m_solid_objects;
	}

	ObjectList SceneGraph::visibleObjects(int altitude) const {

		ObjectList list;

		if (!valueInRange(altitude, 0, MAX_ALTITUDE)) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Altitude not in range, return empty list");
			return list;
		}

		list = m_visible_objects[altitude];

		
		if (m_visible_objects->isEmpty()) {
			LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Debug! Visible Object list in alt: %d empty", altitude);
			return list;
		}
		return list;
	
	}

	ObjectList SceneGraph::inactiveObjects() const {
		ObjectList list;
		if (inactive_objects.isEmpty()) {
			return list;
		}
		return active_objects;
	}

	int SceneGraph::updateAltitude(Object* p_o, int new_alt) {

		if (!valueInRange(new_alt, 0, MAX_ALTITUDE)) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! unable to update altitude of: %d, outside of scope.", new_alt);
			return -1;
		}

		if (!valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE)) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Object outside of altitude scope.");
			return -1;
		}

		if (p_o->getAltitude() == new_alt) {
			LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Debug! no change made in object alt.");
			return 0;
		}

		m_visible_objects[p_o->getAltitude()].remove(p_o);
		m_visible_objects[new_alt].insert(p_o);

		return 0;
	}

	int SceneGraph::updateSolidness(Object* p_o, Solidness new_solidness) {

		// If solidness unchanged, do nothing (but ok).
		if (p_o->getSolidness() == new_solidness) {
			LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Debug! No changes made to object solidness");
			return 0;
		}

		// If was solid, remove from solid objects list.
		if (p_o->isSolid()) {
			m_solid_objects.remove(p_o);
		}

		// If not solid, insert into solid objects list
		if (new_solidness == HARD || new_solidness == SOFT) {
			m_solid_objects.insert(p_o);
		}

		return 0;

	}

	int SceneGraph::updateVisible(Object* p_vo, bool new_visible) {

		// if visibilty unchanged, do nothing (but ok)
		if (p_vo->isVisible() == new_visible) {
			LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Debug! visibility update attempt, no visibility change");
			return 0;
		}


		// if was visible then now invisible, remove from list.
		if (p_vo->isVisible()) {
			m_visible_objects[p_vo->getAltitude()].remove(p_vo);
		}
		else { // Was invisible, so add to list.
			m_visible_objects[p_vo->getAltitude()].insert(p_vo);
		}

		return 0;

	}

	int SceneGraph::updateActive(Object* p_o, bool new_active) {

		if (p_o->isActive() == new_active) {
			LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Debug! active update attempt, no changes.");
			return 0;
		}


		if (p_o->isActive()) {
			active_objects.remove(p_o);
			m_visible_objects[p_o->getAltitude()].remove(p_o);

			if (p_o->isSolid()) {
				m_solid_objects.remove(p_o);
			}

			inactive_objects.insert(p_o);
		}
		else {
			active_objects.insert(p_o);
			
			m_visible_objects[p_o->getAltitude()].insert(p_o);
			if (p_o->isSolid()) {
				m_solid_objects.insert(p_o);
			}

			inactive_objects.remove(p_o);
		}

		return 0;
	}
}