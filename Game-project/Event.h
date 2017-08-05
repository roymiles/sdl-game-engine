#pragma once

#include <memory>

namespace game {

class Event
{
public:
	Event();
	~Event();

	bool operator==(const Event &other) const;
};

typedef std::shared_ptr<Event> eventPointer;

}
