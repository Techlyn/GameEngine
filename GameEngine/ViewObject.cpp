//
// ViewObject.cpp
//

#include "ViewObject.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "EventView.h"
#include "Utility.h"

namespace df {

	ViewObject::ViewObject() {

		// Init Object attributes.
		setSolidness(SPECTRAL);
		setAltitude(MAX_ALTITUDE);
		setType("ViewObject");

		// Initialize ViewObject attributes
		setValue(0);
		setDrawValue();
		setBorder(true);
		setLocation(TOP_CENTER);
		setColour(COLOUR_DEFAULT);

		// Register interest in view events.
		registeredInterest(VIEW_EVENT); 
	}

	int ViewObject::draw() {
		
		std::string temp_str{ "" };
		
		if (m_border) temp_str += " ";
		temp_str += getViewString();
		if (m_draw_value) temp_str += " " + toString(m_value);
		if (m_border) temp_str += " ";

		// Draw centered at pos.
		Vector pos = viewToWorld(getPosition());
		DM.drawString(pos, temp_str, CENTER_JUSTIFIED, getColour());

		if (m_border) {
			// Draw box around display.

		
		}

		return 0;
	}

	int ViewObject::eventHandler(const Event* p_e) {

		// See if this is 'view' event.
		if (p_e->getType() == VIEW_EVENT) {

			const EventView* p_ve = dynamic_cast<const EventView*> (p_e);
			
			// See if this event event is meant for this object.
			if (p_ve->getTag() == getViewString()) {
				if (p_ve->getDelta()) {
					setValue(getValue() + p_ve->getValue());
				}
				else {
					setValue(p_ve->getValue());
				}

				return 1;
			}
		}

		LM.writeLog(CLASS_NAME, LM.LOG_ERROR, 
			"Error! ViewObject event handler called, but no view event declared.");
		return 0;
	}

	void ViewObject::setLocation(ViewObjectLocation new_location) {

		Vector p;
		int y_delta{ 0 };

		switch (new_location) {
		case TOP_LEFT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case TOP_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case TOP_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case CENTER_LEFT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() / 2);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case CENTER_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() / 2);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case CENTER_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() / 2);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case BOTTOM_LEFT:
			p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case BOTTOM_CENTER:
			p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		case BOTTOM_RIGHT:
			p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		default:
			LM.writeLog(CLASS_NAME, LM.LOG_WARNING, "Warning! No View Location given, set to default TOP_CENTER");
			p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
			if (!getBorder()) {
				y_delta = -1;
			}
			break;
		}

		// Shift, as needed ,based on border.
		p.setY(p.getY() + y_delta);

		// Set position of object to new position.
		setPosition(p);

		// Set new location.
		m_location = new_location;
	}

	ViewObjectLocation ViewObject::getLocation() const {
		return m_location;
	}

	void ViewObject::setValue(int new_value) {
		m_value = new_value;
	}

	int ViewObject::getValue() const {
		return m_value;
	}

	void ViewObject::setBorder(bool new_border) {
		if (m_border != new_border) {
			m_border = new_border;
			
			// Reset location to account for border setting.
			setLocation(getLocation());
		}
	}

	bool ViewObject::getBorder() const {
		return m_border;
	}

	void ViewObject::setColour(Colour new_colour) {
		m_colour = new_colour;
	}

	Colour ViewObject::getColour() const {
		return m_colour;
	}

	void ViewObject::setViewString(std::string new_view_string) {
		view_string = new_view_string;
	}

	std::string ViewObject::getViewString() const {
		return view_string;
	}

	void ViewObject::setDrawValue(bool new_draw_value) {
		m_draw_value = new_draw_value;
	}

	bool ViewObject::getDrawValue() const {
		return m_draw_value;
	}




}