/*
	Welcome to my Breakout clone!
*/

// SDL2 - Windowing, Input
#include "SDL.h"
// glew - OpenGL function fetching 
#include <GL/glew.h>
#include <iostream>

int main(int argc, char* argv[]) 
{
	// Init SDL!
	SDL_Init(SDL_INIT_EVERYTHING);

	// The window... into your soul.
	SDL_Window* window;
	window = SDL_CreateWindow("Breakout!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600, 600,
		SDL_WINDOW_SHOWN);

	// Context is key.
	SDL_GLContext SDL_GL_CreateContext(window);
		

	GLenum result = glewInit();
	if (result != GLEW_OK)
	{
		std::cout << "Error! glewInit() != GLEW_OK ... glew failed to initialize? : " << result << std::endl;
	}
	
	//std::cout << std::endl << glGetString(GL_VERSION) << std::endl;

	std::cout << "Hello world!" << std::endl;
	return 0;
}