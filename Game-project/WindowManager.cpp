#include "WindowManager.h"
#include "Globals.h"

#include <iostream>

SDL_Window* WindowManager::window	   = NULL;
SDL_Renderer* WindowManager::renderer  = NULL;

WindowManager::WindowManager()
{
}

WindowManager::~WindowManager()
{
}

bool WindowManager::init()
{
	bool success = true;

	// Initialises SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		// The window to be rendered into
		window = SDL_CreateWindow("Game Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (window == NULL) {
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			SDL_GLContext glcontext = SDL_GL_CreateContext(window);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

void WindowManager::close()
{
	SDL_DestroyRenderer(renderer);

	// Close the window
	SDL_DestroyWindow(window);
	SDL_Quit();
}
