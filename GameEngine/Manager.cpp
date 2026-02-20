//
// Manager.cpp
//

// System includes
#include <string>

// Engine includes
#include "Manager.h"
#include "WorldManager.h"
#include "Object.h"
#include "ObjectList.h"
#include "Event.h"

namespace df {

    Manager::Manager() {
        setType("Manager");
        m_is_started = false;

        event_count = 0;

        for (int i = 0; i < MAX_EVENTS - 1; i++) {
            event[i] = "";
        }
     
        
    }

    Manager::~Manager() {

    }

    bool Manager::isValid(std::string event_name) const {
        return false;
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

       for (int i = 0; i < event_count - 1; i++) {
           if (event[i] == p_e->getType()) {
               for (int j = 0; obj_list[i].getCount(); j++) {
                   //ObjectList o_l = obj_list[i];
                   ObjectList o_l = obj_list[i];
                   o_l[j]->eventHandler(p_e);
                   ++count;
               }
           }

       }

       return count;
    }

   int Manager::registerInterest(Object* p_o, std::string event_type) {

       // Check to see if event has been added previously.
       for (int i = 0; i < event_count - 1; i++) {
           if (event[i] == event_type) {
               obj_list[i].insert(p_o);
               return 0;
           }
       }

       // Otherwise, new event.
       if (event_count >= MAX_EVENTS) {
           LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Event List is full");
           return -1;
       }
       event[event_count] = event_type;
       obj_list[event_count].clear();
       obj_list[event_count].insert(p_o);
       ++event_count;
       LM.writeLog(CLASS_NAME, LM.LOG_DEBUG, "Success, event added to register");
       return 0;
   }

   int Manager::unregisterInterest(Object* p_o, std::string event_type) {

       // Check for event.
       for (int i = 0; i < event_count - 1; i++) {
           if (event[i] == event_type) {
               obj_list[i].remove(p_o);
           }
           if (obj_list[i].isEmpty()) {
               obj_list[i] = obj_list[i + 1];
               event[i] = event[i + 1];
               --event_count;
           }
          
       }

       return 0;
   }



} // end namespace df