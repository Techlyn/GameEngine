//
// Sprite.h
//

#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Frame.h"
#include "LogManager.h"

namespace df {
	
	class Sprite {

	private:
		std::string CLASS_NAME = "Sprite";

		int m_width;			// Sprtie Width.
		int m_height;			// Sprite Height.
		int m_max_frame_count;	// Max number frames sprite can have.
		int m_frame_count;		// Actual number of frames sprite has.
		Colour m_colour;		// optional colour for entire sprite.
		int m_slowdown;			// Animation slowdown (1= no slowdown, 0= strop).
		Frame* m_frame;			// Array of frames.
		std::string m_label;	// Text label to identify sprite.
		char m_transparency;	// Spirit transparent character (0 if none).
		Sprite();				// Sprite always has one arg, the frame count.

	public:
		// Destroy sprite, deleting any allocated frames.
		~Sprite();

		// Create sprite with indicated maximum number of frames.
		Sprite(int max_frames);

		// Set width of sprite
		void setWidth(int new_width);

		// Get width of sprite.
		int getWidth() const;

		// Set height of sprite.
		void setHeight(int new_height);

		// Get height of sprite.
		int getHeight() const;

		// Set Colour of sprite
		void setColour(Colour new_colour);

		// Get Colour of sprite.
		Colour getColour() const;

		// Get total count of frames in sprite.
		int getFrameCount() const;

		// Add frame to sprite,
		// return -1 if frame array full, else 0.
		int addFrame(Frame new_frame);

		// Get next sprite frame indicated by number.
		// Return empty frame if out of range [o, m_frame_count -1].
		Frame getFrame(int frame_number) const;

		// Set label associated with sprite.
		void setLabel(std::string new_label);

		// get label associated with sprite.
		std::string getLabel() const;

		// Set animation slowdown value.
		// Value in multiples of GameManager frame time.
		void setSlowdown(int new_sprite_slowdown);

		// Get animation slowdown value.
		// Value in multiples of GameManager frame time.
		int getSlowdown() const;

		// Draw indicated frame centered at position (x, y).
		// Return 0 if ok, else -1
		// Note: top-left coordinate is (0,0).
		int draw(int frame_number, Vector position) const;

		// Set sprite transparent character (0 means none).
		void setTransparency(char new_transparency);

		// Get sprites transparency character (0 means none).
		char getTransparency() const;

	}; // end class Sprite
} // end namespace df


#endif // __SPRITE_H__