#pragma once

#include <vector>
#include <string>

#include "../Entity.h"
#include "../Maths/Vec2.h"

namespace game { namespace entities {

class Path : public Entity
{
public:
	// Should include all data required for a path to be drawn using SDL functions

	Path();
	~Path();

	// The unique name of the component
	static const std::string name;
	const std::string getName() const override;

	void setup() override;
	void draw(int cameraX, int cameraY, int cameraWidth, int cameraHeight) override;

#pragma message("make getters and setters for this")
	std::vector<maths::Vec2i> points;
};

} }

