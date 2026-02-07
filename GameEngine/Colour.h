//
// Color.h
//
#ifndef __COLOUR_H__
#define __COLOUR_H__

namespace df {

	

	enum Colour {
		UNDEFINED_COLOUR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
	};

	const Colour COLOUR_DEFAULT = WHITE;
} // end namespace df
#endif //__COLOUR_H__
