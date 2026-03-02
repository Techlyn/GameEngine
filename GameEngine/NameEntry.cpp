#include "LogManager.h"
#include "NameEntry.h"

using namespace df;

NameEntry::NameEntry() {
	setViewString("Enter initials: ");
	setLocation(df::CENTER_CENTER);
	setLimit(3);
}

void NameEntry::callback() {
	LM.writeLog("High score: %s", getText().c_str());
}