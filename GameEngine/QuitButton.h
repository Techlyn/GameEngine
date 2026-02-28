//
// Button.h
//

#ifndef __QUIT_BUTTON_H__
#define __QUIT_BUTTON_H__

#include "Button.h"

using namespace df;

	class QuitButton : public Button {
	public:
		QuitButton();
		void callback();
	};

#endif // __QUIT_BUTTON_H__
