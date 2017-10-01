#include "LevelManager.h"
#include "World.h"
#include "Globals.h"

namespace game {

// The dimensions of the current level
const SDL_Rect LevelManager::DIMENSIONS = SDL_Rect(-1000, -1000, 200 * METER, 200 * METER);

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

}
