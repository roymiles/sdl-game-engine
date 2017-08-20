#pragma once

#include <string>
#include <vector>

#include "../Component.h"
#include "../Utility/FileHelper.h" // Access to image file paths
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
public:
	// Should include all data required for an entity to be drawn

	Sprite(int num_states);
	~Sprite();

	// The unique name of the component
	static const std::string name;

	const std::string getName() const override;
        
	int getLayer() const;
	void setLayer(int _layer);

	SDL_Surface* loadImage(std::string filename);
	
	void setup() override;

	void setImagePaths(int state_id, std::vector<std::string> _imagePaths);
	SDL_Texture* getTexture(int state_id);

private:
	// The first index is for the state and the second is the paths of 
	// the sprites in that animation sequence
	std::vector<std::vector<std::string>> imagePaths;
	std::vector<std::shared_ptr<AnimationSequence>> animationSequences; // An animation sequence for each state

	int layer; 
};

} }

