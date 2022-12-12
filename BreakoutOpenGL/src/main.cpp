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
// glm - open gl math library
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Standar Library
#include <cmath>
#include <iostream>
#include <vector>

void CheckForAndPrintGLError(std::string functionName);

GLint createShaderProgram(const GLchar** vertexShaderSource, const GLchar** fragmentShaderSource);

int main(int argc, char* argv[])
{
	// Tell SDL to use OpenGL version 3.3 and the Core profile features only.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	unsigned int width = 1280;
	unsigned int height = 720;
	// The window... into your soul.
	SDL_Window* window;
	window = SDL_CreateWindow("Breakout!",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL); // tell SDL to initialize the window to work with open gl!
	if (window == NULL) {
		std::cout << "SDL_CreateWindow() failed. Window is null. \nError Message: " << SDL_GetError() << std::endl;
		std::cout << "Aborting program." << std::endl;
		return -1;
	}

	SDL_Renderer* renderer{ SDL_CreateRenderer(window, -1, 0) };
	if (renderer == NULL) {
		std::cout << "SDL_CreateRenderer() failed. Renderer is null.\nError Message: " << SDL_GetError() << std::endl;
		std::cout << "Aborting program." << std::endl;
		return -1;
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

	std::string openGLVersionHeader{
		"--------------OpenGL Version-------------------"
	};
	std::cout << openGLVersionHeader << std::endl << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	/* --------------------------------- Get Misc. SDL Data ------------------------------------------- */
	// Print battery info to console
	std::string batteryHeader{
		"--------------Battery Info-------------------"
	};
	std::cout << batteryHeader << std::endl;
	int seconds, percent;
	SDL_PowerState powerState = SDL_GetPowerInfo(&seconds, &percent);
	std::cout << "Battery state: ";
	switch (powerState)
	{
	case SDL_POWERSTATE_UNKNOWN:
		std::cout << "unkown";
		break;
	case SDL_POWERSTATE_ON_BATTERY:
		std::cout << "on battery";
		break;
	case SDL_POWERSTATE_NO_BATTERY:
		std::cout << "no battery";
		break;
	case SDL_POWERSTATE_CHARGING:
		std::cout << "charging";
		break;
	case SDL_POWERSTATE_CHARGED:
		std::cout << "fully charged";
		break;
	default:
		break;
	}
	std::cout << std::endl;
	std::cout << "Power on for " << seconds << " seconds (" << percent << "%)" << std::endl;

	/* --------------------------------- Create Shaders ------------------------------------------- */
	// Create and compile shader 
	// Vertex shader produces vertices that will be used to draw a triangle (hard-coded)
	
	// FOR THE BALL
			
	// FOR THE PADDLE
	static const GLchar* paddleVertexShaderSource[]{ 
		"#version 330 core\n"
		"layout (location = 0) in vec4 offset;"
		"layout (location = 1) in vec4 color;"
		"out vec4 vs_color;"
		"void main(void)"
		"{"
		"const vec4 paddleVertices[] = vec4[](vec4(-0.20, -0.9, 0.5, 1.0),"
		"                                     vec4( 0.20, -0.9, 0.5, 1.0),"
		"                                     vec4( 0.20, -0.8, 0.5, 1.0),"
		"                                     vec4( 0.20, -0.8, 0.5, 1.0),"
		"                                     vec4(-0.20, -0.9, 0.5, 1.0),"
		"                                     vec4(-0.20, -0.8, 0.5, 1.0));"
	    "const vec4 paddleColors[]   = vec4[](vec4( 1.0,   0.0, 0.0, 1.0),"
		"                                     vec4( 0.0,   1.0, 0.0, 1.0),"
		"                                     vec4( 0.0,   0.0, 1.0, 1.0),"
		"                                     vec4( 1.0,   0.0, 0.0, 1.0),"
		"                                     vec4( 0.0,   1.0, 0.0, 1.0),"
		"                                     vec4( 0.0,   0.0, 1.0, 1.0));"
		"const vec4 ballVertex = vec4(0.0, 0.0, 0.5, 1.0);"
		"gl_Position = paddleVertices[gl_VertexID] + offset;"
		"vs_color = paddleColors[gl_VertexID];"
		"}"
	};
	static const GLchar* paddleFragmentShaderSource[]{
		"#version 330 core\n"
		"in vec4 vs_color;" // input from the vertex shader
		"out vec4 color;" // output to the framebuffer
		"void main(void) {"
		"    color = vs_color;"
		//"    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,"
		//"                 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,"
		//"                 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15),"
		//"                 1.0);"
		"}"
	};
	GLint paddleShaderProgram = createShaderProgram(paddleVertexShaderSource, paddleFragmentShaderSource);

	// Create vertex array object
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	CheckForAndPrintGLError("create vertex arrays");
	glBindVertexArray(vao);
	CheckForAndPrintGLError("bind vertex array");

	/* ------------------------------------- Rendering Data ----------------------------------------------- */
	// Next two lines are black magic from the Cherno OpenGL tutorial series
	// Creating matrices to moddel the projection-view matrix model

	glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	SDL_Event inputEvent;
	Uint64 performanceCounter{ SDL_GetPerformanceCounter() };
	Uint64 frequency = SDL_GetPerformanceFrequency();
	double timeDifference;
	//std::cout << "Performance counter frequency: " << frequency << std::endl;

	// The paddle's translation relative to the origin of the world space.
	// The world space is (currently) equivalent to the window space
	// So (0,0) in world space is the most bottom left pixel of the window
	glm::vec3 translation = glm::vec3(0, 0, 0);

	// offset vector for the paddle	
	GLfloat offset[4]{ 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat paddleColor[4]{ 0.5, 0.5, 0.5, 1.0 };
	float speed = 0.020f; // speed at which the paddle moves

	// The background (clear) color 
	GLfloat backgroundColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	/* -------------------------------------  Game Loop ----------------------------------------------- */
	bool gameIsRunning{ true };
	while (gameIsRunning) 
	{
		// Timers  ....
		Uint64 newPerformanceCounter = SDL_GetPerformanceCounter();
		timeDifference = (newPerformanceCounter - performanceCounter) / (double) frequency;
		performanceCounter = newPerformanceCounter;
		//std::cout << "Time differene: " << timeDifference << std::endl;

		/* Input Handling */
		//while (SDL_PollEvent(&inputEvent))
		if (SDL_PollEvent(&inputEvent))
		{
			if (inputEvent.type == SDL_KEYDOWN)
			{
				switch (inputEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					std::cout << "Player pressed esc. Exitting game loop" << std::endl;
					gameIsRunning = false;
					break;
				case SDLK_LEFT:
				case SDLK_a:
					// move(dir::LEFT);
					offset[0] -= speed;
					break;
				case SDLK_RIGHT:
				case SDLK_d:
					// move(dir::RIGHT);
					offset[0] += speed;
					break;
				case SDLK_UP:
				case SDLK_w:
					offset[1] += speed;
					// move(dir::UP);	
					break;
				case SDLK_DOWN:
				case SDLK_s:
					// move(dir::DOWN);
					offset[1] -= speed;
					break;
				default:
					// Key input behavior undefined
					break;
				}
			}
			else if (inputEvent.type == SDL_QUIT)
			{
				gameIsRunning = false;
			}
		}
		
		/* --------------------- Update the Simulation --------------------------*/
		// Change the clear color
		paddleColor[0] = (float) std::sin(performanceCounter / (float) frequency) * 0.5 + 0.5;
		paddleColor[2] = (float) std::cos(performanceCounter / (float) frequency) * 0.5 + 0.5;

		glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mvp = proj * view * model; 

		glVertexAttrib4fv(0, offset);
		glVertexAttrib4fv(1, paddleColor);

		/*-------------------OpenGL Rendering-------------------------*/
		// Wipe the screen to a solid color
		glClearBufferfv(GL_COLOR, 0, backgroundColor);

		// Bind our shader program for the paddle
		glUseProgram(paddleShaderProgram);
		// Draw Triangles
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Swap window buffers 
		SDL_GL_SwapWindow(window); // IT TOOK 3 HOURS TO WRITE THIS LINE OF CODE, THEREFORE FIXING MY CODE!!!
	}

	std::cout << "---------------Quitting application.------------------" << std::endl;
	// Cleanup
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(paddleShaderProgram);
	SDL_Quit();

	return 0;
}

void CheckForAndPrintGLError(std::string functionName)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL error in function " << functionName << " with error code: " << error << std::endl;
	}
}

