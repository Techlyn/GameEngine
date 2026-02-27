//
// EventView.cpp
//

#include "EventView.h"

namespace df {

	EventView::EventView(std::string new_tag, int new_value, bool new_delta) {
		m_tag = new_tag;
		m_value = new_value;
		m_delta = new_delta;
	}

	void EventView::setTag(std::string new_tag) {
		m_tag = new_tag;
	}

	std::string EventView::getTag() const {
		return m_tag;
	}

	void EventView::setValue(int new_value) {
		m_value = new_value;
	}

	int EventView::getValue() const {
		return m_value;
	}

	void EventView::setDelta(bool new_delta) {
		m_delta = new_delta;
	}

	bool EventView::getDelta() const {
		return m_delta;
	}
}