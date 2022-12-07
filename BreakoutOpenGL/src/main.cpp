/*
	Welcome to my Breakout clone!
	Dependencies: 
	glew
	sdl2

*/
// glew - OpenGL function fetching 
#include <GL/glew.h>
// SDL2 - Windowing, Input
#include "SDL.h"

#include <iostream>


int main(int argc, char* argv[])
{
	// The window... into your soul.
	SDL_Window* window;
	window = SDL_CreateWindow("Breakout!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280, 720,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); // tell SDL to initialize the window to work with open gl!
	if (window == NULL) {
		std::cout << "SDL_CreateWindow() failed. Window is NULL. \n Error Message: " << SDL_GetError() << std::endl;
	}

	// Context is key.
	SDL_GLContext context = SDL_GL_CreateContext(window);

	if (context == NULL) {
		std::cout << "SDL_GL_CreateContext failed. Context is null. \nError Message: " << SDL_GetError() << std::endl;
		std::cout << "Aborting program." << std::endl;
		return -1;
	}

	// Make the context current.
	int makeContextCurrentSuccess = SDL_GL_MakeCurrent(window, context);
	if (makeContextCurrentSuccess != 0)
	{
		std::cout << "Error! SDL_GL_MakeCurrent() returned code " << makeContextCurrentSuccess << std::endl;
		std::cout << "Error message: " << std::endl << SDL_GetError() << std::endl;
		SDL_ClearError();
	}

	// Tell SDL to use OpenGL version 3.3 and the Core profile features only.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Init SDL!
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init(SDL_INIT_EVERYTHING) Failed! \n Error message: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Initialize glew (fetches OpenGL function pointers from GPU drivers)
	GLenum glewInitSuccess = glewInit();
	if (glewInitSuccess != GLEW_OK)
	{
		std::cout << "Error! glewInit() failed with code " << glewInitSuccess << std::endl;
		std::cout << "Error message: " << std::endl << SDL_GetError() << std::endl;
		SDL_ClearError();
	}

	std::cout << std::endl << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	/* Create OpenGL Data */
	// Create and compile shader
	// Create vertex array object
	// Create index buffer 


	/* -------------------------------------  Game Loop ------------------------------------------------*/

	bool gameIsRunning{ true };
	SDL_Event inputEvent;

	while (gameIsRunning) 
	{
		/* Input Handling */
		while (SDL_PollEvent(&inputEvent))
		{
			if (inputEvent.type == SDL_KEYDOWN)
			{
				if (inputEvent.key.keysym.sym == SDLK_ESCAPE)
				{
					std::cout << "Player pressed esc. Exitting game loop" << std::endl;
					gameIsRunning = false;
				}
			}
		}

		/* OpenGL Drawing */
		// Draw a Triangle
		// Wipe the screen to a solid color
		glClear(GL_COLOR_BUFFER_BIT);
		GLenum errorCode = glGetError();
		if (errorCode != GL_NO_ERROR)
		{
			std::cout << "glClear(GL_COLOR_BUFFER_BIT) failed!\nError code: " << errorCode << std::endl;
		}
		// bind shader 
		// bind vertex array 
		// bind index buffer
		// draw elements
		// glDrawElements(GL_TRIANGLES, count, type, indices);
	}

	std::cout << "Quitting application." << std::endl;
	SDL_Quit();

	return 0;
}