GLint createShaderProgram(const GLchar** vertexShaderSource, const GLchar** fragmentShaderSource) 
{
	// Create and compile vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Check if shader compiled correctly
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "Vertex shader compilation failed!" << std::endl;
		GLint logSize = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> infoLog(logSize);
		glGetShaderInfoLog(vertexShader, logSize, NULL, &infoLog[0]);
		std::cout << "Error log: ";
		for (GLchar c : infoLog)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Vertex shader compiled successfuly." << std::endl;
	}

	// Create and compile fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	CheckForAndPrintGLError("frag shader source");
	glCompileShader(fragmentShader);
	CheckForAndPrintGLError("compile frag shader");

	// Check if shader compiled correctly
	success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "Fragment shader compilation failed!" << std::endl;
		GLint logSize = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logSize);
		std::vector<GLchar> infoLog(logSize);
		glGetShaderInfoLog(vertexShader, logSize, NULL, &infoLog[0]);
		std::cout << "Error log: ";
		for (GLchar c : infoLog)
		{
			std::cout << c;
		}
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Fragment shader compiled successfuly." << std::endl;
	}

	// Create program, attach shaders to it and link
	GLuint program = glCreateProgram();
	CheckForAndPrintGLError("create shader program");
	glAttachShader(program, vertexShader);
	CheckForAndPrintGLError("attach vertex shader");
	glAttachShader(program, fragmentShader);
	CheckForAndPrintGLError("attach frag shader");
	glLinkProgram(program);
	CheckForAndPrintGLError("link shader program");

	// Delete the now uneccessary shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
