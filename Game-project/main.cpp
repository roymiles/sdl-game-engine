//  main.cpp
//  GameProject
//
//  Created by Aatina Punjabi on 16/07/2017.
//  Copyright 2017 Aatina Punjabi. All rights reserved.
//

#include <iostream>
#include <vector>

#include "SDL.h"
// The following is needed because SDL_main redefines the main function
// #undef main

#include "World.h"
#include "Events/EventManager.h"

using namespace game;
using namespace events;
using namespace entity;

// Screen Dimensions constants
const int WIDTH = 800, HEIGHT = 600;

const int fps = 40;
const int minframetime = 1000 / fps;

SDL_Window *window = NULL;
SDL_Surface *screenSurface = NULL;
SDL_Surface *imageSurface = NULL;

/*
 Functions
 */

bool init();
bool loadMedia();
void close();

bool init(){
    bool success = true;
    
    // Initialises SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
    }
    else{
        // The window to be rendered into
        window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        if ( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else{
            // Get window surface
            screenSurface = SDL_GetWindowSurface( window );
        }
    }
    return success;
}

bool loadMedia()
{
    // Loading success flag
    bool success = true;
    
    // Load splash image
    imageSurface = SDL_LoadBMP( "hi.bmp" );
    if( imageSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", "hi.bmp", SDL_GetError() );
        success = false;
    }
    
    return success;
}

void close(){
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;
    
    SDL_FreeSurface(screenSurface);
    screenSurface = NULL;
    
    //Close the window
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}

int main(int argc, char * argv[]) {
    
    if(!init()){
        printf( "Failed to initialize!\n" );
		return EXIT_FAILURE;
    }

    // Constantly running window
    SDL_BlitSurface( imageSurface, NULL, screenSurface, NULL );
    SDL_UpdateWindowSurface( window );
        
	// Manages all the entities
	World* world = new World();

	Character* character = new Character();
	Entity* entity = world->createEntity(character);

	entity->registerEvent('KEYUP');
	entity->registerEvent('KEYDOWN');

	// Handles any event that occurs in app
	SDL_Event window_event;
	EventManager* eventManager = new EventManager(world);

	// Call setup on all entities
	world->setup();

	int frametime;

    while (true) {
		frametime = SDL_GetTicks();

		eventManager->update();

		world->update();

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
