//
//	ObjectListIterator.cpp
// 

#include "LogManager.h"
#include "ObjectListIterator.h"
#include "ObjectList.h"

namespace df {


	ObjectListIterator::ObjectListIterator() {
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "%s: created at %p", __func__, this);

		m_index = 0;
		m_p_list = nullptr;
	}

	ObjectListIterator::ObjectListIterator(const ObjectList* p_l) :
		m_p_list(p_l)
	{
		first();
	}

	void ObjectListIterator::first() {
		m_index = 0;
	}

	void ObjectListIterator::next() {
		if (m_index < m_p_list->m_count) {
			m_index++;
		}
	}

	bool ObjectListIterator::isDone() const {
		return (m_index == m_p_list->m_count);
	}

	Object* ObjectListIterator::currentObject() const {
		return m_p_list->m_p_obj[m_index];
	}

}