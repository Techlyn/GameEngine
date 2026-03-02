//
// SceneGraph.cpp
//

// Engine includes
#include "LogManager.h"
#include "SceneGraph.h"
#include "Utility.h"

namespace df {
	SceneGraph::SceneGraph() {

	}
	SceneGraph::~SceneGraph() {

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
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! unable to update altitude, outside of scope.");
			return -1;
		}

		if (!valueInRange(p_o->getAltitude(), 0, MAX_ALTITUDE)) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Object outside of altitude scope.");
			return -1;
		}

		m_visible_objects[p_o->getAltitude()].remove(p_o);
		m_visible_objects[new_alt].insert(p_o);

		return 0;
	}

	int SceneGraph::updateSolidness(Object* p_o, Solidness new_solidness) {

		// If was solid, remove from solid objects list.
		if (p_o->isSolid()) {
			m_solid_objects.remove(p_o);
		}

		if (new_solidness == HARD || new_solidness == SOFT) {
			m_solid_objects.insert(p_o);
		}
	}

	int SceneGraph::updateVisible(Object* p_vo, bool new_visible) {

	}

	int SceneGraph::updateActive(Object* p_o, bool new_active) {
		if (p_o->isActive() == new_active)
			return 0;

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
		}
	}
}