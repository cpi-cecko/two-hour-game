/* 
 * This file contains the functions that will handle:
 * SDL initialization, window creation, context creation, GLEW initialization, "destructor"
 */

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <iostream>
#include <cstdlib>

using namespace std;

// Static variables for window and opengl context.
static SDL_Window* mainWindow = NULL;
static SDL_GLContext glContext = NULL;

// General settings.
static const char* WINDOW_TITLE = "Two-hour Game Engine";
static const unsigned short WINDOW_WIDTH = 640;
static const unsigned short WINDOW_HEIGHT = 480;  
static const Uint32 SDL_INIT_FLAGS = SDL_INIT_VIDEO;
static const Uint32 SDL_WINDOW_FLAGS = SDL_WINDOW_OPENGL;

// Forward declared so it can be used within other functions.
static void initSDL();
static void createWindow();
static void createContext();
static void initGLEW();
void cleanSDL();

void initDisplay()
{
	initSDL();
	createWindow();
	createContext();
	initGLEW();
}

// Initialize SDL.
static void initSDL()
{
	if(SDL_Init(SDL_INIT_FLAGS) < 0)
	{
		cout << "SDL initialization: FAILED" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		exit(EXIT_FAILURE);
	}
	
	else
	{
		cout << "SDL initialization: OK" << endl;
	}
}

// Create SDL window.
static void createWindow()
{
	mainWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FLAGS);

	if(mainWindow == NULL)
	{
		cout << "Window creation: FAILED" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		cleanSDL();
		exit(EXIT_FAILURE);
	}
	
	else
	{
		cout << "Window creation: OK" << endl;
	}
}

// Create OpenGL context.
static void createContext()
{
	glContext = SDL_GL_CreateContext(mainWindow);
	
	if(glContext == NULL)
	{
		cout << "Context creation: FAILED" << endl;
		cout << "Error: " << SDL_GetError() << endl;
		cleanSDL();
		exit(EXIT_FAILURE);
	}
	
	else
	{
		cout << "Context creation: OK" << endl;
	}
}

// Initialize GLEW.
static void initGLEW()
{
	glewExperimental = GL_TRUE;
	
	GLuint glewError = glewInit();
	if(glewError != GLEW_OK)
	{
		cout << "GLEW initialization: FAILED" << endl;
		cout << "Error: " << glewGetErrorString(glewError) << endl;
		cleanSDL();
		exit(EXIT_FAILURE);
	}
	
	else
	{
		cout << "GLEW initialization: OK" << endl;
	}
}

// Swap buffers.
void updateDisplay()
{
	SDL_GL_SwapWindow(mainWindow);
}

// Clean after SDL.
void cleanSDL()
{
	cout << "Cleaning..." << endl;
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}
