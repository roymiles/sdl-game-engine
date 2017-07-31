#pragma once

namespace game {

typedef std::shared_ptr<Event> eventPointer;

class Event
{
public:
	Event();
	~Event();

	bool operator==(const Event &other) const;
};

}
