#include "Sprite.h"
#include "../WindowManager.h"
#include "../Utility/FileHelper.h"
#include "../World.h"

#include <string>

namespace game { namespace components {

using namespace utilities;

const std::string Sprite::name = "Sprite";

const rgb* Sprite::transparentColour = new rgb(108, 61, 182);

Sprite::Sprite(int num_states)
{
	imagePaths.resize(num_states);
	animationSequences.resize(num_states);

	layer = FOREGROUND; // Default layer
}

Sprite::~Sprite()
{

}

const std::string Sprite::getName() const
{
	return name;
}

int Sprite::getLayer() const
{
	return layer;
}

void Sprite::setLayer(int _layer)
{
	layer = _layer;
}

SDL_Surface* Sprite::loadImage(std::string filename) {
	SDL_Surface *tmp;
	tmp = SDL_LoadBMP(filename.c_str());

	if (!tmp) {
		fprintf(stderr, "Error: '%s' could not be opened: %s\n", filename, SDL_GetError());
		return NULL;
	}
	else {
		if (SDL_SetColorKey(tmp, SDL_RLEACCEL, SDL_MapRGB(tmp->format, transparentColour->red, transparentColour->green, transparentColour->blue)) == -1)
			fprintf(stderr, "Warning: colorkey will not be used, reason: %s\n", SDL_GetError());
	}

	return tmp;
}

void Sprite::setup(int entityId)
{
	// Add this entity to the list of drawable entities
	World::drawableEntityIDs[layer].push_back(entityId);

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
			SDL_Surface* imageSurface = loadImage(imagePaths[i][j]);
			textures[j] = SDL_CreateTextureFromSurface(WindowManager::renderer, imageSurface);

			if (textures[j] == NULL)
			{
				// Load empty image
				SDL_Surface* imageSurface = loadImage(FileHelper::resourceFolder + "empty.bmp");
				textures[j] = SDL_CreateTextureFromSurface(WindowManager::renderer, imageSurface);

				printf("Unable to load image %s! SDL Error: %s\n", imagePaths[i][j].c_str(), SDL_GetError());
			}
		}

		std::shared_ptr<AnimationSequence> animationSequence(new AnimationSequence(textures));
		animationSequences[i] = animationSequence;
	}
}

void Sprite::setImagePaths(int state_id, std::vector<std::string> _imagePaths)
{
	imagePaths[state_id] = _imagePaths;
}

SDL_Texture* Sprite::getTexture(int state_id)
{
	return animationSequences[state_id]->getTexture();
}

} }