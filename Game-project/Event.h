#pragma once

#include <memory>

namespace game {

class Event
{
public:
	Event();
	virtual ~Event() = 0;

	bool operator==(const Event &other) const;
};

typedef std::shared_ptr<Event> eventPointer;

}
