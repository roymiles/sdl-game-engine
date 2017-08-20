//  main.cpp
//  GameProject
//
//  Aatina and Roys project :D
//

#include <iostream>
#include <vector>
#include <memory>

#include "SDL.h"

#include "Window.h"
#include "World.h"
#include "EventManager.h"
#include "PhysicsEngine.h"
#include "RenderingEngine.h"
#include "Algorithms/PathFinding.h" // TEMPORARY
#include "Utility/FileHelper.h" // TEMPORARY

#include "Entities/Character.h"

using namespace game;
using namespace entities;
using namespace algorithms; // TEMPORARY
using namespace utilities; // TEMPORARY

const int fps = 40;
const int minframetime = 1000 / fps;

int main(int argc, char * argv[]) {
    
	std::shared_ptr<Window> window(new Window());
    if(!window->init()){
		std::cout << "Failed to initialize!" << std::endl;
		return EXIT_FAILURE;
    }
        
	// Manages all the entities
	std::shared_ptr<World> world(new World());

	// Call setup on all entities
	world->setup();

	// TEMPORARY
	std::shared_ptr<PathFinding> p(new PathFinding(world));
	std::vector<std::vector<char>> navMesh = p->createNavMesh(10);
	FileHelper::writeMatrixToFile<char>(navMesh);
	std::vector<moves> moveList = p->astar(navMesh);

	// Handles any event that occurs in app
	SDL_Event window_event;
	std::unique_ptr<EventManager> eventManager(new EventManager(world));

	// Physics engine is responsible for detecting and reacting to collisions
	std::unique_ptr<PhysicsEngine> physicsEngine(new PhysicsEngine(world));

	// Rendering engine is responsible for drawing appropriate entities to screen
	std::unique_ptr<RenderingEngine> renderingEngine(new RenderingEngine(world));
	
	unsigned int frametime;

    while (true) {
		frametime = SDL_GetTicks();

#pragma message("Maybe pass in some delta time into these update functions? like how unity does it")
#pragma message("Double check update() order")
		// Handle inputs
		eventManager->update(&window_event);

		// Physics Engine
		physicsEngine->update();

		// Logic
		world->update();

		// Render
		renderingEngine->update();

		// Wait until the next frame
		// This ensures the game runs at the same
		// speed on all computers
		if (SDL_GetTicks() - frametime < minframetime) {
			SDL_Delay(minframetime - (SDL_GetTicks() - frametime));
		}
    }
    
	// Delete renderer, window
    window->close();
    
    return EXIT_SUCCESS;
}
