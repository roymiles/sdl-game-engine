#pragma once

#include <string>
#include <vector>

#include "../Component.h"
#include "../Utility/FileHelpers.h" // Access to image file paths
#include "../Utility/AnimationSequence.h" // Every sprite has an AnimationSequence object to iterate through
#include "../Window.h"
#include "SDL.h" 

namespace game { namespace components {

enum layers : int {
	BACKGROUND = 0,
	FOREGROUND = 1,

	SIZE = 2 // Number of layers, used for looping
};

class Sprite : public Component
{
	// TODO: Move function definitions back into cpp file
public:
	// Should include all data required for an entity to be drawn

	Sprite(int num_states)
	{	
		imagePaths.resize(num_states);
		animationSequences.resize(num_states);

		zIndex = FOREGROUND; // Default layer
	}

	~Sprite()
	{

	}

	// The unique name of the component
	static const std::string name;

	const std::string getName() const override
	{
		return name;
	}
        
    int getZIndex() const
    {
        return zIndex;
    }
        
    void setZIndex(int _zIndex)
    {
        zIndex = _zIndex;
    }

	SDL_Surface* loadImage(std::string filename) {
		SDL_Surface *tmp;
		tmp = SDL_LoadBMP(filename.c_str());

		if (!tmp) {
			fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename, SDL_GetError());
			return NULL;
		}
		else {
			if (SDL_SetColorKey(tmp, SDL_RLEACCEL, SDL_MapRGB(tmp->format, 255, 255, 255)) == -1)
				fprintf(stderr, "Warning: colorkey will not be used, reason: %s\n", SDL_GetError());
		}

		return tmp;
	}
	
	void setup()
	{
		std::vector<SDL_Texture*> textures;
		// Loop through all the states
		for (int i = 0; i < imagePaths.size(); i++)
		{
			// Create an instance of AnimationSequence and then pass in the
			// vector of image paths
			textures.clear();
			textures.resize(imagePaths[i].size());

			for (int j = 0; j < imagePaths[i].size(); j++)
			{
				SDL_Surface* imageSurface = loadImage(imagePaths[i][j]); //SDL_LoadBMP(imagePaths[i][j].c_str());
				textures[j] = SDL_CreateTextureFromSurface(Window::renderer, imageSurface);

				if (textures[j] == NULL)
				{
					//image = SDL_LoadBMP("question_mark.bmp");
					printf("Unable to load image %s! SDL Error: %s\n", imagePaths[i][j].c_str(), SDL_GetError());
				}
			}

			std::shared_ptr<AnimationSequence> animationSequence(new AnimationSequence(textures));
			animationSequences[i] = animationSequence;
		}
	}

	void setImagePaths(int state_id, std::vector<std::string> _imagePaths)
	{
		imagePaths[state_id] = _imagePaths;
	}

	SDL_Texture* getTexture(int state_id)
	{
		return animationSequences[state_id]->getTexture();
	}

private:
	// The first index is for the state and the second is the paths of 
	// the sprites in that animation sequence
	std::vector<std::vector<std::string>> imagePaths;
	std::vector<std::shared_ptr<AnimationSequence>> animationSequences; // An animation sequence for each state

	int zIndex; 
};

} }

