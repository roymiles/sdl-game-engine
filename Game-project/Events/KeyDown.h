#pragma once

#include "../Event.h"

namespace game { namespace events {

class KeyDown : public Event
{
public:
	KeyDown();
	~KeyDown();

	const std::string getName() const override;

private:
	static const std::string name;
};

} }

