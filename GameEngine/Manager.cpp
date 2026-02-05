//
// Manager.cpp
//

// System includes
#include <string>

// Engine includes
#include "Manager.h"
#include "WorldManager.h"


namespace df {

    Manager::Manager() {
        setType("Manager");
        m_is_started = false;
    }

    Manager::~Manager() {

    }

    void Manager::setType(std::string type) {
        m_type = type;
    }

    std::string Manager::getType() const {
        return m_type;
    }

    int Manager::startUp() {
        m_is_started = true;
        return 0;
    }

    void Manager::shutDown() {
        m_is_started = false;
    }

    bool Manager::isStarted() const {
        return m_is_started;
    }

   int Manager::onEvent(const Event* p_e) const {
       int count = 0;
       ObjectList all_objects = WorldManager::getInstance().getAllObjects();

       for (int i = 0; i < all_objects.getCount(); i++) {
           all_objects[i]->eventHandler(p_e);
           ++count;
       }
       return count;
    }

} // end namespace df