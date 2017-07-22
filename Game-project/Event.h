#pragma once

namespace game {

class Event
{
public:
	Event();
	~Event();

	bool operator==(const Event &other) const;
};

}
