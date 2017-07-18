#pragma once

namespace game {

class GameObject
{
public:
	GameObject();
	~GameObject();

	// Called before the main while loop
	virtual void setup() {};

	// Called on every frame
	virtual void update() {};
};

}

