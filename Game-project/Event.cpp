#include "Event.h"

namespace game {

Event::Event()
{
}


Event::~Event()
{
}

bool Event::operator==(const Event &other) const 
{
	if (getName() == other.getName()) {
		return true;
	}
	else {
		return false;
	}
}

}
