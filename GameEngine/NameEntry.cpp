#include "LogManager.h"
#include "NameEntry.h"

using namespace df;

NameEntry::NameEntry() {
	setViewString("Text Example: ");
	setLocation(df::CENTER_CENTER);
	setLimit(90);
}

void NameEntry::callback() {
	LM.writeLog("High score: %s", getText().c_str());
}