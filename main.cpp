#include <SDL2/SDL.h>

// Contains basic functions for handling the display.
#include "window_handle.cpp"
#include "mesh.h"
#include "shader.h"

int main(int argc, char* argv[])
{
	// Initialize SDL, create window, create OpenGL context and initialize GLEW.
	initDisplay();
	
	// Mesh data.
	vertex triangle_vertices[] = {
		vertex(vec3(0.0, 0.5, 0.0)),
		vertex(vec3(0.5, -0.5, 0.0)),
		vertex(vec3(-0.5, -0.5, 0.0))
	};
	mesh triangle_mesh(triangle_vertices, sizeof(triangle_vertices) / sizeof(triangle_vertices[0]));
	
	// Shader data.
	shader basicShader("shaders/basic");
	basicShader.useShader();
	
	// Main loop.
	bool isRunning = true;
	SDL_Event userInput;
	while(isRunning)
	{
		// Check for user input.
		if(SDL_PollEvent(&userInput))
		{
			// Close window if "x" is pressed.
			if(userInput.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}
		
		// Logic.
		
		// Render.
		triangle_mesh.draw();
		
		// Swap buffers.
		updateDisplay();
	}
	
	// Clean after SDL.
	cleanSDL();
	
	return 0;
}

