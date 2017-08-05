#pragma once

#include "../Event.h"

namespace game { namespace events {

class KeyUp : public Event
{
public:
	KeyUp();
	~KeyUp();

	const std::string getName() const override;

private:
	static const std::string name;
};

} }

