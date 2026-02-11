//
// DisplayManager.cpp
//

#include "DisplayManager.h"
#include "Colour.h"
#include "Utility.h"



namespace df {

	DisplayManager::DisplayManager() {
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "%s created at %p", __func__, this);
		setType("DisplayManager");
		m_font_file = FONT_FILE_DEFAULT;
		m_p_window = NULL;
		m_window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
		m_window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
		m_window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
		m_window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
		m_window_background_colour = WINDOW_BACKGROUND_COLOUR_DEFAULT;




	}

	void DisplayManager::operator=(DisplayManager const&) {

	}

	DisplayManager& DisplayManager::getInstance() {
		static DisplayManager instance;
		return instance;
	}

	int DisplayManager::startUp() {
		if (m_p_window != NULL) {
			LM.writeLog(CLASS_NAME, LM.LOG_INFO, "window already created.");
			return 0;
		}

		sf::Vector2u size = sf::Vector2u(m_window_horizontal_pixels, m_window_vertical_pixels);
		m_p_window = new sf::RenderWindow(sf::VideoMode(size), WINDOW_TITLE_DEFAULT, WINDOW_STYLE_DEFAULT);

		if (!m_p_window) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Unable to allocate RenderWindow"); 
			return -1;
		}

		m_p_window->setMouseCursorVisible(false);
		m_p_window->setVerticalSyncEnabled(true);
		

		if (m_font.openFromFile(m_font_file) == false) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! unable to find font file");
			return -1;
		}

		Manager::startUp();
		LM.writeLog(CLASS_NAME, LM.LOG_INFO, "Display Manager Startup: SUCCESS");
		return 0;
	}

	void DisplayManager::shutDown() {
		m_p_window->setMouseCursorVisible(true);
		m_p_window->setVerticalSyncEnabled(false);
		m_p_window->close();
		delete m_p_window;
		Manager::shutDown();
	}

	int DisplayManager::drawCircle(sf::CircleShape circle) {
		m_p_window->draw(circle);
		return 0;
	}

	int DisplayManager::drawCh(Vector world_pos, char ch, Colour colour) const {
		// Window allocation check
		if (m_p_window == NULL) {
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Window not allocated");
			return -1;
		}

		// Converts spaces (x,y) to pixels (x,y)
		//Vector pixel_pos = spaceToPixels(world_pos);

		Vector view_pos = worldToView(world_pos);

		// Draw background rectangle since text is "see through" in SFML.
		/*static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
		rectangle.setFillColor(WINDOW_BACKGROUND_COLOUR_DEFAULT);
		rectangle.setPosition(sf::Vector2f({ pixel_pos.getX() - charWidth() / 10},
			{ pixel_pos.getY() + charHeight() / 5}));
		m_p_window->draw(rectangle);*/

		// Create character text to draw.
		static sf::Text text(m_font); 
		text.setString(ch);
		text.setStyle(sf::Text::Bold); // Make bold.

		//Sacle to right size.
		if (charWidth() < charHeight()) {
			text.setCharacterSize(charWidth() * 2);
		}
		else {
			text.setCharacterSize(charHeight() * 2);
		}
		// SetSFML colour based on DF colour.
		switch (colour) {
		case YELLOW:
			text.setFillColor(sf::Color::Yellow);
			break;
		case RED:
			text.setFillColor(sf::Color::Red);
			break;
		case GREEN:
			text.setFillColor(sf::Color::Green);
			break;
		case BLUE:
			text.setFillColor(sf::Color::Blue);
			break;
		case MAGENTA:
			text.setFillColor(sf::Color::Magenta);
			break;
		case CYAN:
			text.setFillColor(sf::Color::Magenta);
			break;
		case WHITE:
			text.setFillColor(sf::Color::White);
			break;
		case BLACK:
			text.setFillColor(sf::Color::Black);
			break;
		default:
			LM.writeLog(CLASS_NAME, LM.LOG_ERROR, "Error! Colour not recognised or added.");
			break;
		}

		//Set position in window (in pixels)
		text.setPosition(sf::Vector2f( view_pos.getX(), view_pos.getY() ));

		m_p_window->draw(text);

		return 0;

	}

	int DisplayManager::drawString(Vector pos, std::string str, 
										Justification just, 
										Colour colour) const {

		// get starting position.
		Vector starting_pos = pos;
		switch (just) {
		case CENTER_JUSTIFIED:
			starting_pos.setX(pos.getX() - static_cast<float>(str.size()) / 2);
			break;
		case RIGHT_JUSTIFIED:
			starting_pos.setX(pos.getX() - str.size());
			break;
		case LEFT_JUSTIFIED:
			break;
		default:
			break;
		}

		// draw string character by character.
		for (int i = 0; i < str.size(); i++) {
			Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
			drawCh(temp_pos, str[i], colour);
		}
		
		// if ok
		return 0;

	}

	int DisplayManager::getHorizontal() const {
		return m_window_horizontal_chars;
	}
	int DisplayManager::getVertical() const {
		return m_window_vertical_chars;
	}
	
	int DisplayManager::getHorizontalPixels() const {
		return m_window_horizontal_pixels;
	}
	int DisplayManager::getVerticalPixels() const {
		return m_window_vertical_pixels;
	}

	bool DisplayManager::setBackgroundColor(int new_color) {
		switch (new_color) {
		case BLACK:
			m_window_background_colour = sf::Color::Black;
			break;
		case RED:
			m_window_background_colour = sf::Color::Red;
			break;
		case GREEN:
			m_window_background_colour = sf::Color::Green;
			break;
		case YELLOW:
			m_window_background_colour = sf::Color::Yellow;
			break;
		case BLUE:
			m_window_background_colour = sf::Color::Blue;
			break;
		case MAGENTA:
			m_window_background_colour = sf::Color::Magenta;
			break;
		case CYAN:
			m_window_background_colour = sf::Color::Cyan;
			break;
		case WHITE:
			m_window_background_colour = sf::Color::White;
			break;
		default:
			LM.writeLog(LogManager::LOG_ERROR, "Error! Colour not recognised.");
			return false;
		}
		return true;
	}

	int DisplayManager::swapBuffer() {
		if (m_p_window == NULL) {
			LM.writeLog(LogManager::LOG_ERROR, "Error! window returned NULL");
			return -1;
		}

		m_p_window->display();
		m_p_window->clear(m_window_background_colour);
		return 0;
	}

	sf::RenderWindow* DisplayManager::getWindow() const {
		return m_p_window;
	}

	float DisplayManager::charHeight() const {
		return m_window_vertical_pixels / m_window_vertical_chars;
	}

	float DisplayManager::charWidth() const {
		return m_window_horizontal_pixels / m_window_horizontal_chars;
	}

	Vector DisplayManager::spaceToPixels(Vector spaces) const {
		Vector v;
		v.setX(spaces.getX() * charWidth());
		v.setY(spaces.getY() * charHeight());
		return v;

	}

	Vector DisplayManager::pixelsToSpaces(Vector pixels) const {
		Vector v;
		v.setX(pixels.getX() / charWidth());
		v.setY(pixels.getY() / charHeight());
		return v;
	}
}