//
// DisplayManager.h
//

#ifndef __DISPLAY_MANAGER_H__
#define __DISPLAY_MANAGER_H__

//system includes
#include <SFML/Graphics.hpp>

//engine includes
#include "Manager.h"
#include "LogManager.h"
#include "Colour.h"
#include "Vector.h"


enum Justification {
	LEFT_JUSTIFIED,
	CENTER_JUSTIFIED,
	RIGHT_JUSTIFIED
};


const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 80;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 24;
const int WINDOW_STYLE_DEFAULT = sf::Style::Close;
const sf::Color WINDOW_BACKGROUND_COLOUR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Game";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";



namespace df {

	class DisplayManager : public Manager {
	private:

		static df::LogManager& log;
		const std::string CLASS_NAME = "DisplayManager";

		DisplayManager();						// Private (a singleton)
		DisplayManager(DisplayManager const&);  // Don't allow copy.
		void operator=(DisplayManager const&);  // Don't allow assignment
		sf::Font m_font;				// Font used for ASCII graphics
		std::string m_font_file;
		sf::RenderWindow* m_p_window;   // Pointer to SFML window.
		int m_window_horizontal_pixels; // Horizontal pixels in window.
		int m_window_vertical_pixels;   // Vertical pixels in window.
		int m_window_horizontal_chars;  // Horizontal hight of a character.
		int m_window_vertical_chars;	// Vertical hight of a character.
		sf::Color m_window_background_colour; // Background window color.

	public:
		// Get the one and only instance of the DisplayManager.
		static DisplayManager& getInstance();

		// Open graphics window, ready for text-based display.
		// Return 0 if ok, else -1.
		int startUp();

		// Close graphics window.
		void shutDown();

		// Draw characters at window location (x,y) with colour.
		int drawCh(Vector world_pos, char ch, Colour colour) const;

		// Draw string at window location (x,y) with default color.
		// Justified left, center or right.
		// Return 0 if ok, else -1
		int drawString(Vector pos, std::string str, Justification just, 
						Colour colour) const;

		// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		// Return window's vertical maximum (in characters).
		int getVertical() const;

		// Returns window's horizontal maximum (in pixels)
		int getHorizontalPixels() const;

		// Returns window's virtical maximum (in pixels)
		int getVerticalPixels() const;

		// Set default background color. Return true of ok, else false.
		// sets with Colour.h, (IE df::BLUE)
		bool setBackgroundColor(int new_color);

		// Render current window buffer.
		// Return 0 if ok, else -1.
		int swapBuffer();

		// Returns pointer to SFML graphics window.
		sf::RenderWindow* getWindow() const;

		// Computes character height in pixels, based on window size
		float charHeight() const;

		// Computers character width in pixels, based on window size
		float charWidth() const;

		// Convert ASCII spaces (x, y) to window pixels (x, y)
		Vector spaceToPixels(Vector spaces) const;

		// Convert windows pixels (x,y) to ASCII spaces (x, y)
		Vector pixelsToSpaces(Vector pixels) const;
	}; // end class DisplayManager
} // end namespace df
#endif // __DISPLAY_MANAGER_H__