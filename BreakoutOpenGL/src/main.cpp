#include "SDL.h"
#include <iostream>

int main(int argc, char* argv[]) 
{
	// Init SDL!
	SDL_Init(SDL_INIT_EVERYTHING);

	std::cout << "Hello world!" << std::endl;
	return 0;
}