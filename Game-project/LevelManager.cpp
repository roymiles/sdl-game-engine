#include "LevelManager.h"
#include "World.h"
#include "Globals.h"

namespace game {

// The dimensions of the current level
const SDL_Rect LevelManager::DIMENSIONS = SDL_Rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

LevelManager::LevelManager()
{
}


LevelManager::~LevelManager()
{
}

}
