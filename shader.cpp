#include <GL/glew.h>

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

#include "shader.h"

using namespace std;

// Forward declarations.
static GLuint createShader(const string& shaderText, GLenum shaderType);
static void checkShaderError(GLuint shader, GLuint flag, const bool& isProgram, const string& errorMessage);
static string loadShader(const string& fileName);

shader::shader(const string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = createShader(loadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = createShader(loadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);
	
	glBindAttribLocation(m_program, 0, "aVertexPosition");
	
	for(unsigned short timesLooped = 0; timesLooped < NUM_SHADERS; timesLooped++)
	{
		glAttachShader(m_program, m_shaders[timesLooped]);
	}
	
	glLinkProgram(m_program);
	checkShaderError(m_program, GL_LINK_STATUS, true, "Program could not link.");
	
	glValidateProgram(m_program);
	checkShaderError(m_program, GL_VALIDATE_STATUS, true, "Program could not validate.");
}

void shader::useShader()
{
	glUseProgram(m_program);
}

shader::~shader()
{
	glDeleteProgram(m_program);
	
	for(unsigned short timesLooped = 0; timesLooped < NUM_SHADERS; timesLooped++)
	{
		glDetachShader(m_program, m_shaders[timesLooped]);
		glDeleteShader(m_shaders[timesLooped]);
	}
}

static GLuint createShader(const string& shaderText, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	
	const GLchar* shaderSourceStrings[1];
	shaderSourceStrings[0] = shaderText.c_str();
	
	GLint shaderSourceStringLengths[1];
	shaderSourceStringLengths[0] = shaderText.length();
	
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader could not compile.");
	
	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, const bool& isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[] = { 0 };
	
	if(isProgram) glGetProgramiv(shader, flag, &success);
	else glGetShaderiv(shader, flag, &success);
	
	if(success == GL_FALSE)
	{
		if(isProgram) glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		
		cerr << errorMessage << "\nError: " << error << endl;
		exit(EXIT_FAILURE);
	}
}

// Returns shader string.
static string loadShader(const string& fileName)
{
	string output, line;
	
	ifstream iFile;
	iFile.open(fileName.c_str());
	
	if(iFile.is_open())
	{
		while(iFile.good())
		{
			getline(iFile, line);
			output.append(line + "\n");
		}
	}
	
	else
	{
		cout << "Could not open " << fileName << "." << endl;
		exit(EXIT_FAILURE);
	}
	
	iFile.close();
	
	return output;
}
