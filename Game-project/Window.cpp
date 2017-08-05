#include "Window.h"

#include <iostream>

// Screen Dimensions constants
const int Window::WIDTH = 800;
const int Window::HEIGHT = 600;

SDL_Window* Window::window	   = NULL;
SDL_Renderer* Window::renderer = NULL;

Window::Window()
{
}

Window::~Window()
{
}

bool Window::init()
{
	bool success = true;

	// Initialises SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
	}
	else {
		// The window to be rendered into
		window = SDL_CreateWindow("Game Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
		if (window == NULL) {
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

void Window::close()
{
	SDL_DestroyRenderer(renderer);

	// Close the window
	SDL_DestroyWindow(window);
	SDL_Quit();
}
