#include <SDL2/SDL.h>

#include "window_handle.cpp"

int main(int argc, char* argv[])
{
	// Initialize SDL, create window, create OpenGL context and initialize GLEW.
	initDisplay();
	
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
		
		// Swap buffers.
		updateDisplay();
	}
	
	// Clean after SDL.
	cleanSDL();
	
	return 0;
}
