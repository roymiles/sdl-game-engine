#include "Sprite.h"

namespace game { namespace components {

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::setup()
{
	image = SDL_LoadBMP(imagePath.c_str());
	if (image == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "02_getting_an_image_on_the_screen/hello_world.bmp", SDL_GetError());
	}
}

} }