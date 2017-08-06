#pragma once

#include "SDL.h"

class Window
{
public:
	Window();
	~Window();

	bool init();
	void close();

	static SDL_Window* window;
	static SDL_Renderer* renderer;

	// Screen Dimensions constants
	static const int WIDTH;
	static const int HEIGHT;
};

