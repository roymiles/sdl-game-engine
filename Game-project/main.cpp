//  main.cpp
//  GameProject
//
//  Aatina and Roys project :D
//

#include <iostream>
#include <vector>
#include <memory>

#include "SDL.h"

#include "World.h"
#include "EventManager.h"
#include "PhysicsEngine.h"
#include "RenderingEngine.h"

#include "Entities\Character.h"

using namespace game;
using namespace entities;

// Screen Dimensions constants
const int WIDTH = 800, HEIGHT = 600;

const int fps = 40;
const int minframetime = 1000 / fps;

SDL_Window  *window			= NULL;
SDL_Surface *screenSurface	= NULL;
SDL_Surface *imageSurface	= NULL;

/*
 Functions
 */

bool init();
void close();

bool init(){
    bool success = true;
    
    // Initialises SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
    }else{
        // The window to be rendered into
        window = SDL_CreateWindow("Game Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if (window == NULL){
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }else{
            // Get window surface
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

void close()
{
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;
    
    // Close the window
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char * argv[]) {
    
    if(!init()){
		std::cout << "Failed to initialize!" << std::endl;
		return EXIT_FAILURE;
    }

    // Constantly running window
    SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
    SDL_UpdateWindowSurface(window);
        
	// Manages all the entities
	std::shared_ptr<World> world(new World());

	// -------------- Temporary ---------------
	// Create entities for level
	std::shared_ptr<Character> character(new Character());
	world->createEntity(character);
	// ----------------------------------------

	// Handles any event that occurs in app
	//SDL_Event window_event;
	std::unique_ptr<EventManager> eventManager(new EventManager(world));

	// Physics engine is responsible for detecting and reacting to collisions
	std::unique_ptr<PhysicsEngine> physicsEngine(new PhysicsEngine(world));

	// Rendering engine is responsible for drawing appropriate entities to screen
	std::unique_ptr<RenderingEngine> renderingEngine(new RenderingEngine(world, window, screenSurface));

	// Call setup on all entities
	world->setup();
	
	unsigned int frametime;

    while (true) {
		frametime = SDL_GetTicks();

#pragma message("Maybe pass in some delta time into these update functions? like how unity does it")
#pragma message("Double check update() order")
		// Handle inputs
		//eventManager->update(&window_event);

		// Physics Engine
		// physicsEngine->update();

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
    
    close();
    
    return EXIT_SUCCESS;
}