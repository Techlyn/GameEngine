//
// QuitButton.cpp
//

#include "QuitButton.h"
#include "GameManager.h"

using namespace df;


QuitButton::QuitButton() {
	setViewString("Quit");
	setLocation(BOTTOM_CENTER);
}

void QuitButton::callback() {
	GM.setGameOver();
}