#pragma once

#include <string>
#include <vector>

#include "../Component.h"
#include "../Utility/FileHelpers.h" // Access to image file paths
#include "../Window.h"
#include "SDL.h" 

namespace game { namespace components {

class Sprite : public Component
{
	// TODO: Move function definitions back into cpp file
public:
	// Should include all data required for an entity to be drawn

	Sprite()
	{

	}

	~Sprite()
	{

	}

	const std::string getName() const override
	{
		return name;
	}

	void setup()
	{
		// Attempt to load images
		for (int i = 0; i < imagePaths.size(); i++)
		{
			SDL_Surface* imageSurface = SDL_LoadBMP(imagePaths[i].c_str());
			imageTextures[i] = SDL_CreateTextureFromSurface(Window::renderer, imageSurface);
			// imageTexture = IMG_LoadTexture(Window::renderer, imagePath.c_str());
			if (imageTextures[i] == NULL)
			{
				//image = SDL_LoadBMP("question_mark.bmp");
				printf("Unable to load image %s! SDL Error: %s\n", imagePaths[i].c_str(), SDL_GetError());
			}
		}
	}

	// TODO: I really don't like this function name
	void setNumberOfImages(size_t size)
	{
		imagePaths.resize(size);
		imageTextures.resize(size);
	}

	void setImagePath(int id, std::string _imagePath)
	{
		imagePaths[id] = _imagePath;
	}

	SDL_Texture* getTexture(int id)
	{
		return imageTextures[id];
	}

private:
	// The path to the image
	std::vector<std::string> imagePaths;
	std::vector<SDL_Texture*> imageTextures;

	// The unique name of the component
	static const std::string name;
};

} }

