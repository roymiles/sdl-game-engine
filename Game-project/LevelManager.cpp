#include "LevelManager.h"
#include "World.h"

namespace game {

// The dimensions of the current level
const SDL_Rect LevelManager::DIMENSIONS = SDL_Rect(-1000, -1000, 200 * World::METER, 200 * World::METER);

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

}
