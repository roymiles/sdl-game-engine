#include "DownKey.h"

namespace game {
namespace events {

const std::string DownKey::name = "DownKey";

DownKey::DownKey()
{
}

DownKey::~DownKey()
{
}

const std::string DownKey::getName() const
{
	return name;
}

}
}
