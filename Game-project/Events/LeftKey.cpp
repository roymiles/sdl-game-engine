#include "LeftKey.h"

namespace game {
namespace events {

const std::string LeftKey::name = "LeftKey";

LeftKey::LeftKey()
{
}

LeftKey::~LeftKey()
{
}

const std::string LeftKey::getName() const
{
	return name;
}

}
}
