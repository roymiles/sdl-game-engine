#pragma once

#include "../Event.h"

namespace game { namespace events {

class KeyDown : public Event
{
public:
	KeyDown();
	~KeyDown();

	const std::string getName() const override;
	// This needs to be public so that it can easily be read without
	// creating unnecessary event instances
	static const std::string name;
};

} }

