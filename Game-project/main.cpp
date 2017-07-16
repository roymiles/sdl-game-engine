//
//  main.cpp
//  GameProject
//
//  Created by Aatina Punjabi on 16/07/2017.
//  Copyright © 2017 Aatina Punjabi. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char * argv[]) {
    
    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialise! SDL Error: " << SDL_GetError() << std::endl;
    }
    return EXIT_SUCCESS;
}
