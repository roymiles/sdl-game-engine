#pragma once

#include "../Entity.h"
#include "../Components/Sprite.h"
#include "../Components/Transform.h"
#include "../Components/RigidBody.h"
#include "../Utility/FileHelper.h"

namespace game { namespace entities {

using namespace components;
using namespace utilities;

class Box : public Entity
{
public:
	Box(int _width, int _height, std::vector<std::string> _idleImagePaths);
	~Box();

	void setup(int entityId) override;
	void update() override;
	const std::string getName() const override;
	int getCurrentState() const override;

	const enum state : int { IDLE, SIZE = 1 };

private:
	static const std::string name;

	const int width, height;

	// Default sprite images are empty
	std::vector<std::string> idleImagePaths = { FileHelper::resourceFolder + "empty.bmp" };

	state currentState;
};

} }
