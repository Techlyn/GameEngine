#include <stdexcept>

#include "ObjectList.h"
#include "LogManager.h"




namespace df {

	ObjectList::ObjectList()
		: m_count(0)
	{
	

	for (int i = 0; i < MAX_OBJECTS; i++) {
			m_p_obj[i] = nullptr;
			
		}
	}

	//ObjectList::~ObjectList() {
	//	log.writeLog(CLASS_NAME, LogManager::LOG_INFO, "%s: Destroyed at %p", __func__, this);

	//	// Deletes all remaining objects
	//	for (int i = 0; i < m_count; i++) {
	//		if (m_p_obj[i] != nullptr) {
	//			delete m_p_obj[i];
	//			m_p_obj[i] = nullptr;
	//			--m_count;
	//		}
	//	}
	//	log.writeLog(CLASS_NAME, LogManager::LOG_DEBUG, "%s: objects in list destroyed", __func__);
	//}

	int ObjectList::insert(Object* p_o) {
		if (m_count == MAX_OBJECTS || p_o == nullptr) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "%s object inserted failed", __func__);
			return -1;
		}

		//checks if object pointer is already in list
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) return -2;
		}
		m_p_obj[m_count] = p_o;
		m_count++;
		return 0;
		

	}

	int ObjectList::remove(Object* p_o) {
		for (int i = 0; i < m_count; i++) {
			if (m_p_obj[i] == p_o) {	// found ..
				for (int j = i; j < m_count - 1; j++) { // scoot over
					m_p_obj[j] = m_p_obj[j + 1];
				}
				// as every pointer has been shifted down an index number,
				// last pointer becomes a nullptr.
				m_p_obj[m_count - 1] = nullptr;
				m_count--;
				
				return 0; // Found.
			}
		}
		return -1;

	}

	void ObjectList::clear() {
		//emptys list [to work on, objects are still in memory after pointer clear]
		m_count = 0;
	}

	int ObjectList::getCount() const {
		//getter for current list count
		return m_count;
	}

	bool ObjectList::isEmpty() const {

		//iterates through the list
		for (int i = 0; i < MAX_OBJECTS; i++) {
			//if finds pointer returns false (found a pointer, list is not empty)
			if (m_p_obj[i] != nullptr) {
				return false;
			}
		}
		return true; //no pointer found, list is empty
	}

	bool ObjectList::isFull() const {
		
		for (int i = 0; i < MAX_OBJECTS; i++) {
			// if any in list contains a nullptr, list is not full
			if (m_p_obj[i] == nullptr) {
				return false;
			}
		}
		return true; // found no nullptr, list is full.
	}


	Object* ObjectList::operator[](int index) {
		//checks to make sure index within [] are in bounds to m_count
		// if greater than m_count or less than 0, throw error
		if (index >= m_count || index < 0)
			throw std::out_of_range("Invalid index!");

		//otherwise returns the object pointer.
		return m_p_obj[index];

	}

	ObjectList ObjectList::operator+(ObjectList list) {
		
		// stat with first list (list acted upon)
		ObjectList big_list = *this;

		// inserts "list" into the list acted upon
		for (int i = 0; i < list.getCount(); i++) {
			big_list.insert(list[i]);
		}
		
		// returns the lists added together.
		return big_list;
	}

	void ObjectList::listList() const {
		LM.writeLog("%s Listing all in generated object list",__func__);
		LM.writeLog("i\tpointer");
		for (int i = 0; i < MAX_OBJECTS; i++) {
			LM.writeLog("%d\t%p", i, m_p_obj[i]);
		}
		LM.writeLog("end of %s", __func__);
	}

}


