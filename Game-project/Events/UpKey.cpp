#include "UpKey.h"

namespace game {
namespace events {

const std::string UpKey::name = "UpKey";

UpKey::UpKey()
{
}

UpKey::~UpKey()
{
}

const std::string UpKey::getName() const
{
	return name;
}

}
}
