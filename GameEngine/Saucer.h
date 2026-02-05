#include "Object.h"
#include "EventStep.h"

class Saucer : public df::Object {
public:

	Saucer();

	int eventHandler(const df::Event* p_e) override;

};