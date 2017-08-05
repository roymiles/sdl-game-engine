#pragma once

#include "../Event.h"

namespace game { namespace events {

class KeyUp : public Event
{
public:
	static const int ID;

	KeyUp();
	~KeyUp();
};

} }

