#include "Character.h"

namespace game { namespace entity {

Character::Character()
{
}


Character::~Character()
{
}

void Character::setup()
{

}

void Character::update()
{

}

void Character::onEvent(std::string key)
{
	switch (key) {
		case "KEY_UP":
			std::cout << "Move up" << std::endl;
			break;
	}
}

} }
