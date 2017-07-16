//
//  main.cpp
//  GameProject
//
//  Created by Aatina Punjabi on 16/07/2017.
//  Copyright © 2017 Aatina Punjabi. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

//Screen Dimensions
const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char * argv[]) {

	//Initialises SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}

	//The window to be rendered into
	SDL_Window *window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

	//Return error if window can't be created
	if (NULL == window) {
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;

		return EXIT_FAILURE;
	}

	//Handles any event that occurs in app
	SDL_Event windowEvent;

	//Constantly running window
	while (true) {
		if (SDL_PollEvent(&windowEvent)) {
			if (SDL_QUIT == windowEvent.type) {
				break;
			}
		}
	}

	//Close the window
	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}
