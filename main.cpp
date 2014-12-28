#include <SDL2/SDL.h>

#include <vector>

// Contains basic functions for handling the display.
#include "window_handle.cpp"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "perspective.h"
#include "obj_parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	// Initialize SDL, create window, create OpenGL context and initialize GLEW.
	initDisplay();
	
	// Mesh data.
	mesh skybox("models/skybox.obj");
	mesh plane("models/plane.obj");
	
	float fMeshPosition = 0.0;
	float fMeshRotAngle = 0.0;
	
	// Shader data.
	shader basicShader("shaders/basic");
	basicShader.useShader();
	
	// Texture data.
	texture skybox_texture("textures/skybox.png");
	texture plane_texture("textures/triangle.jpg");
	
	// Transform class.
	camera myPersp(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), vec3(0.0, 1.0, 0.0), 70, 640 / 480, 0.1, 1000.0);
	transform transfClass;
	
	// Main loop.
	bool isRunning = true;
	SDL_Event userInput;
	glEnable(GL_DEPTH_TEST);
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
		// fMeshPosition += 0.0001;
		fMeshRotAngle += 0.01;
		
		// Render.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		transfClass.setMatrix();
		
		// Draw skybox
		/* PUSH AND POP DONT WORK!!! CHECK transform.h */
		transfClass.pushMatrix();
		skybox_texture.useTexture(0);
		basicShader.setSamplerUniform(0);
		transfClass.setRotationY(fMeshRotAngle);
		basicShader.update(transfClass, myPersp);
		skybox.draw();
		transfClass.popMatrix();
		
		// Draw plane.
		transfClass.pushMatrix();
		plane_texture.useTexture(1);
		basicShader.setSamplerUniform(1);
		// transfClass.setRotationY(-fMeshRotAngle);
		basicShader.update(transfClass, myPersp);
		plane.draw();
		transfClass.popMatrix();
		
		// Swap buffers.
		updateDisplay();
	}
	
	// Clean after SDL.
	cleanSDL();
	
	return 0;
}
