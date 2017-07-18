//
//  main.cpp
//  GameProject
//
//  Created by Aatina Punjabi on 16/07/2017.
//  Copyright 2017 Aatina Punjabi. All rights reserved.
//

#include <iostream>

#include "SDL.h"
// The following is needed because SDL_main redefines the main function
#undef main

#include "Events/EventManager.h"

using namespace game;

// Screen Dimensions constants
const int WIDTH = 800, HEIGHT = 600;

const int fps = 40;
const int minframetime = 1000 / fps;

int main(int argc, char * argv[]) {

	// Initialises SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}

	// The window to be rendered into
	SDL_Window *window = SDL_CreateWindow("2D Sims", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);


	//Return error if window can't be created
	if (NULL == window) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;

		return EXIT_FAILURE;
	}

	// Handles any event that occurs in app
	SDL_Event window_event;
	events::EventManager* event_manager = new events::EventManager();

	int frametime;

	// Main game loop
	while (true) {

		frametime = SDL_GetTicks();

		// Handle inputs
		event_manager->handle_inputs(&window_event);

		// logic
		// update screen

		// Wait until the next frame
		// This ensures the game runs at the same
		// speed on all computers
		if (SDL_GetTicks() - frametime < minframetime) {
			SDL_Delay(minframetime - (SDL_GetTicks() - frametime));
		}
	}

	// Close the window
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}