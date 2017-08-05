#include "Sprite.h"
#include "../Window.h"

#include <string>

namespace game { namespace components {

const std::string Sprite::name = "Sprite";

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

const std::string Sprite::getName() const
{
	return name;
}

void Sprite::setup()
{
	// Attempt to load image
	imageSurface = SDL_LoadBMP(imagePath.c_str());
	imageTexture = SDL_CreateTextureFromSurface(Window::renderer, imageSurface);
	// imageTexture = IMG_LoadTexture(Window::renderer, imagePath.c_str());
	if (imageTexture == NULL)
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