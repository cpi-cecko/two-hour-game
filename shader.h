#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

#include <GL/glew.h>
#include <string>

#include "transform.h"
#include "perspective.h"

using namespace std;

class shader
{
	public:
		shader(const string& fileName);
		void update(transform& curTransform, const camera& curPersp);
		void useShader();
		void setSamplerUniform(unsigned short unit);
		virtual ~shader();
	private:
		enum
		{
			MVMATRIX_U, 
			SAMPLER_U,
			NUM_UNIFORMS
		};
	
		static const unsigned short NUM_SHADERS = 2;
		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];
};

#endif
