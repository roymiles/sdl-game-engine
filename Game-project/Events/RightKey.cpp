#include "RightKey.h"

namespace game {
namespace events {

const std::string RightKey::name = "RightKey";

RightKey::RightKey()
{
}

RightKey::~RightKey()
{
}

const std::string RightKey::getName() const
{
	return name;
}

}
}
