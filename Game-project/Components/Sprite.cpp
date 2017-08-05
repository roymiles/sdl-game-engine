#include "Sprite.h"
#include <string>

namespace game { namespace components {

const std::string name = "Sprite";
const unsigned int ID  = utilities::hashCode(name.c_str());

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

std::string Sprite::getName() const
{
	return name;
}

unsigned int Sprite::getID() const
{
	return ID;
}

void Sprite::setup()
{
	// Attempt to load image
	image = SDL_LoadBMP(imagePath.c_str());
	if (image == NULL)
	{
		//image = SDL_LoadBMP("question_mark.bmp");
		printf("Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError());
	}
}

void Sprite::setImagePath(std::string _imagePath)
{
	imagePath = _imagePath;
}

} }