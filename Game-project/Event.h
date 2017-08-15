#pragma once

#include <memory>
#include <string>

namespace game {

class Event
{
public:
	Event();
	virtual ~Event() = 0;

	/*
	 * Is this function redundant??
	 */
	virtual const std::string getName() const = 0;
};

typedef std::shared_ptr<Event> eventPointer;

}
