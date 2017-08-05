#pragma once

#include <memory>
#include <string>

namespace game {

class Event
{
public:
	Event();
	virtual ~Event() = 0;
	virtual const std::string getName() const = 0;

	bool operator==(const Event &other) const;
};

typedef std::shared_ptr<Event> eventPointer;

}
