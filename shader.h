#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <GL/glew.h>
#include <string>

using namespace std;

class shader
{
	public:
		shader(const string& fileName);
		void useShader();
		virtual ~shader();
	private:
		static const unsigned short NUM_SHADERS = 2;
		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
};

#endif
